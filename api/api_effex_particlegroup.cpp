// Copyright (c) All Rights Reserved, Navié
//
// This does not touch the license for the Cinema 4D specific code functions used
// Please see the Cinema 4D license correspondingly. All other rights reserved.
//
// Author: Samir Kharchi
#include "api_effex.h"

extern C4DLibrary* fx_particle_lib;

FXAPI::FXParticle* FXAPI::FXParticleGroup::GetParticle( Int32_C4D index, ParticleFactoryTypes subgroup )
{
	get_library_sub(EffexLibrary,fx_pgroup,GetParticle,nullptr,fx_particle_lib);
	return get_library_value_2_cast(vlib->fx_pgroup,ParticleGroup,FXParticle,GetParticle,index,subgroup);
}

FXAPI::FXParticle* FXAPI::FXParticleGroup::AddParticle( ParticleFactoryTypes subgroup, bool multithreaded)
{
	get_library_sub(EffexLibrary,fx_pgroup,AddParticle,nullptr,fx_particle_lib);
	return get_library_value_2_cast(vlib->fx_pgroup,ParticleGroup,FXParticle,AddParticle,subgroup,multithreaded);
}

Int32_C4D FXAPI::FXParticleGroup::GetParticleCount( ParticleFactoryTypes subgroup )
{
	get_library_sub(EffexLibrary,fx_pgroup,GetParticleCount,0,fx_particle_lib);
	return get_library_value_1(vlib->fx_pgroup,ParticleGroup,GetParticleCount,subgroup);
}

void FXAPI::FXParticleGroup::FindNeighbors( ParticleFactoryTypes subgroup, const vector3d& global_position, const double radius, std::vector<NAVIE_GLOBAL::NeighborData>& neighbors, const int cpu )
{
	get_library_set_sub(EffexLibrary,fx_pgroup,ComputeNeighbors,fx_particle_lib);
	get_library_value_5(vlib->fx_pgroup,ParticleGroup,ComputeNeighbors,subgroup,global_position,radius,neighbors,cpu);

}

void FXAPI::FXParticleGroup::SetDirtySearch( const ParticleFactoryTypes subgroup )
{
	get_library_set_sub(EffexLibrary,fx_pgroup,SetDirtySearch,fx_particle_lib);
	get_library_value_1(vlib->fx_pgroup,ParticleGroup,SetDirtySearch,subgroup);
}

void NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXParticleGroup::UpdateBounds( void )
{
	get_library_set_sub(EffexLibrary,fx_pgroup,UpdateBounds,fx_particle_lib);
	get_library_value_0(vlib->fx_pgroup,ParticleGroup,UpdateBounds);
}

/************************************************************************/
/* Particle Iterator */
FXAPI::FXParticle* FXAPI::FXParticleIterator::GetParticle(const int cpu)
{
	get_library_sub(EffexLibrary,fx_piterator,GetParticle,nullptr,fx_particle_lib);
	return get_library_value_1_cast(vlib->fx_piterator,NAVIE_GLOBAL::NAVIE_EFFEX::ParticleIterator,FXParticle,GetParticle,cpu);	
}

FXAPI::FXParticle* FXAPI::FXParticleIterator::GetFirstParticle(const int cpu)
{
	get_library_sub(EffexLibrary,fx_piterator,GetFirstParticle,0,fx_particle_lib);
	return get_library_value_1_cast(vlib->fx_piterator,NAVIE_GLOBAL::NAVIE_EFFEX::ParticleIterator,FXParticle,GetFirstParticle,cpu);	
}

FXAPI::FXParticle* FXAPI::FXParticleIterator::GetLastParticle(const int cpu)
{
	get_library_sub(EffexLibrary,fx_piterator,GetLastParticle,0,fx_particle_lib);
	return get_library_value_1_cast(vlib->fx_piterator,NAVIE_GLOBAL::NAVIE_EFFEX::ParticleIterator,FXParticle,GetLastParticle,cpu);	
}

bool FXAPI::FXParticleIterator::Init( FXParticleGroup* group, const ParticleFactoryTypes m_factory , const int cpus)
{
	get_library_sub(EffexLibrary,fx_piterator,Init,false,fx_particle_lib);
	return get_library_value_3(vlib->fx_piterator,NAVIE_GLOBAL::NAVIE_EFFEX::ParticleIterator,Init,(NAVIE_GLOBAL::NAVIE_EFFEX::ParticleGroup*)group,m_factory,cpus);	
}

void FXAPI::FXParticleIterator::Restart( const int cpu )
{
	get_library_set_sub(EffexLibrary,fx_piterator,Restart,fx_particle_lib);
	get_library_value_1(vlib->fx_piterator,NAVIE_GLOBAL::NAVIE_EFFEX::ParticleIterator,Restart,cpu);	
}

bool FXAPI::FXParticleIterator::SetNext( const int cpu )
{
	get_library_sub(EffexLibrary,fx_piterator,SetNext,false,fx_particle_lib);
	return get_library_value_1(vlib->fx_piterator,NAVIE_GLOBAL::NAVIE_EFFEX::ParticleIterator,SetNext,cpu);	
}

bool FXAPI::FXParticleIterator::SetPrev( const int cpu )
{
	get_library_sub(EffexLibrary,fx_piterator,SetPrev,false,fx_particle_lib);
	return get_library_value_1(vlib->fx_piterator,NAVIE_GLOBAL::NAVIE_EFFEX::ParticleIterator,SetPrev,cpu);	
}

void FXAPI::FXParticleIterator::Offset( const int cpu, Int32_C4D offset )
{
	get_library_set_sub(EffexLibrary,fx_piterator,Offset,fx_particle_lib);
	get_library_value_2(vlib->fx_piterator,NAVIE_GLOBAL::NAVIE_EFFEX::ParticleIterator,Offset,cpu,offset);	
}

bool FXAPI::FXParticleIterator::OffsetSafe( const int cpu, Int32_C4D offset )
{
	get_library_sub(EffexLibrary,fx_piterator,OffsetSafe,false,fx_particle_lib);
	return get_library_value_2(vlib->fx_piterator,NAVIE_GLOBAL::NAVIE_EFFEX::ParticleIterator,OffsetSafe,cpu,offset);	
}

bool FXAPI::FXParticleIterator::IsValid( const int cpu ) const
{
	get_library_sub(EffexLibrary,fx_piterator,IsValid,false,fx_particle_lib);
	return get_library_value_1(vlib->fx_piterator,NAVIE_GLOBAL::NAVIE_EFFEX::ParticleIterator,IsValid,cpu);	
}

FXAPI::FXParticleIterator* FXAPI::FXParticleIterator::Alloc()
{
	get_library_sub(EffexLibrary,fx_piterator,Alloc,0,fx_particle_lib);
	return get_library_funcvalue_0_cast(vlib->fx_piterator,FXParticleIterator,Alloc);	
}

void FXAPI::FXParticleIterator::Free( FXParticleIterator*& p )
{
	get_library_set_sub(EffexLibrary,fx_piterator,Free,fx_particle_lib);    
	
	NAVIE_GLOBAL::NAVIE_EFFEX::ParticleIterator* tmp = (NAVIE_GLOBAL::NAVIE_EFFEX::ParticleIterator*) p;
	vlib->fx_piterator->Free(tmp);
	p = nullptr;
}
