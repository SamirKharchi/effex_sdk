// Copyright (c) All Rights Reserved, Navié
//
// This does not touch the license for the Cinema 4D specific code functions used
// Please see the Cinema 4D license correspondingly. All other rights reserved.
//
// Author: Samir Kharchi
#include "api_effex.h"

extern C4DLibrary* fx_particle_lib;
/************************************************************************/
/* Effex Particle */
/************************************************************************/
const NAVIE_GLOBAL::vector3d& FXAPI::FXParticle::GetPosition( void ) const 
{
	get_library_sub(EffexLibrary,fx_particle,GetPosition,zerovector,fx_particle_lib);
	return get_library_value_0(vlib->fx_particle,const EffexParticle,GetPosition);
}
const NAVIE_GLOBAL::vector3d& FXAPI::FXParticle::GetVelocity( void ) const 
{
	get_library_sub(EffexLibrary,fx_particle,GetVelocity,zerovector,fx_particle_lib);
	return get_library_value_0(vlib->fx_particle,const EffexParticle,GetVelocity); 
}
double FXAPI::FXParticle::GetProperty_Scalar( const double& _default , const ParticleProperty & prop, const iNodeBaseWrapper* node_interface /*= nullptr*/ ) const
{ 
	get_library_sub(EffexLibrary,fx_particle,GetProperty_Scalar,_default,fx_particle_lib);
	return get_library_value_3(vlib->fx_particle,const EffexParticle,GetProperty_Scalar,_default,prop,node_interface); 
}
NAVIE_GLOBAL::vector3d FXAPI::FXParticle::GetProperty_Vector( const vector3d& _default , const ParticleProperty & prop, const iNodeBaseWrapper* node_interface /*= nullptr*/ ) const
{ 
	get_library_sub(EffexLibrary,fx_particle,GetProperty_Vector,_default,fx_particle_lib);
	return get_library_value_3(vlib->fx_particle,const EffexParticle,GetProperty_Vector,_default,prop,node_interface); 
}
bool FXAPI::FXParticle::GetProperty_State( const bool& _default , const ParticleProperty & prop, const iNodeBaseWrapper* node_interface /*= nullptr*/ ) const
{ 
	get_library_sub(EffexLibrary,fx_particle,GetProperty_State,_default,fx_particle_lib);
	return get_library_value_3(vlib->fx_particle,const EffexParticle,GetProperty_State,_default,prop,node_interface); 
}
double FXAPI::FXParticle::GetAge( void ) const
{
	get_library_sub(EffexLibrary,fx_particle,GetPosition,0.0,fx_particle_lib);
	return get_library_value_0(vlib->fx_particle,const EffexParticle,GetAge); 
}

/************************************************************************/
void FXAPI::FXParticle::SetPosition( const vector3d& pos )
{
	get_library_set_sub(EffexLibrary,fx_particle,SetPosition,fx_particle_lib);
	get_library_value_1(vlib->fx_particle,EffexParticle,SetPosition,pos); 
}
void FXAPI::FXParticle::SetVelocity( const vector3d& vel ) 
{
	get_library_set_sub(EffexLibrary,fx_particle,SetVelocity,fx_particle_lib);
	get_library_value_1(vlib->fx_particle,EffexParticle,SetVelocity,vel); 
}
bool FXAPI::FXParticle::SetProperty_Scalar( const double val , const ParticleProperty & prop, const iNodeBaseWrapper* node_interface /*= nullptr*/ )
{ 
	get_library_sub(EffexLibrary,fx_particle,SetProperty_Scalar,false,fx_particle_lib);
	return get_library_value_3(vlib->fx_particle,EffexParticle,SetProperty_Scalar,val,prop,node_interface);
}
bool FXAPI::FXParticle::SetProperty_Vector( const vector3d& val , const ParticleProperty & prop, const iNodeBaseWrapper* node_interface /*= nullptr*/ )
{ 
	get_library_sub(EffexLibrary,fx_particle,SetProperty_Vector,false,fx_particle_lib);
	return get_library_value_3(vlib->fx_particle,EffexParticle,SetProperty_Vector,val,prop,node_interface);
}
bool FXAPI::FXParticle::SetProperty_State( const bool val , const ParticleProperty & prop, const iNodeBaseWrapper* node_interface /*= nullptr*/ )
{ 
	get_library_sub(EffexLibrary,fx_particle,SetProperty_State,false,fx_particle_lib);
	return get_library_value_3(vlib->fx_particle,EffexParticle,SetProperty_State,val,prop,node_interface); 
}
void FXAPI::FXParticle::SetAge( const int age )
{ 
	get_library_set_sub(EffexLibrary,fx_particle,SetAge,fx_particle_lib);
	get_library_value_1(vlib->fx_particle,EffexParticle,SetAge,age);
}
