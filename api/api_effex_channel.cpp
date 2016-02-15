// Copyright (c) All Rights Reserved, Navié
//
// This does not touch the license for the Cinema 4D specific code functions used
// Please see the Cinema 4D license correspondingly. All other rights reserved.
//
// Author: Samir Kharchi
#include "api_effex.h"

extern C4DLibrary* fx_particle_lib;

void NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXScalarChannel::UpdateBounds( void )
{
	get_library_set_sub(EffexLibrary,fx_channelscalar,UpdateBounds,fx_particle_lib);
	get_library_value_0(vlib->fx_channelscalar , ChannelScalar , UpdateBounds);
}

double NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXScalarChannel::GetRangeMinimum( void ) const
{
	get_library_sub(EffexLibrary,fx_channelscalar,GetRangeMinimum,0.0,fx_particle_lib);
	return get_library_value_0(vlib->fx_channelscalar,ChannelScalar,GetRangeMinimum);
}

double NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXScalarChannel::GetRangeMaximum( void ) const
{
	get_library_sub(EffexLibrary,fx_channelscalar,GetRangeMaximum,0.0,fx_particle_lib);
	return get_library_value_0(vlib->fx_channelscalar,ChannelScalar,GetRangeMaximum);
}

double NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXScalarChannel::GetResetValue( void ) const
{
	get_library_sub(EffexLibrary,fx_channelscalar,GetResetValue,0.0,fx_particle_lib);
	return get_library_value_0(vlib->fx_channelscalar,ChannelScalar,GetResetValue);
}

void NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXScalarChannel::GetBounds( vector3d& ref_minimum, vector3d& ref_maximum )
{
	get_library_set_sub(EffexLibrary,fx_channelscalar,GetBounds,fx_particle_lib);
	get_library_value_2(vlib->fx_channelscalar,ChannelScalar,GetBounds,ref_minimum,ref_maximum);
}

bool NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXScalarChannel::Inside( const vector3d& physical_position , const bool excludeborders)
{
	get_library_sub(EffexLibrary,fx_channelscalar,Inside,false,fx_particle_lib);
	return get_library_value_2(vlib->fx_channelscalar,ChannelScalar,Inside,physical_position,excludeborders);
}

bool NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXScalarChannel::InsideGrid( const vector3d& physical_position, const bool excludeborders /*= false*/ )
{
	get_library_sub(EffexLibrary,fx_channelscalar,InsideGrid,false,fx_particle_lib);
	return get_library_value_2(vlib->fx_channelscalar,ChannelScalar,InsideGrid,physical_position,excludeborders);
}

double NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXScalarChannel::GetValue( const vector3d& physical_position ) const
{
	get_library_sub(EffexLibrary,fx_channelscalar,GetValue,false,fx_particle_lib);
	return get_library_value_1(vlib->fx_channelscalar,ChannelScalar,GetValue,physical_position);
}

bool NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXScalarChannel::Resize( vector3d& ref_minimum, vector3d& ref_maximum )
{
	get_library_sub(EffexLibrary,fx_channelscalar,Resize,false,fx_particle_lib);
	return get_library_value_2(vlib->fx_channelscalar,ChannelScalar,Resize,ref_minimum,ref_maximum);
}

void NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXScalarChannel::SetValue( const vector3d& physical_position, const double value )
{
	get_library_set_sub(EffexLibrary,fx_channelscalar,SetValue,fx_particle_lib);
	get_library_value_2(vlib->fx_channelscalar,ChannelScalar,SetValue,physical_position,value);
}

/************************************************************************/
/************************************************************************/

const NAVIE_GLOBAL::vector3d& NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXVectorChannel::GetRangeMinimum( void ) const
{
	get_library_sub(EffexLibrary,fx_channelvector,GetRangeMinimum,zerovector,fx_particle_lib);
	return get_library_value_0(vlib->fx_channelvector,ChannelVector,GetRangeMinimum);
}

const NAVIE_GLOBAL::vector3d& NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXVectorChannel::GetRangeMaximum( void ) const
{
	get_library_sub(EffexLibrary,fx_channelvector,GetRangeMaximum,zerovector,fx_particle_lib);
	return get_library_value_0(vlib->fx_channelvector,ChannelVector,GetRangeMaximum);
}

