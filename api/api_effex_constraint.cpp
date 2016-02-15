// Copyright (c) All Rights Reserved, Navié
//
// This does not touch the license for the Cinema 4D specific code functions used
// Please see the Cinema 4D license correspondingly. All other rights reserved.
//
// Author: Samir Kharchi
#include "api_effex.h"

extern C4DLibrary* fx_particle_lib;

bool FXAPI::FXConstraint::IsInverted( void ) const
{
	get_library_sub(EffexLibrary,fx_constraint,IsInverted,false,fx_particle_lib);
	return get_library_value_0(vlib->fx_constraint,Constraint,IsInverted);
}

bool FXAPI::FXConstraint::IsParticleConstraint( void ) const
{
	get_library_sub(EffexLibrary,fx_constraint,IsParticleConstraint,false,fx_particle_lib);
	return get_library_value_0(vlib->fx_constraint,Constraint,IsParticleConstraint);
}

bool FXAPI::FXConstraint::GetConstraint( const vector3d& position, double& src_value, int blendmode, void* local_data, int cpu /*= 0*/ )
{
	get_library_sub(EffexLibrary,fx_constraint,GetConstraint,false,fx_particle_lib);
	return get_library_value_5(vlib->fx_constraint,Constraint,GetConstraint,position,src_value,blendmode,local_data,cpu);
}

bool FXAPI::FXConstraint::GetConstraintParticle( const vector3d& position, double& src_value, int blendmode, void* local_data, int cpu /*= 0*/, const void* t_particle /*= nullptr*/ )
{
	get_library_sub(EffexLibrary,fx_constraint,GetConstraintParticle,false,fx_particle_lib);
	return get_library_value_6(vlib->fx_constraint,Constraint,GetConstraintParticle,position,src_value,blendmode,local_data,cpu,t_particle);
}

