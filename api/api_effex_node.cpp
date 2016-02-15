// Copyright (c) All Rights Reserved, Navié
//
// This does not touch the license for the Cinema 4D specific code functions used
// Please see the Cinema 4D license correspondingly. All other rights reserved.
//
// Author: Samir Kharchi
#include <algorithm>

#include "api_effex.h"
#include "fx_base.h"
#include "fx_force_base.h"
#include "fx_base_constraints.h"
#include "customgui_inexclude.h"

NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXNodeData::FXNodeData() : ObjectData(), m_wrapper(nullptr)
{
}

NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXNodeData::~FXNodeData()
{
	if(m_wrapper) DeleteWrapper(m_wrapper);
}

iNodeBaseWrapper* NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXNodeData::get_wrapper(void)
{
	return m_wrapper;
}

const iNodeBaseWrapper* NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXNodeData::get_wrapper(void) const
{
	return m_wrapper;
}

Bool FXAPI::FXNodeData::IsInstanceOf(const GeListNode *node, Int32_C4D type) const
{
	if(type==EFFEX_SCENE) return TRUE;
	return ObjectData::IsInstanceOf(node,type);
}

BaseObject *FXAPI::FXNodeData::GetVirtualObjects(BaseObject *op, HierarchyHelp *hh)
{
	BaseContainer *data = op->GetDataInstance();

	Bool dirty = op->CheckCache(hh) || op->IsDirty(DIRTYFLAGS_DATA);
	if (!dirty) 
	{
		return op->GetCache(hh);
	}
	return PolygonObject::Alloc(0,0);
}

Bool FXAPI::FXNodeData::Init( GeListNode *node )
{
	BaseObject		*op		= (BaseObject*)node;
	BaseContainer *data = op->GetDataInstance();

	data->SetData(FORCE_BASE_CONSTRAINTS, GeData(CUSTOMDATATYPE_INEXCLUDE_LIST, DEFAULTVALUE));
	data->SetInt32(FX_BASE_PIPELINESTAGE,0);
	data->SetInt32(FX_BASE_PRIORITY,0);
	data->SetInt32(FX_FORCE_BASE_ITERATIONS,0);
	data->SetBool(FX_BASE_SPLIT,true);

	m_is_rendering = false;
	m_link_dropped = false;
	m_is_rendering_external = false;

	BaseDocument* doc = op->GetDocument();
	if(!m_wrapper) m_wrapper = CreateWrapper(op);
	return ObjectData::Init(node);
}

void NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXNodeData::Free(GeListNode *node)
{
	if(m_wrapper) DeleteWrapper(m_wrapper);
}

void SearchConstraints( BasePlugin* t_plugin, FXAPI::FXTypeInfos &t_types )
{
	bool effex_nodes = false;
	while(t_plugin!=nullptr)
	{
		if(t_plugin->GetID()==EFFEX_SCENE)
			effex_nodes = true;
		if(effex_nodes && t_plugin->GetPluginType()==PLUGINTYPE_OBJECT)
		{
			BaseList2D* tnode = t_plugin->Alloc(t_plugin->GetID());
			if(tnode && (tnode->IsInstanceOf(EFFEX_CONSTRAINT_BASE) || tnode->IsInstanceOf(EFFEX_CONSTRAINT_PLUGIN)))
			{
				t_types.push_back(FXAPI::FXTypeInfo(t_plugin->GetID(),t_plugin->GetName()));
			}
			BaseList2D::Free(tnode);
		}
		if(t_plugin->GetDown())
			SearchConstraints(t_plugin->GetDown(),t_types);
		
		t_plugin = t_plugin->GetNext();
	}
}

inline bool sort_types(const FXAPI::FXTypeInfo& A, const FXAPI::FXTypeInfo& B)
{
	return A.second.LexCompare(B.second) < 0;
}