const NAVIE_GLOBAL::vector3d& NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXVectorChannel::GetResetValue( void ) const
{
	get_library_sub(EffexLibrary,fx_channelvector,GetResetValue,zerovector,fx_particle_lib);
	return get_library_value_0(vlib->fx_channelvector,ChannelVector,GetResetValue);
}

void NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXVectorChannel::GetBounds( vector3d& ref_minimum, vector3d& ref_maximum )
{
	get_library_set_sub(EffexLibrary,fx_channelvector,GetBounds,fx_particle_lib);
	get_library_value_2(vlib->fx_channelvector,ChannelVector,GetBounds,ref_minimum,ref_maximum);
}

bool NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXVectorChannel::Inside( const vector3d& physical_position, const bool excludeborders )
{
	get_library_sub(EffexLibrary,fx_channelvector,Inside,false,fx_particle_lib);
	return get_library_value_2(vlib->fx_channelvector,ChannelVector,Inside,physical_position,excludeborders);
}

bool NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXVectorChannel::InsideGrid( const vector3d& physical_position, const bool excludeborders /*= false*/ )
{
	get_library_sub(EffexLibrary,fx_channelvector,InsideGrid,false,fx_particle_lib);
	return get_library_value_2(vlib->fx_channelvector,ChannelVector,InsideGrid,physical_position,excludeborders);
}

NAVIE_GLOBAL::vector3d NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXVectorChannel::GetValue( const vector3d& physical_position ) const
{
	get_library_sub(EffexLibrary,fx_channelvector,GetValue,vector3d(0.0),fx_particle_lib);
	return get_library_value_1(vlib->fx_channelvector,ChannelVector,GetValue,physical_position);
}

bool NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXVectorChannel::Resize( vector3d& ref_minimum, vector3d& ref_maximum )
{
	get_library_sub(EffexLibrary,fx_channelvector,Resize,false,fx_particle_lib);
	return get_library_value_2(vlib->fx_channelvector,ChannelVector,Resize,ref_minimum,ref_maximum);
}

void NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXVectorChannel::SetValue( const vector3d& physical_position, const vector3d& value )
{
	get_library_set_sub(EffexLibrary,fx_channelvector,SetValue,fx_particle_lib);
	get_library_value_2(vlib->fx_channelvector,ChannelVector,SetValue,physical_position,value);
}

void NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXVectorChannel::UpdateBounds( void )
{
	get_library_set_sub(EffexLibrary,fx_channelvector,UpdateBounds,fx_particle_lib);
	get_library_value_0(vlib->fx_channelvector,ChannelVector,UpdateBounds);
}

/************************************************************************/
/************************************************************************/

double NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXFuelChannel::GetIgnitionTemperature() const
{
	get_library_sub(EffexLibrary,fx_channelscalar,GetIgnitionTemperature,600.0,fx_particle_lib);
	return get_library_value_0(vlib->fx_channelscalar,ChannelFuel,GetIgnitionTemperature);
}
/************************************************************************/
/************************************************************************/

double NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXFireChannel::GetCoolingPoint() const
{
	get_library_sub(EffexLibrary,fx_channelscalar,GetCoolingPoint,600.0,fx_particle_lib);
	return get_library_value_0(vlib->fx_channelscalar,ChannelFire,GetCoolingPoint);
}

double NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXFireChannel::GetDeathRate() const
{
	get_library_sub(EffexLibrary,fx_channelscalar,GetDeathRate,0.3,fx_particle_lib);
	return get_library_value_0(vlib->fx_channelscalar,ChannelFire,GetDeathRate);
}

double NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXFireChannel::GetAfterLife() const
{
	get_library_sub(EffexLibrary,fx_channelscalar,GetAfterLife,0.1,fx_particle_lib);
	return get_library_value_0(vlib->fx_channelscalar,ChannelFire,GetAfterLife);
}

/************************************************************************/
/************************************************************************/
double default_zero = 0.0;

double NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXScalarCellIterator::GetValue( const int cpu )
{
	get_library_sub(EffexLibrary,fx_csiterator,GetValue,default_zero,fx_particle_lib);
	return get_library_value_1(vlib->fx_csiterator,ScalarIterator,GetValue,cpu);	
}

double NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXScalarCellIterator::GetNeighborValue( const int cpu, short x, short y, short z )
{
	get_library_sub(EffexLibrary,fx_csiterator,GetNeighborValue,default_zero,fx_particle_lib);
	return get_library_value_4(vlib->fx_csiterator,ScalarIterator,GetNeighborValue,cpu,x,y,z);
}

bool NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXScalarCellIterator::Init( FXScalarChannel* channel )
{
	get_library_sub(EffexLibrary,fx_csiterator,Init,false,fx_particle_lib);
	return get_library_value_1(vlib->fx_csiterator,ScalarIterator,Init,reinterpret_cast<ChannelScalar*>(channel));	
}

bool NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXScalarCellIterator::Init( FXScalarChannel* channel, int cpus, bool include_borders /*= false*/ )
{
	get_library_sub(EffexLibrary,fx_csiterator,InitMP,false,fx_particle_lib);
	return get_library_value_3(vlib->fx_csiterator,ScalarIterator,InitMP,reinterpret_cast<ChannelScalar*>(channel),cpus,include_borders);	
}

void NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXScalarCellIterator::Start( const int cpu, bool reverse /*= false*/ )
{
	get_library_set_sub(EffexLibrary,fx_csiterator,Start,fx_particle_lib);
	get_library_value_2(vlib->fx_csiterator,ScalarIterator,Start,cpu,reverse);	
}

bool NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXScalarCellIterator::SetNext( const int cpu )
{
	get_library_sub(EffexLibrary,fx_csiterator,SetNext,false,fx_particle_lib);
	return get_library_value_1(vlib->fx_csiterator,ScalarIterator,SetNext,cpu);	
}

bool NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXScalarCellIterator::SetPrev( const int cpu )
{
	get_library_sub(EffexLibrary,fx_csiterator,SetPrev,false,fx_particle_lib);
	return get_library_value_1(vlib->fx_csiterator,ScalarIterator,SetPrev,cpu);	
}

void NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXScalarCellIterator::Offset( Int32_C4D offset )
{
	get_library_set_sub(EffexLibrary,fx_csiterator,Offset,fx_particle_lib);
	get_library_value_1(vlib->fx_csiterator,ScalarIterator,Offset,offset);	
}

bool NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXScalarCellIterator::IsValid( void ) const
{
	get_library_sub(EffexLibrary,fx_csiterator,IsValid,false,fx_particle_lib);
	return get_library_value_0(vlib->fx_csiterator,ScalarIterator,IsValid);	
}

bool NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXScalarCellIterator::OffsetSafe( Int32_C4D offset )
{
	get_library_sub(EffexLibrary,fx_csiterator,OffsetSafe,false,fx_particle_lib);
	return get_library_value_1(vlib->fx_csiterator,ScalarIterator,OffsetSafe,offset);	
}

FXAPI::FXScalarCellIterator* NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXScalarCellIterator::Alloc()
{
	get_library_sub(EffexLibrary,fx_csiterator,Alloc,0,fx_particle_lib);
	return get_library_funcvalue_0_cast(vlib->fx_csiterator,FXScalarCellIterator,Alloc);	
}

void NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXScalarCellIterator::Free( FXScalarCellIterator*& p )
{
	get_library_set_sub(EffexLibrary,fx_csiterator,Free,fx_particle_lib);    

	ScalarIterator* tmp = (ScalarIterator*) p;
	vlib->fx_csiterator->Free(tmp);
	p = nullptr;
}

void NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXScalarCellIterator::SetValue( const int cpu, const double& value )
{
	get_library_set_sub(EffexLibrary,fx_csiterator,SetValue,fx_particle_lib);
	get_library_value_2(vlib->fx_csiterator,ScalarIterator,SetValue,cpu,value);	
}


