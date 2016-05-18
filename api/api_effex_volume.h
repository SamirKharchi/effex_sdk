// Copyright (c) All Rights Reserved, Navié
//
// This does not touch the license for the Cinema 4D specific code functions used
// Please see the Cinema 4D license correspondingly. All other rights reserved.
//
// Author: Samir Kharchi
#ifndef API_EFFEX_VOLUME_H
#define API_EFFEX_VOLUME_H

#include "api_effex_base.h"

namespace NAVIE_GLOBAL
{
	namespace NAVIE_EFFEX
	{		
		namespace NAVIE_API
		{			
			class FXVolume : public FXBase
			{
			public:
				void		GetBounds		(vector3d& ref_minimum, vector3d& ref_maximum);
				bool		Inside			(const vector3d& physical_position) const;
				bool		InsideVolume	(const vector3d& physical_position, float offset = 0.0f) const;
				void		UpdateBounds	(void);

				double		GetDistance		(const vector3d& physical_position) const;
				double		GetMaxDistance	(void) const;
				float		GetDensity		(void) const;
				float		GetInvMass		(void) const;
				vector3d	GetInvTensor	(void) const;

				bool		IsObstacle		(void) const;
				bool		IsGridObstacle	(void) const;
				bool		IsDynamicBody	(void) const;
				bool		IsKinematicBody	(void) const;
				bool		IsStaticBody	(void) const;

				vector3d	GetNormal		(const vector3d& physical_position) const;
				double		LinearFalloff	(const vector3d& physical_position) const;
				bool		ProjectPoint	(vector3d &global_physical_position, vector3d &result_grid_position, vector3d& result_coll_normal, double projection = 0.001) const;				
			};

			class FXVolumeCellIterator
			{
			public:
				VecInt3D	GetCoordinate	(const int cpu) ;
				Int32_C4D	GetLinearCoordinate(const int cpu) ;
				double		GetValue		(const int cpu) ;
				double		GetNeighborValue(const int cpu, short x, short y, short z);
				void		SetValue		(const int cpu, const double& value) ;

				bool		Init			(FXVolume* channel);
				bool		Init			(FXVolume* channel, int cpus, bool include_borders = false);

				void Start			(const int cpu, bool reverse = false) ;
				bool SetNext			(const int cpu) ;
				bool SetPrev			(const int cpu) ;

				void Offset			(Int32_C4D offset);
				bool IsValid			(void) const;
				bool OffsetSafe			(Int32_C4D offset);

				static FXVolumeCellIterator* Alloc();
				static void Free(FXVolumeCellIterator*& p);
			};

			class FXVolumeMesh : public FXVolume
			{
			public:
				BaseObject* GetMeshInterface		(void);
				Matrix		GetMg					(void) const;
				void		GetMotion				(const vector3d& physical_position, vector3d& linear, vector3d& angular) const;
			};

			static Int32_C4D GetTriangleCount		(const FXVolumeMesh* meshvolume);
			static Int32_C4D GetVertexCount			(const FXVolumeMesh* meshvolume);
			static bool HasUVdata				(const FXVolumeMesh* meshvolume);
			
			class FXMesher : public FXBase
			{
			public:
				Matrix		GetMg				(void) const;
				bool		UpdateMesh			(void);
			};

			static Int32_C4D GetTriangleCount		(const FXMesher* meshvolume);
			static Int32_C4D GetVertexCount			(const FXMesher* meshvolume);
			static bool HasUVdata				(const FXMesher* meshvolume);

			class FXMeshIterator
			{
			public:
				vector3d	GetVertex			(void);
				vector3d	GetVertexByIndex	(Int32_C4D index);
				VecInt3D	GetTriangle			(void);
				VecInt3D	GetTriangleByIndex	(Int32_C4D index);

				double		GetProperty_Scalar	(const ParticleProperty type, BaseObject* node) const;
				vector3d	GetProperty_Vector	(const ParticleProperty type, BaseObject* node) const;
				void		SetProperty_Scalar	(const double new_value, const ParticleProperty type, BaseObject* node) const;
				void		SetProperty_Vector	(const vector3d& new_value, const ParticleProperty type, BaseObject* node) const;

				bool		Init				(FXVolumeMesh* mesh);
				bool		Init				(FXMesher* mesh);
				void		Restart				(bool tri = true, bool vert = true);
				bool		SetNext				(bool tri);
				bool		SetPrev				(bool tri);
				void		Offset				(bool tri, Int32_C4D offset);
				bool		IsValid				(bool tri) const;
				bool		OffsetSafe			(bool tri, Int32_C4D offset);

				static FXMeshIterator* Alloc();
				static void Free(FXMeshIterator*& p);
			};
		}
	}
}


#endif //API_EFFEX_PARTICLE_H
