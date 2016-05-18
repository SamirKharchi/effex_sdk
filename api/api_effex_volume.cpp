// Copyright (c) All Rights Reserved, Navié
//
// This does not touch the license for the Cinema 4D specific code functions used
// Please see the Cinema 4D license correspondingly. All other rights reserved.
//
// Author: Samir Kharchi
#include "api_effex.h"

extern C4DLibrary* fx_particle_lib;

void NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXVolume::GetBounds( vector3d& ref_minimum, vector3d& ref_maximum )
{
	get_library_set_sub(EffexLibrary,fx_volume,GetBounds,fx_particle_lib);
	get_library_value_2(vlib->fx_volume , VolumeBase , GetBounds,ref_minimum,ref_maximum);
}

bool NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXVolume::Inside( const vector3d& physical_position ) const
{
	get_library_sub(EffexLibrary,fx_volume,Inside,false,fx_particle_lib);
	return get_library_value_1(vlib->fx_volume , VolumeBase , Inside,physical_position);
}

double NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXVolume::GetDistance( const vector3d& physical_position ) const
{
	get_library_sub(EffexLibrary,fx_volume,GetValue,false,fx_particle_lib);
	return get_library_value_1(vlib->fx_volume , VolumeBase , GetValue,physical_position);
}

void NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXVolume::UpdateBounds( void )
{
	get_library_set_sub(EffexLibrary,fx_volume,UpdateBounds,fx_particle_lib);
	get_library_value_0(vlib->fx_volume , VolumeBase , UpdateBounds);
}

bool NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXVolume::IsObstacle( void ) const
{
	get_library_sub(EffexLibrary,fx_volume,IsObstacle,false,fx_particle_lib);
	return get_library_value_0(vlib->fx_volume , VolumeBase , IsObstacle);
}

bool NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXVolume::IsGridObstacle( void ) const
{
	get_library_sub(EffexLibrary,fx_volume,IsGridObstacle,false,fx_particle_lib);
	return get_library_value_0(vlib->fx_volume , VolumeBase , IsGridObstacle);
}

double NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXVolume::GetMaxDistance( void ) const
{
	get_library_sub(EffexLibrary,fx_volume,GetMaxDistance,false,fx_particle_lib);
	return get_library_value_0(vlib->fx_volume , VolumeBase , GetMaxDistance);
}

/*
bool NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXVolume::IsDynamicBody( void ) const
{
	get_library_sub(EffexLibrary,fx_volume,IsDynamicBody,false,fx_particle_lib);
	return get_library_value_0(vlib->fx_volume , VolumeBase , IsDynamicBody);
}

bool NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXVolume::IsKinematicBody( void ) const
{
	get_library_sub(EffexLibrary,fx_volume,IsKinematicBody,false,fx_particle_lib);
	return get_library_value_0(vlib->fx_volume , VolumeBase , IsKinematicBody);
}

bool NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXVolume::IsStaticBody( void ) const
{
	get_library_sub(EffexLibrary,fx_volume,IsStaticBody,false,fx_particle_lib);
	return get_library_value_0(vlib->fx_volume , VolumeBase , IsStaticBody);
}

float NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXVolume::GetDensity( void ) const
{
	get_library_sub(EffexLibrary,fx_volume,GetDensity,false,fx_particle_lib);
	return get_library_value_0(vlib->fx_volume , VolumeBase , GetDensity);
}

float NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXVolume::GetInvMass( void ) const
{
	get_library_sub(EffexLibrary,fx_volume,GetInvMass,false,fx_particle_lib);
	return get_library_value_0(vlib->fx_volume , VolumeBase , GetInvMass);
}

NAVIE_GLOBAL::vector3d NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXVolume::GetInvTensor( void ) const
{
	get_library_sub(EffexLibrary,fx_volume,GetInvTensor,false,fx_particle_lib);
	return get_library_value_0(vlib->fx_volume , VolumeBase , GetInvTensor);
}*/

