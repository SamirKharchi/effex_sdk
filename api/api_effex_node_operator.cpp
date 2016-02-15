// Copyright (c) All Rights Reserved, Navié
//
// This does not touch the license for the Cinema 4D specific code functions used
// Please see the Cinema 4D license correspondingly. All other rights reserved.
//
// Author: Samir Kharchi
#include "api_effex.h"
#include "fx_constraint.h"
#include "fx_operator_plugin.h"

Bool FXAPI::FXOperatorData::IsInstanceOf( const GeListNode *node, Int32_C4D type ) const
{
	if(type==EFFEX_OPERATOR) return TRUE;
	return Base::IsInstanceOf(node,type);
}

bool NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXOperatorData::Precompute( FXServer* server )
{
	return true;
}

bool NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXOperatorData::PrecomputeMP( FXServer* server )
{
	return true;
}

void NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXOperatorData::Process( void* t_data )
{

}

void NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXOperatorData::FreePrecompute( void )
{

}

bool NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXOperatorData::UseOwnThread( void ) const
{
	return false;
}

bool NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXOperatorData::IsMultiStep( void ) const
{
	return false;
}

bool NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXOperatorData::IsMultiPrecompute( void ) const
{
	return false;
}

bool NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXOperatorData::IsUpdateable( void ) const
{
	return false;
}

Bool NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXOperatorData::Message(GeListNode *node, Int32_C4D type, void *t_data)
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

			if(dc && dc->id[0].id==OPERATORPLUGIN_DURATION_SELECTOR)
			{
				std::vector<FXBase*> items;
				GetNodes(server->GetEffexScene(get_wrapper()),nullptr,items,FXAPI::NodeRetrieveType_Duration);

				FXAPI::FXTypeInfos t_types;
				t_types.push_back(FXAPI::FXTypeInfo(EFFEX_DURATION,"Duration"));

				OpenCandidatePopup(dc->msg->GetId()==EFFEX_NODEGROUP,items,t_types,op,OPERATORPLUGIN_DURATION,false,true,0);
				return true;
			}
		}
		break;
	}
	return Base::Message(node,type,t_data);
}

void NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXOperatorData::GetSubType(int& subtype) const
{
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
#ifdef C4D_R15
	np->DrawShadow = &ObjectData::DrawShadow;
#endif
}

Bool RegisterFXOperatorPlugin(Int32_C4D id, const String &str, Int32_C4D objectinfo, DataAllocator *npalloc, const String &description, BaseBitmap *icon, Int32_C4D disklevel)
{
	if (description.Content() && !RegisterDescription(id,description)) return FALSE;

	FXAPI::FXOPERATORPLUGIN np;
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

	np.Precompute				= &FXAPI::FXOperatorData::Precompute;
	np.PrecomputeMP				= &FXAPI::FXOperatorData::PrecomputeMP;
	np.Process					= &FXAPI::FXOperatorData::Process;
	np.FreePrecompute			= &FXAPI::FXOperatorData::FreePrecompute;

	np.UseOwnThread				= &FXAPI::FXOperatorData::UseOwnThread;
	np.IsMultiStep				= &FXAPI::FXOperatorData::IsMultiStep;
	np.IsMultiPrecompute		= &FXAPI::FXOperatorData::IsMultiPrecompute;
	np.IsUpdateable				= &FXAPI::FXOperatorData::IsUpdateable;;

	return GeRegisterPlugin(PLUGINTYPE_OBJECT,id,str,&np,sizeof(np));
}