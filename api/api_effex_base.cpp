// Copyright (c) All Rights Reserved, Navié
//
// This does not touch the license for the Cinema 4D specific code functions used
// Please see the Cinema 4D license correspondingly. All other rights reserved.
//
// Author: Samir Kharchi
#include "api_effex_base.h"
#include "api_effex.h"

extern C4DLibrary* fx_particle_lib;

void NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXBase::Initialise( iNodeBaseWrapper* ptr_interface, FXScene* server )
{
	get_library_set_sub(EffexLibrary,fx_base,Initialise,fx_particle_lib);
	get_library_value_2(vlib->fx_base,iBase,Initialise,ptr_interface,(NAVIE_GLOBAL::NAVIE_EFFEX::Scene*)server);
}

bool NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXBase::IsCached( void ) const
{
	get_library_sub(EffexLibrary,fx_base,IsCached,false,fx_particle_lib);
	return get_library_value_0(vlib->fx_base,iBase,IsCached);
}

bool NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXBase::IsDirty( DirtyCheck* checklist )
{
	get_library_sub(EffexLibrary,fx_base,IsDirty,false,fx_particle_lib);
	return get_library_value_1(vlib->fx_base,iBase,IsDirty,checklist);
}

FXAPI::FXScene* NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXBase::GetScene(void) const
{
	get_library_sub(EffexLibrary,fx_base,GetScene,false,fx_particle_lib);
	return get_library_value_0_cast(vlib->fx_base,iBase,FXScene,GetScene);
}

iNodeBaseWrapper* FXAPI::FXBase::GetInterface()
{
	get_library_sub(EffexLibrary,fx_base,GetInterface,0,fx_particle_lib);
	return get_library_value_0(vlib->fx_base,iBase,GetInterface);
}

const int FXAPI::FXBase::GetType( void ) const
{
	get_library_sub(EffexLibrary,fx_base,GetType,2000,fx_particle_lib);
	return get_library_value_0(vlib->fx_base,iBase,GetType);
}

NAVIE_GLOBAL::NAVIE_EFFEX::NodeBaseType FXAPI::FXBase::GetBaseType( void ) const
{
	get_library_sub(EffexLibrary,fx_base,GetBaseType,NAVIE_GLOBAL::NAVIE_EFFEX::NodeBaseType(nbt_unknown),fx_particle_lib);
	return get_library_value_0(vlib->fx_base,iBase,GetBaseType);
}

void FXAPI::FXBase::GetSubType( int& subtype ) const
{
	get_library_set_sub(EffexLibrary,fx_base,GetSubType,fx_particle_lib);
	get_library_value_1(vlib->fx_base,iBase,GetSubType,subtype);
}
