// Copyright (c) All Rights Reserved, Navié
//
// This does not touch the license for the Cinema 4D specific code functions used
// Please see the Cinema 4D license correspondingly. All other rights reserved.
//
// Author: Samir Kharchi
#include "api_effex.h"
#include "fx_force_plugin.h"

Bool FXAPI::FXForceData::IsInstanceOf( const GeListNode *node, Int32_C4D type ) const
{
	if(type==EFFEX_FORCE) return TRUE;
	return Base::IsInstanceOf(node,type);
}

bool NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXForceData::Precompute( FXServer* server )
{
	return true;
}

bool NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXForceData::PrecomputeMP( FXServer* server )
{
	return true;
}

void NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXForceData::Process( void* t_data )
{

}

void NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXForceData::FreePrecompute( void )
{
}

Bool NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXForceData::Message(GeListNode *node, Int32_C4D type, void *t_data)
{
	BaseObject		*op		= (BaseObject*)node;
	BaseContainer *data = op->GetDataInstance();
		
	switch(type)
	{
	case MSG_DESCRIPTION_COMMAND:
		{
			DescriptionCommand *dc = (DescriptionCommand*)t_data;

			/* Handle Selectors */
			FXAPI::FXServer *server = FXAPI::FXServer::Get(node->GetDocument());
			if(!server) break;

			if(dc && dc->id[0].id==FORCEPLUGIN_DURATION_SELECTOR)
			{
				std::vector<FXBase*> items;
				GetNodes(server->GetEffexScene(get_wrapper()),nullptr,items,FXAPI::NodeRetrieveType_Duration);

				FXAPI::FXTypeInfos t_types;
				t_types.push_back(FXAPI::FXTypeInfo(EFFEX_DURATION,"Duration"));

				OpenCandidatePopup(dc->msg->GetId()==EFFEX_NODEGROUP,items,t_types,op,FORCEPLUGIN_DURATION,false,true,0);
				return true;
			}
		}
		break;
	}
	return Base::Message(node,type,t_data);
}

void NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXForceData::GetSubType(int& subtype) const
{
	subtype |= (1 << nst_particle);
	subtype |= (1 << nst_grid);
}

static void FillObjectPlugin(OBJECTPLUGIN *np, DataAllocator *npalloc, Int32_C4D info, Int32_C4D disklevel, BaseBitmap *icon, void *emulation)
{
	FillNodePlugin(np,info,npalloc,icon,disklevel,emulation);

	np->command_icon				= icon;
	np->GetDimension				= &ObjectData::GetDimension;
	np->Draw						= &ObjectData::Draw;
	np->DetectHandle				= &ObjectData::DetectHandle;
	np->MoveHandle					= &ObjectData::MoveHandle;
	np->Execute						= &ObjectData::Execute;
	np->AddToExecution				= &ObjectData::AddToExecution;
	np->GetModelingAxis				= &ObjectData::GetModelingAxis;
	np->DrawShadow					= &ObjectData::DrawShadow;
}

Bool RegisterFXForcePlugin(Int32_C4D id, const String &str, Int32_C4D objectinfo, DataAllocator *npalloc, const String &description, BaseBitmap *icon, Int32_C4D disklevel)
{
	if (description.Content() && !RegisterDescription(id,description)) return FALSE;

	FXAPI::FXFORCEPLUGIN np;
	ClearMem(&np,sizeof(np));
	FillObjectPlugin(&np,npalloc,objectinfo,disklevel,icon,nullptr);

	np.CheckDirty				= &ObjectData::CheckDirty;
	np.GetVirtualObjects		= &ObjectData::GetVirtualObjects;

	np.GetSubType				= &FXAPI::FXNodeData::GetSubType;
	np.PortsDirty				= &FXAPI::FXNodeData::PortsDirty;
	np.DrawNode					= &FXAPI::FXNodeData::DrawNode;
	np.get_wrapper				= &FXAPI::FXNodeData::get_wrapper;

	np.FillData					= &FXAPI::FXNodeData::FillData;
	np.FillPorts				= &FXAPI::FXNodeData::FillPorts;
	np.ClearPorts				= &FXAPI::FXNodeData::ClearPorts;

	np.Precompute				= &FXAPI::FXForceData::Precompute;
	np.PrecomputeMP				= &FXAPI::FXForceData::PrecomputeMP;
	np.Process					= &FXAPI::FXForceData::Process;
	np.FreePrecompute			= &FXAPI::FXForceData::FreePrecompute;

	return GeRegisterPlugin(PLUGINTYPE_OBJECT,id,str,&np,sizeof(np));
}