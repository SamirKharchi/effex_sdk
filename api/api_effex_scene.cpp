// Copyright (c) All Rights Reserved, Navié
//
// This does not touch the license for the Cinema 4D specific code functions used
// Please see the Cinema 4D license correspondingly. All other rights reserved.
//
// Author: Samir Kharchi
#include "api_effex.h"

extern C4DLibrary* fx_particle_lib;


/************************************************************************/
FXAPI::FXServer* FXAPI::FXServer::Get(BaseDocument* doc)
{
	return static_cast<FXServer*>(doc->FindSceneHook(EFFEX_SERVER));
}
/************************************************************************/
/* Server */
const int FXAPI::FXServer::GetSceneCount() const
{
	get_library_sub(EffexLibrary,fx_server,GetSceneCount,0,fx_particle_lib);
	return get_library_internalvalue_0(vlib->fx_server,const EffexHook,GetNodeData(),GetSceneCount);
}

FXAPI::FXScene* FXAPI::FXServer::GetEffexScene( BaseObject* node )
{
	get_library_sub(EffexLibrary,fx_server,GetEffexScene,0,fx_particle_lib);
	return get_library_internalvalue_1_cast(vlib->fx_server,EffexHook,GetNodeData(),FXAPI::FXScene,GetEffexScene,node);
}

FXAPI::FXScene* FXAPI::FXServer::GetEffexScene( iNodeBaseWrapper* node )
{
	get_library_sub(EffexLibrary,fx_server,nvGetEffexScene,0,fx_particle_lib);
	return get_library_internalvalue_1_cast(vlib->fx_server,EffexHook,GetNodeData(),FXAPI::FXScene,nvGetEffexScene,node);
}

const int FXAPI::FXServer::GetActiveSceneCount() const
{
	get_library_sub(EffexLibrary,fx_server,GetActiveSceneCount,0,fx_particle_lib);
	return get_library_internalvalue_0(vlib->fx_server,const EffexHook,GetNodeData(),GetActiveSceneCount);
}

FXAPI::FXParticleGroup* FXAPI::FXServer::GetParticleGroup( iNodeBaseWrapper* node )
{
	get_library_sub(EffexLibrary,fx_server,GetParticleGroup,0,fx_particle_lib);
	return get_library_internalvalue_1_cast(vlib->fx_server,EffexHook,GetNodeData(),FXAPI::FXParticleGroup,GetParticleGroup,node);
}

const FXAPI::FXParticleGroup* FXAPI::FXServer::GetParticleGroup( iNodeBaseWrapper* node ) const
{
	get_library_sub(EffexLibrary,fx_server,GetParticleGroup,0,fx_particle_lib);
	return get_library_internalvalue_1_cast(vlib->fx_server,EffexHook,GetNodeData(),const FXAPI::FXParticleGroup,GetParticleGroupR,node);
}

void NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXServer::GetConstraints( iLinkList* filter, std::vector<FXConstraint*>& result )
{
	get_library_set_sub(EffexLibrary,fx_server,GetConstraints,fx_particle_lib);
	get_library_internalvalue_2(vlib->fx_server,EffexHook,GetNodeData(),GetConstraints,filter,reinterpret_cast<std::vector<Constraint*>&>(result));
}

/************************************************************************/
/* Scene */
iNodeBaseWrapper* FXAPI::FXScene::GetInterface()
{
	get_library_sub(EffexLibrary,fx_scene,GetInterface,0,fx_particle_lib);
	return get_library_value_0(vlib->fx_scene,Scene,GetInterface);
}

int FXAPI::FXScene::GetCPUCount( void ) const
{
	get_library_sub(EffexLibrary,fx_scene,GetCPUCount,0,fx_particle_lib);
	return get_library_value_0(vlib->fx_scene,Scene,GetCPUCount);
}

bool FXAPI::FXScene::IsActive( void ) const
{
	get_library_sub(EffexLibrary,fx_scene,IsActive,0,fx_particle_lib);
	return get_library_value_0(vlib->fx_scene,Scene,IsActive);
}

const NAVIE_GLOBAL::vector3d& FXAPI::FXScene::GetGravity( void ) const
{
	get_library_sub(EffexLibrary,fx_scene,GetGravity,zerovector,fx_particle_lib);
	return get_library_value_0(vlib->fx_scene,Scene,GetGravity);
}

const NAVIE_GLOBAL::NAVIE_EFFEX::SimulationInfo* FXAPI::FXScene::GetSimulationInfo( void ) const
{
	get_library_sub(EffexLibrary,fx_scene,GetSimulationInfo,nullptr,fx_particle_lib);
	return get_library_value_0(vlib->fx_scene,Scene,GetSimulationInfo);
}