bool NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXVolume::InsideVolume( const vector3d& physical_position, float offset /*= 0.0f*/ ) const
{
	get_library_sub(EffexLibrary,fx_volume,InsideVolume,false,fx_particle_lib);
	return get_library_value_2(vlib->fx_volume , VolumeBase , InsideVolume,physical_position,offset);
}

double NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXVolume::LinearFalloff( const vector3d& physical_position ) const
{
	get_library_sub(EffexLibrary,fx_volume,LinearFalloff,false,fx_particle_lib);
	return get_library_value_1(vlib->fx_volume , VolumeBase , LinearFalloff, physical_position);
}

bool NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXVolume::ProjectPoint( vector3d &global_physical_position, vector3d &result_grid_position, vector3d& result_coll_normal, double projection /*= 0.001*/ ) const
{
	get_library_sub(EffexLibrary,fx_volume,ProjectPoint,false,fx_particle_lib);
	return get_library_value_4(vlib->fx_volume , VolumeBase , ProjectPoint,global_physical_position,result_grid_position,result_coll_normal,projection);
}

NAVIE_GLOBAL::vector3d NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXVolume::GetNormal( const vector3d& physical_position ) const
{
	get_library_sub(EffexLibrary,fx_volume,GetNormal,vector3d(0.0),fx_particle_lib);
	return get_library_value_1(vlib->fx_volume , VolumeBase , GetNormal, physical_position);
}


/************************************************************************/
/************************************************************************/
NAVIE_GLOBAL::VecInt3D NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXVolumeCellIterator::GetCoordinate( const int cpu )
{
	get_library_sub(EffexLibrary,fx_cvoliterator,GetCoordinate,VecInt3D(0),fx_particle_lib);
	return get_library_value_1(vlib->fx_cvoliterator,VolumeIterator,GetCoordinate,cpu);	
}

Int32_C4D NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXVolumeCellIterator::GetLinearCoordinate( const int cpu )
{
	get_library_sub(EffexLibrary,fx_cvoliterator,GetLinearCoordinate,0,fx_particle_lib);
	return get_library_value_1(vlib->fx_cvoliterator,VolumeIterator,GetLinearCoordinate,cpu);	
}

double NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXVolumeCellIterator::GetValue( const int cpu )
{
	get_library_sub(EffexLibrary,fx_cvoliterator,GetValue,0.0,fx_particle_lib);
	return get_library_value_1(vlib->fx_cvoliterator,VolumeIterator,GetValue,cpu);	
}

double NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXVolumeCellIterator::GetNeighborValue( const int cpu, short x, short y, short z )
{
	get_library_sub(EffexLibrary,fx_cvoliterator,GetNeighborValue,0.0,fx_particle_lib);
	return get_library_value_4(vlib->fx_cvoliterator,VolumeIterator,GetNeighborValue,cpu,x,y,z);
}

bool NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXVolumeCellIterator::Init( FXVolume* channel )
{
	get_library_sub(EffexLibrary,fx_cvoliterator,Init,false,fx_particle_lib);
	return get_library_value_1(vlib->fx_cvoliterator,VolumeIterator,Init,reinterpret_cast<VolumeBase*>(channel));	
}

bool NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXVolumeCellIterator::Init( FXVolume* channel, int cpus, bool include_borders /*= false*/ )
{
	get_library_sub(EffexLibrary,fx_cvoliterator,InitMP,false,fx_particle_lib);
	return get_library_value_3(vlib->fx_cvoliterator,VolumeIterator,InitMP,reinterpret_cast<VolumeBase*>(channel),cpus,include_borders);	
}

void NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXVolumeCellIterator::Start( const int cpu, bool reverse /*= false*/ )
{
	get_library_set_sub(EffexLibrary,fx_cvoliterator,Start,fx_particle_lib);
	get_library_value_2(vlib->fx_cvoliterator,VolumeIterator,Start,cpu,reverse);	
}

