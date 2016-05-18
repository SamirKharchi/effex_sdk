// Copyright (c) All Rights Reserved, Navié
//
// This does not touch the license for the Cinema 4D specific code functions used
// Please see the Cinema 4D license correspondingly. All other rights reserved.
//
// Author: Samir Kharchi
#include "api_effex.h"

C4DLibrary* fx_particle_lib = nullptr;

Bool FXAPI::InitEffex(void)
{
	return nullptr != CheckLib(EFFEXPARTICLE_LIBID, 0, &fx_particle_lib);
}

/* Function Library */
void NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::PhysicalToWorld( FXScene* scene, vector3d& physical_position )
{
	get_library_set(EffexLibrary,PhysicalToWorld,fx_particle_lib);
	get_library_funcvalue_2(vlib,PhysicalToWorld,reinterpret_cast<NAVIE_GLOBAL::NAVIE_EFFEX::Scene*>(scene),physical_position); 
}

void NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::WorldToPhysical( FXScene* scene, vector3d& world_position )
{
	get_library_set(EffexLibrary,WorldToPhysical,fx_particle_lib);
	get_library_funcvalue_2(vlib,WorldToPhysical,reinterpret_cast<NAVIE_GLOBAL::NAVIE_EFFEX::Scene*>(scene),world_position); 
}

bool NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::GridToWorld(FXBase* channel, const NAVIE_GLOBAL::VecInt3D& grid_pos, vector3d& world_position, bool local)
{
	get_library(EffexLibrary,GridToWorld,false,fx_particle_lib);
	return get_library_funcvalue_4(vlib,GridToWorld,reinterpret_cast<NAVIE_GLOBAL::NAVIE_EFFEX::iBase*>(channel),grid_pos,world_position,local); 
}

bool NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::GridToPhysical(FXBase* channel, const NAVIE_GLOBAL::VecInt3D& grid_pos, vector3d& physical_position, bool local)
{
	get_library(EffexLibrary,GridToPhysical,false,fx_particle_lib);
	return get_library_funcvalue_4(vlib,GridToPhysical,reinterpret_cast<NAVIE_GLOBAL::NAVIE_EFFEX::iBase*>(channel),grid_pos,physical_position,local); 
}

bool NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::WorldToGrid(FXBase* channel, NAVIE_GLOBAL::vector3d world_pos, NAVIE_GLOBAL::VecInt3D& grid_pos, bool local)
{
	get_library(EffexLibrary,WorldToGrid,false,fx_particle_lib);
	return get_library_funcvalue_4(vlib,WorldToGrid,reinterpret_cast<NAVIE_GLOBAL::NAVIE_EFFEX::iBase*>(channel),world_pos,grid_pos,local); 
}

bool NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::PhysicalToGrid(FXBase* channel, NAVIE_GLOBAL::vector3d physical_pos, NAVIE_GLOBAL::VecInt3D& grid_pos, bool local)
{
	get_library(EffexLibrary,PhysicalToGrid,false,fx_particle_lib);
	return get_library_funcvalue_4(vlib,WorldToGrid,reinterpret_cast<NAVIE_GLOBAL::NAVIE_EFFEX::iBase*>(channel),physical_pos,grid_pos,local); 
}

void NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::HandleInexcludeBits(InExcludeData* include, std::vector<Int32>& oldflags)
{
	get_library_set(EffexLibrary,HandleInexcludeBits,fx_particle_lib);
	get_library_funcvalue_2(vlib,HandleInexcludeBits,include,oldflags);
}

bool NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::OpenCandidatePopup( bool is_node_group, std::vector<FXBase*>& items, FXTypeInfos& types, BaseObject* caller, Int32_C4D linkfield_id, bool is_inexclude, bool create_menu, Int32_C4D inex_flags )
{
	get_library(EffexLibrary,OpenCandidatePopup,false,fx_particle_lib);
	return get_library_funcvalue_8(vlib,OpenCandidatePopup,is_node_group,reinterpret_cast< std::vector<iBase*>& >(items),types,caller,linkfield_id,is_inexclude,create_menu,inex_flags); 
}

FXAPI::FXBase* NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::GetNode( FXScene* scene, BaseObject* node, NodeRetrieveType type )
{
	get_library(EffexLibrary,GetNode,nullptr,fx_particle_lib);
	return get_library_funcvalue_3_cast(vlib,FXBase,GetNode,reinterpret_cast<NAVIE_GLOBAL::NAVIE_EFFEX::Scene*>(scene),node,type); 
}

void NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::GetNodes( FXScene* scene, InExcludeData* filter, std::vector<FXBase*>& result, NodeRetrieveType type )
{
	get_library_set(EffexLibrary,GetNodes,fx_particle_lib);
	return get_library_funcvalue_4(vlib,GetNodes,reinterpret_cast<NAVIE_GLOBAL::NAVIE_EFFEX::Scene*>(scene),filter,reinterpret_cast< std::vector<iBase*>& >(result),type); 
}

NAVIE_GLOBAL::NAVIE_EFFEX::iNodeBaseWrapper* NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::CreateWrapper(BaseObject* op )
{
	get_library(EffexLibrary,CreateWrapper,nullptr,fx_particle_lib);
	return get_library_funcvalue_1(vlib,CreateWrapper,op); 
}

void NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::DeleteWrapper(NAVIE_GLOBAL::NAVIE_EFFEX::iNodeBaseWrapper*& ptr_wrapper )
{
	get_library_set(EffexLibrary,DeleteWrapper,fx_particle_lib);
	return get_library_funcvalue_1(vlib,DeleteWrapper,ptr_wrapper); 
}

void NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::UpdateWrapper(iNodeBaseWrapper* ptr_wrapper, BaseObject* op)
{
	get_library_set(EffexLibrary,UpdateWrapper,fx_particle_lib);
	return get_library_funcvalue_2(vlib,UpdateWrapper,ptr_wrapper,op); 
}