//-----------------------------------------------------------------------------
static BaseObject *CheckHierarchy(BaseObject *obj, BaseObject* stopAt) 
{ 
	if (!obj) return nullptr; 

	BaseObject* next = nullptr; 
	if ((next = obj->GetDown())) return next; 
	else if ((next = obj->GetNext())) return next;
	else if(next==nullptr && obj==stopAt) return nullptr;

	BaseObject* up = obj; 
	while ((up = up->GetUp())) 
	{ 
		if (up == stopAt) return nullptr; 
		if ((next = up->GetNext())) return next; 
	}  
	return nullptr;
} 

static bool has_acceptable_children(BaseObject* description_op, BaseObject* dropelement, const DescID& linkfield_id)
{
	AutoAlloc<Description> desc; if (!desc) return false;
	if (!description_op->GetDescription(desc,DESCFLAGS_DESC_0)) return false;

	const BaseContainer *bc = desc->GetParameterI(linkfield_id,nullptr); if(!bc) return false;

	BaseContainer accept_list = bc->GetContainer(DESC_ACCEPT);
	BrowseContainer browser(&accept_list);

	Int32_C4D current_id = -1; GeData *t_data;
	while(browser.GetNext(&current_id,&t_data))
	{
		if(current_id==EFFEX_NODEGROUP) continue;

		BaseObject* child_node = dropelement->GetDown();
		while(child_node!=nullptr)
		{		
			if(child_node->IsInstanceOf(current_id))
				return true;

			/* Browse next object */
			child_node = CheckHierarchy(child_node,dropelement); 
			if(!child_node) break;
		}
	}
	return false;
}

static Int32_C4D get_acceptable_children(BaseObject* description_op, BaseObject* dropelement, const DescID* linkfield_id, AtomArray* arr)
{
	AutoAlloc<Description> desc; if (!desc) return false;
	if (!description_op->GetDescription(desc,DESCFLAGS_DESC_0)) return false;

	const BaseContainer *bc = desc->GetParameterI(*linkfield_id,nullptr); if(!bc) return false;

	BaseContainer accept_list = bc->GetContainer(DESC_ACCEPT);
	//Int32_C4D candidate_button = bc->GetLong(DESC_PARENTID,NOTOK);

	BrowseContainer browser(&accept_list);

	Int32_C4D current_id = -1; GeData *t_data;
	int cnt = 0;
	while(browser.GetNext(&current_id,&t_data))
	{
		if(current_id==EFFEX_NODEGROUP || current_id==Obase) continue;

		BaseObject* child_node = dropelement->GetDown();
		while(child_node!=nullptr)
		{		
			if(child_node->IsInstanceOf(current_id) && arr->Find(child_node)==NOTOK){
				arr->Append(child_node);
				++cnt;
			}

			/* Browse next object */
			child_node = CheckHierarchy(child_node,dropelement); 
			if(!child_node) break;
		}
	}	
	return cnt;
}

inline void FixExcludeList_AfterRemoval(InExcludeData* t_objlist, BaseDocument* doc)
{
	if(t_objlist && t_objlist->GetObjectCount() > 0) {
		for(int i = 0; i < t_objlist->GetObjectCount(); ++i) {
			BaseList2D* t_baseobject = t_objlist->ObjectFromIndex(doc, i);
			if(!t_baseobject) {/* An object has been deleted but C4D still returns the old count (C4D bug) */
				if(!t_objlist->DeleteObject(i))
					break;
			}
		}
	}
}

