// Copyright (c) All Rights Reserved, Navié
//
// This does not touch the license for the Cinema 4D specific code functions used
// Please see the Cinema 4D license correspondingly. All other rights reserved.
//
// Author: Samir Kharchi
#include "api_effex.h"
#include "fx_constraint.h"

Bool NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXConstraintData::Init( GeListNode *node )
{
	BaseObject		*op		= (BaseObject*)node;
	BaseContainer *data = op->GetDataInstance();

	data->SetBool(CONSTRAINT_INVERT, FALSE);
	data->SetFloat(CONSTRAINT_INTENSITY, 1.0);
	//Range Mapper
	data->SetFloat(CONSTRAINT_MAPPING_INPUT_MIN, 0.0);
	data->SetFloat(CONSTRAINT_MAPPING_INPUT_MAX, 1.0);
	data->SetFloat(CONSTRAINT_MAPPING_OUTPUT_MIN, 0.0);
	data->SetFloat(CONSTRAINT_MAPPING_OUTPUT_MAX, 1.0);
	data->SetBool(CONSTRAINT_MAPPING_CLAMP_MIN, true);
	data->SetBool(CONSTRAINT_MAPPING_CLAMP_MAX, true);
	data->SetBool(CONSTRAINT_MAPPING_SPLINE_USE, false);

	GeData spline(CUSTOMDATATYPE_SPLINE, DEFAULTVALUE);
	SplineData* i_spline = (SplineData*)spline.GetCustomDataType(CUSTOMDATATYPE_SPLINE);
	i_spline->MakeLinearSplineLinear(2);
	data->SetData	(CONSTRAINT_MAPPING_SPLINE,spline); 

	return Base::Init(node);
}
Bool FXAPI::FXConstraintData::IsInstanceOf( const GeListNode *node, Int32_C4D type ) const
{
	if(type==EFFEX_CONSTRAINT) return TRUE;
	return Base::IsInstanceOf(node,type);
}

void NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXConstraintData::GetSubType( int& subtype ) const
{
	subtype |= (1 << nst_constraint);
}

bool FXAPI::FXConstraintData::IsParticleConstraint( void ) const
{
	return false;
}

void FXAPI::FXConstraintData::PrecomputeConstraint( void* t_data )
{

}

void FXAPI::FXConstraintData::FreePrecomputeConstraint( void )
{

}

bool FXAPI::FXConstraintData::GetConstraint( const vector3d& position, double& src_value, void* local_data, int cpu /*= 0*/ )
{
	return true;
}

bool FXAPI::FXConstraintData::GetParticleConstraint( const vector3d& position, double& src_value, void* local_data, int cpu /*= 0*/, const void* t_particle /*= nullptr*/ )
{
	return true;
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

Bool RegisterFXConstraintPlugin(Int32_C4D id, const String &str, Int32_C4D objectinfo, DataAllocator *npalloc, const String &description, BaseBitmap *icon, Int32_C4D disklevel)
{
	if (description.Content() && !RegisterDescription(id,description)) return FALSE;

	FXAPI::FXCONSTRAINTPLUGIN np;
	ClearMem(&np,sizeof(np));
	FillObjectPlugin(&np,npalloc,objectinfo,disklevel,icon,nullptr);

	np.CheckDirty				= &ObjectData::CheckDirty;
	np.GetVirtualObjects		= &ObjectData::GetVirtualObjects;

	np.GetSubType				= &FXAPI::FXNodeData::GetSubType;

	np.FillData					= &FXAPI::FXNodeData::FillData;
	np.FillPorts				= &FXAPI::FXNodeData::FillPorts;
	np.ClearPorts				= &FXAPI::FXNodeData::ClearPorts;
	np.DrawNode					= &FXAPI::FXNodeData::DrawNode;
	np.get_wrapper				= &FXAPI::FXNodeData::get_wrapper;

	np.IsParticleConstraint		= &FXAPI::FXConstraintData::IsParticleConstraint;
	np.PrecomputeConstraint		= &FXAPI::FXConstraintData::PrecomputeConstraint;
	np.FreePrecomputeConstraint = &FXAPI::FXConstraintData::FreePrecomputeConstraint;
	np.GetConstraint			= &FXAPI::FXConstraintData::GetConstraint;
	np.GetParticleConstraint	= &FXAPI::FXConstraintData::GetParticleConstraint;

	return GeRegisterPlugin(PLUGINTYPE_OBJECT,id,str,&np,sizeof(np));
}