/************************************************************************/
/************************************************************************/
NAVIE_GLOBAL::vector3d NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXVectorCellIterator::GetValue( const int cpu )
{
	get_library_sub(EffexLibrary,fx_cviterator,GetValue,vector3d(default_zero),fx_particle_lib);
	return get_library_value_1(vlib->fx_cviterator,VectorIterator,GetValue,cpu);	
}

void NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXVectorCellIterator::SetValue( const int cpu, const NAVIE_GLOBAL::vector3d& value )
{
	get_library_set_sub(EffexLibrary,fx_cviterator,SetValue,fx_particle_lib);
	get_library_value_2(vlib->fx_cviterator,VectorIterator,SetValue,cpu,value);	
}

NAVIE_GLOBAL::vector3d NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXVectorCellIterator::GetNeighborValue( const int cpu, short x, short y, short z )
{
	get_library_sub(EffexLibrary,fx_cviterator,GetNeighborValue,vector3d(default_zero),fx_particle_lib);
	return get_library_value_4(vlib->fx_cviterator,VectorIterator,GetNeighborValue,cpu,x,y,z);
}

bool NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXVectorCellIterator::Init( FXVectorChannel* channel )
{
	get_library_sub(EffexLibrary,fx_cviterator,Init,false,fx_particle_lib);
	return get_library_value_1(vlib->fx_cviterator,VectorIterator,Init,reinterpret_cast<ChannelVector*>(channel));	
}

bool NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXVectorCellIterator::Init( FXVectorChannel* channel, int cpus, bool include_borders /*= false*/ )
{
	get_library_sub(EffexLibrary,fx_cviterator,InitMP,false,fx_particle_lib);
	return get_library_value_3(vlib->fx_cviterator,VectorIterator,InitMP,reinterpret_cast<ChannelVector*>(channel),cpus,include_borders);	
}

void NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXVectorCellIterator::Start( const int cpu, bool reverse /*= false*/ )
{
	get_library_set_sub(EffexLibrary,fx_cviterator,Start,fx_particle_lib);
	get_library_value_2(vlib->fx_cviterator,VectorIterator,Start,cpu,reverse);	
}

bool NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXVectorCellIterator::SetNext( const int cpu )
{
	get_library_sub(EffexLibrary,fx_cviterator,SetNext,false,fx_particle_lib);
	return get_library_value_1(vlib->fx_cviterator,VectorIterator,SetNext,cpu);	
}

bool NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXVectorCellIterator::SetPrev( const int cpu )
{
	get_library_sub(EffexLibrary,fx_cviterator,SetPrev,false,fx_particle_lib);
	return get_library_value_1(vlib->fx_cviterator,VectorIterator,SetPrev,cpu);	
}

void NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXVectorCellIterator::Offset( Int32_C4D offset )
{
	get_library_set_sub(EffexLibrary,fx_cviterator,Offset,fx_particle_lib);
	get_library_value_1(vlib->fx_cviterator,VectorIterator,Offset,offset);	
}

bool NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXVectorCellIterator::IsValid( void ) const
{
	get_library_sub(EffexLibrary,fx_cviterator,IsValid,false,fx_particle_lib);
	return get_library_value_0(vlib->fx_cviterator,VectorIterator,IsValid);	
}

bool NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXVectorCellIterator::OffsetSafe( Int32_C4D offset )
{
	get_library_sub(EffexLibrary,fx_cviterator,OffsetSafe,false,fx_particle_lib);
	return get_library_value_1(vlib->fx_cviterator,VectorIterator,OffsetSafe,offset);	
}

FXAPI::FXVectorCellIterator* NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXVectorCellIterator::Alloc()
{
	get_library_sub(EffexLibrary,fx_cviterator,Alloc,0,fx_particle_lib);
	return get_library_funcvalue_0_cast(vlib->fx_cviterator,FXVectorCellIterator,Alloc);	
}

void NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API::FXVectorCellIterator::Free( FXVectorCellIterator*& p )
{
	get_library_set_sub(EffexLibrary,fx_cviterator,Free,fx_particle_lib);    

	VectorIterator* tmp = (VectorIterator*) p;
	vlib->fx_cviterator->Free(tmp);
	p = nullptr;
}