Bool FXAPI::FXNodeData::Message( GeListNode *node, Int32_C4D type, void *t_data )
{
	BaseObject		*op		= (BaseObject*)node;
	BaseContainer *data = op->GetDataInstance();

	FixExcludeList_AfterRemoval((InExcludeData*)data->GetCustomDataType(FORCE_BASE_CONSTRAINTS, CUSTOMDATATYPE_INEXCLUDE_LIST),op->GetDocument());

	switch(type)
	{
	case MSG_MULTI_RENDERNOTIFICATION:
		{
			RenderNotificationData *cid = (RenderNotificationData*)t_data;
			if(cid)
			{
				if(cid->start && !cid->external){
					m_is_rendering = true;
				}
				else if(!cid->start && !cid->external)
					m_is_rendering = false;
			}
		}
		break;
	case MSG_DESCRIPTION_POSTSETPARAMETER:
		{
			DescriptionPostSetValue* dpsv = static_cast<DescriptionPostSetValue*>(t_data);
			if(dpsv && dpsv->descid->operator [](0).id==FORCE_BASE_CONSTRAINTS) 
			{
				//Handle Constraint flags
				InExcludeData* include = (InExcludeData*)data->GetCustomDataType(FORCE_BASE_CONSTRAINTS, CUSTOMDATATYPE_INEXCLUDE_LIST);
				HandleInexcludeBits(include,m_csmode_oldflag);				
			}
		}
		break;
	case MSG_DESCRIPTION_COMMAND:
		{
			DescriptionCommand *dc = (DescriptionCommand*)t_data;

			/* Handle Selectors */
			FXAPI::FXServer *server = FXAPI::FXServer::Get(node->GetDocument());
			if(!server) break;

			if(dc && dc->id[0].id==FORCE_BASE_CONSTRAINTS_SELECTOR)
			{
				std::vector<FXConstraint*> items;
				server->GetConstraints(nullptr,items);

				FXAPI::FXTypeInfos t_types;
				SearchConstraints(GetFirstPlugin(), t_types);
				std::sort(t_types.begin(),t_types.end(),sort_types);

				OpenCandidatePopup(dc->msg->GetId()==EFFEX_NODEGROUP,reinterpret_cast< std::vector<FXBase*>& >(items),t_types,op,FORCE_BASE_CONSTRAINTS,true,true,2);
				return true;
			}
		}
		break;
	case MSG_DESCRIPTION_CHECKDRAGANDDROP:
		{
			DescriptionCheckDragAndDrop* dropped = static_cast<DescriptionCheckDragAndDrop*>(t_data); if(!dropped) break;
			BaseObject* dropelement = static_cast<BaseObject*>(dropped->element);
			if(dropelement->GetType()==EFFEX_NODEGROUP)
			{
				if(has_acceptable_children(op,dropelement,dropped->id))
				{
					dropped->result = true;
					m_link_dropped = true;
					return true;
				}
				else
					dropped->result = false;
				return true;
			}
		}
		break;
	case MSG_DESCRIPTION_CHECKUPDATE:
		{
			DescriptionCheckUpdate* dcu = static_cast<DescriptionCheckUpdate*>(t_data);
			if(dcu && m_link_dropped)
			{
				BaseObject* node_group = data->GetObjectLink(dcu->descid->operator [](0).id,dcu->doc);
				if(node_group && node_group->GetType()==EFFEX_NODEGROUP)
				{
					AutoAlloc<AtomArray> arr;
					Int32_C4D cnt = get_acceptable_children(op,node_group,dcu->descid,arr);
					if(cnt > 1)
					{
						FXAPI::FXServer *server = FXAPI::FXServer::Get(node->GetDocument()); if(!server) break;
						FXAPI::FXScene* t_scene = server->GetEffexScene(op); if(!t_scene) break;

						std::vector<FXAPI::FXBase*> items; FXAPI::FXTypeInfos t_types;
						for (Int32_C4D i = 0; i < arr->GetCount(); ++i)
						{
							FXAPI::FXBase* snode = GetNode(t_scene,static_cast<BaseObject*>(arr->GetIndex(i)),FXAPI::NodeRetrieveType_Unknown); if(!snode) continue;
							items.push_back(snode);
						}
						if(!FXAPI::OpenCandidatePopup(false,items,t_types,op,dcu->descid->operator [](0).id,false,true,0))
							op->SetParameter(dcu->descid->operator [](0).id,static_cast<BaseList2D*>(arr->GetIndex(0)),DESCFLAGS_SET_0);
					}		
					else
						op->SetParameter(dcu->descid->operator [](0).id,static_cast<BaseList2D*>(arr->GetIndex(0)),DESCFLAGS_SET_0);
				}
				m_link_dropped = false;
				return true;
			}
		}
	}
	return ObjectData::Message(node,type,t_data);
}