bool NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXVolumeCellIterator::SetNext( const int cpu )
{
	get_library_sub(EffexLibrary,fx_cvoliterator,SetNext,false,fx_particle_lib);
	return get_library_value_1(vlib->fx_cvoliterator,VolumeIterator,SetNext,cpu);	
}

bool NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXVolumeCellIterator::SetPrev( const int cpu )
{
	get_library_sub(EffexLibrary,fx_cvoliterator,SetPrev,false,fx_particle_lib);
	return get_library_value_1(vlib->fx_cvoliterator,VolumeIterator,SetPrev,cpu);	
}

void NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXVolumeCellIterator::Offset( Int32_C4D offset )
{
	get_library_set_sub(EffexLibrary,fx_cvoliterator,Offset,fx_particle_lib);
	get_library_value_1(vlib->fx_cvoliterator,VolumeIterator,Offset,offset);	
}

bool NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXVolumeCellIterator::IsValid( void ) const
{
	get_library_sub(EffexLibrary,fx_cvoliterator,IsValid,false,fx_particle_lib);
	return get_library_value_0(vlib->fx_cvoliterator,VolumeIterator,IsValid);	
}

bool NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXVolumeCellIterator::OffsetSafe( Int32_C4D offset )
{
	get_library_sub(EffexLibrary,fx_cvoliterator,OffsetSafe,false,fx_particle_lib);
	return get_library_value_1(vlib->fx_cvoliterator,VolumeIterator,OffsetSafe,offset);	
}

FXAPI::FXVolumeCellIterator* NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXVolumeCellIterator::Alloc()
{
	get_library_sub(EffexLibrary,fx_cvoliterator,Alloc,0,fx_particle_lib);
	return get_library_funcvalue_0_cast(vlib->fx_cvoliterator,FXVolumeCellIterator,Alloc);	
}

void NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXVolumeCellIterator::Free( FXVolumeCellIterator*& p )
{
	get_library_set_sub(EffexLibrary,fx_cvoliterator,Free,fx_particle_lib);    

	VolumeIterator* tmp = (VolumeIterator*) p;
	vlib->fx_cvoliterator->Free(tmp);
	p = nullptr;
}

void NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXVolumeCellIterator::SetValue( const int cpu, const double& value )
{
	get_library_set_sub(EffexLibrary,fx_cvoliterator,SetValue,fx_particle_lib);
	get_library_value_2(vlib->fx_cvoliterator,VolumeIterator,SetValue,cpu,value);	
}

/************************************************************************/
/************************************************************************/

NAVIE_GLOBAL::vector3d NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXMeshIterator::GetVertex()
{
	get_library_sub(EffexLibrary,fx_miterator,GetVertex,vector3d(0.0),fx_particle_lib);
	return get_library_value_0(vlib->fx_miterator,MeshIterator,GetVertex);	
}

NAVIE_GLOBAL::vector3d NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXMeshIterator::GetVertexByIndex( Int32_C4D index )
{
	get_library_sub(EffexLibrary,fx_miterator,GetVertexByIndex,vector3d(0.0),fx_particle_lib);
	return get_library_value_1(vlib->fx_miterator,MeshIterator,GetVertexByIndex,index);	
}

NAVIE_GLOBAL::VecInt3D NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXMeshIterator::GetTriangle()
{
	get_library_sub(EffexLibrary,fx_miterator,GetTriangle,VecInt3D(0),fx_particle_lib);
	return get_library_value_0(vlib->fx_miterator,MeshIterator,GetTriangle);	
}

NAVIE_GLOBAL::VecInt3D NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXMeshIterator::GetTriangleByIndex( Int32_C4D index )
{
	get_library_sub(EffexLibrary,fx_miterator,GetTriangleByIndex,VecInt3D(0),fx_particle_lib);
	return get_library_value_1(vlib->fx_miterator,MeshIterator,GetTriangleByIndex,index);	
}

double NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXMeshIterator::GetProperty_Scalar( const ParticleProperty type, BaseObject* node ) const
{
	get_library_sub(EffexLibrary,fx_miterator,GetProperty_Scalar,0.0,fx_particle_lib);
	return get_library_value_2(vlib->fx_miterator,MeshIterator,GetProperty_Scalar,type,node);
}

NAVIE_GLOBAL::vector3d NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXMeshIterator::GetProperty_Vector( const ParticleProperty type, BaseObject* node ) const
{
	get_library_sub(EffexLibrary,fx_miterator,GetProperty_Vector,vector3d(0.0),fx_particle_lib);
	return get_library_value_2(vlib->fx_miterator,MeshIterator,GetProperty_Vector,type,node);
}

void NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXMeshIterator::SetProperty_Scalar( const double new_value, const ParticleProperty type, BaseObject* node ) const
{
	get_library_set_sub(EffexLibrary,fx_miterator,SetProperty_Scalar,fx_particle_lib);
	get_library_value_3(vlib->fx_miterator,MeshIterator,SetProperty_Scalar,new_value,type,node);
}

void NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXMeshIterator::SetProperty_Vector( const vector3d& new_value, const ParticleProperty type, BaseObject* node ) const
{
	get_library_set_sub(EffexLibrary,fx_miterator,SetProperty_Vector,fx_particle_lib);
	get_library_value_3(vlib->fx_miterator,MeshIterator,SetProperty_Vector,new_value,type,node);
}

bool NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXMeshIterator::Init( FXVolumeMesh* mesh )
{
	get_library_sub(EffexLibrary,fx_miterator,Init,false,fx_particle_lib);
	return get_library_value_1(vlib->fx_miterator,MeshIterator,Init,reinterpret_cast<VolumeMesh*>(mesh));
}

void NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXMeshIterator::Restart( bool tri /*= true*/, bool vert /*= true*/ )
{
	get_library_set_sub(EffexLibrary,fx_miterator,Restart,fx_particle_lib);
	get_library_value_2(vlib->fx_miterator,MeshIterator,Restart,tri,vert);
}

bool NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXMeshIterator::SetNext( bool tri )
{
	get_library_sub(EffexLibrary,fx_miterator,SetNext,false,fx_particle_lib);
	return get_library_value_1(vlib->fx_miterator,MeshIterator,SetNext,tri);
}

bool NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXMeshIterator::SetPrev( bool tri )
{
	get_library_sub(EffexLibrary,fx_miterator,SetPrev,false,fx_particle_lib);
	return get_library_value_1(vlib->fx_miterator,MeshIterator,SetPrev,tri);
}

void NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXMeshIterator::Offset( bool tri, Int32_C4D offset )
{
	get_library_set_sub(EffexLibrary,fx_miterator,Offset,fx_particle_lib);
	get_library_value_2(vlib->fx_miterator,MeshIterator,Offset,tri,offset);
}

bool NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXMeshIterator::IsValid( bool tri ) const
{
	get_library_sub(EffexLibrary,fx_miterator,IsValid,false,fx_particle_lib);
	return get_library_value_1(vlib->fx_miterator,MeshIterator,IsValid,tri);
}

bool NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXMeshIterator::OffsetSafe( bool tri, Int32_C4D offset )
{
	get_library_sub(EffexLibrary,fx_miterator,OffsetSafe,false,fx_particle_lib);
	return get_library_value_2(vlib->fx_miterator,MeshIterator,OffsetSafe,tri,offset);
}

FXAPI::FXMeshIterator* NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXMeshIterator::Alloc()
{
	get_library_sub(EffexLibrary,fx_miterator,Alloc,0,fx_particle_lib);
	return get_library_funcvalue_0_cast(vlib->fx_miterator,FXMeshIterator,Alloc);	
}

void NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXMeshIterator::Free( FXMeshIterator*& p )
{
	get_library_set_sub(EffexLibrary,fx_miterator,Free,fx_particle_lib);    

	MeshIterator* tmp = (MeshIterator*) p;
	vlib->fx_miterator->Free(tmp);
	p = nullptr;
}

/************************************************************************/
/************************************************************************/
/*
BaseObject* NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXVolumeMesh::GetMeshInterface()
{
	get_library_sub(EffexLibrary,fx_volume,GetMeshInterface,nullptr,fx_particle_lib);
	return get_library_value_0(vlib->fx_volume,VolumeMesh,GetMeshInterface);
}

Matrix NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXVolumeMesh::GetMg() const
{
	get_library_sub(EffexLibrary,fx_volume,GetMg,Matrix(),fx_particle_lib);
	return get_library_value_0(vlib->fx_volume,VolumeMesh,GetMg);
}

void NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXVolumeMesh::GetMotion( const vector3d& physical_position, vector3d& linear, vector3d& angular ) const
{
	get_library_set_sub(EffexLibrary,fx_volume,GetMotion,fx_particle_lib);
	get_library_value_3(vlib->fx_volume,VolumeMesh,GetMotion,physical_position,linear,angular);
}*/

Int32_C4D NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::GetTriangleCount( const FXVolumeMesh* meshvolume )
{
	get_library_sub(EffexLibrary,fx_volume,GetTriangleCount,0,fx_particle_lib);
	return get_library_funcvalue_1(vlib->fx_volume,GetTriangleCount,reinterpret_cast<const VolumeMesh*>(meshvolume));
}

Int32_C4D NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::GetVertexCount( const FXVolumeMesh* meshvolume )
{
	get_library_sub(EffexLibrary,fx_volume,GetVertexCount,0,fx_particle_lib);
	return get_library_funcvalue_1(vlib->fx_volume,GetVertexCount,reinterpret_cast<const VolumeMesh*>(meshvolume));
}

bool NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::HasUVdata( const FXVolumeMesh* meshvolume )
{
	get_library_sub(EffexLibrary,fx_volume,HasUVdata,false,fx_particle_lib);
	return get_library_funcvalue_1(vlib->fx_volume,HasUVdata,reinterpret_cast<const VolumeMesh*>(meshvolume));
}

/************************************************************************/
/************************************************************************/
Matrix NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXMesher::GetMg( void ) const
{
	get_library_sub(EffexLibrary,fx_mesher,GetMg,Matrix(),fx_particle_lib);
	return get_library_value_0(vlib->fx_mesher,ImplicitMesher,GetMg);
}

bool NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXMesher::UpdateMesh( void )
{
	get_library_sub(EffexLibrary,fx_mesher,UpdateMesh,false,fx_particle_lib);
	return get_library_value_0(vlib->fx_mesher,ImplicitMesher,UpdateMesh);
}

Int32_C4D NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::GetTriangleCount( const FXMesher* meshvolume )
{
	get_library_sub(EffexLibrary,fx_mesher,GetTriangleCount,0,fx_particle_lib);
	return get_library_funcvalue_1(vlib->fx_mesher,GetTriangleCount,reinterpret_cast<const ImplicitMesher*>(meshvolume));
}

Int32_C4D NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::GetVertexCount( const FXMesher* meshvolume )
{
	get_library_sub(EffexLibrary,fx_mesher,GetVertexCount,0,fx_particle_lib);
	return get_library_funcvalue_1(vlib->fx_mesher,GetVertexCount,reinterpret_cast<const ImplicitMesher*>(meshvolume));
}

bool NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::HasUVdata( const FXMesher* meshvolume )
{
	get_library_sub(EffexLibrary,fx_mesher,HasUVdata,false,fx_particle_lib);
	return get_library_funcvalue_1(vlib->fx_mesher,HasUVdata,reinterpret_cast<const ImplicitMesher*>(meshvolume));
}