Bool FXAPI::FXNodeData::Read(GeListNode *node, HyperFile *hf, Int32_C4D level)
{
	/************************************************************************/	
	Int32_C4D cnt = 0;
	if(!hf->ReadInt32(&cnt)) return FALSE;

	m_csmode_oldflag.resize(cnt);
	for(std::vector<Int32_C4D>::iterator iter = m_csmode_oldflag.begin(); iter != m_csmode_oldflag.end(); ++iter)
	{
		Int32_C4D val;
		if(!hf->ReadInt32(&val)) return FALSE; *iter = val;
	}
	return ObjectData::Read(node,hf,level);
}

Bool FXAPI::FXNodeData::Write(GeListNode *node, HyperFile *hf)
{
	/************************************************************************/	
	if(!hf->WriteInt32((Int32_C4D)m_csmode_oldflag.size())) return FALSE;
	for(std::vector<Int32_C4D>::const_iterator iter = m_csmode_oldflag.begin(); iter != m_csmode_oldflag.end(); ++iter)
		if(!hf->WriteInt32(*iter)) return FALSE;

	return ObjectData::Write(node,hf);
}

Bool FXAPI::FXNodeData::CopyTo(NodeData *dest, GeListNode *snode, GeListNode *dnode, COPYFLAGS flags, AliasTrans *trn)
{
	FXNodeData* t_dest	= (FXNodeData*)dest;
	t_dest->m_csmode_oldflag		= m_csmode_oldflag;

	return ObjectData::CopyTo(dest,snode,dnode,flags,trn);
}

bool FXAPI::FXNodeData::FillData( BaseObject* node )
{
	return node!=nullptr;
}

bool FXAPI::FXNodeData::FillPorts( BaseObject* node , FXServer* server )
{
	return (node!=nullptr && server!=nullptr);
}

void FXAPI::FXNodeData::ClearPorts( void )
{

}

void FXAPI::FXNodeData::GetSubType( int& subtype ) const
{

}

bool FXAPI::FXNodeData::PortsDirty( FXServer* server ) const
{
	return false;
}

DRAWRESULT FXAPI::FXNodeData::DrawNode( BaseObject* op, DRAWPASS drawpass, BaseDraw* bd, BaseDrawHelp* bh )
{
	return DRAWRESULT_OK;
}

static void FillObjectPlugin(OBJECTPLUGIN *np, DataAllocator *npalloc, Int32_C4D info, Int32_C4D disklevel, BaseBitmap *icon, void *emulation)
{
	FillNodePlugin(np,info,npalloc,icon,disklevel,emulation);

	np->command_icon				= icon;
	np->GetDimension				= &ObjectData::GetDimension;
	np->Draw								= &ObjectData::Draw;
	np->DetectHandle				= &ObjectData::DetectHandle;
	np->MoveHandle					= &ObjectData::MoveHandle;
	np->Execute							= &ObjectData::Execute;
	np->AddToExecution			= &ObjectData::AddToExecution;
	np->GetModelingAxis			= &ObjectData::GetModelingAxis;
	np->DrawShadow = &ObjectData::DrawShadow;
}

Bool RegisterFXObjectPlugin(Int32_C4D id, const String &str, Int32_C4D objectinfo, DataAllocator *npalloc, const String &description, BaseBitmap *icon, Int32_C4D disklevel)
{
	if (description.Content() && !RegisterDescription(id,description)) return FALSE;

	FXAPI::FXNODEPLUGIN np;
	ClearMem(&np,sizeof(np));
	FillObjectPlugin(&np,npalloc,objectinfo,disklevel,icon,nullptr);

	np.CheckDirty				= &ObjectData::CheckDirty;
	np.GetVirtualObjects		= &ObjectData::GetVirtualObjects;
	np.DrawNode					= &FXAPI::FXNodeData::DrawNode;
	np.get_wrapper				= &FXAPI::FXNodeData::get_wrapper;
	
	return GeRegisterPlugin(PLUGINTYPE_OBJECT,id,str,&np,sizeof(np));
}