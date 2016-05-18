// Copyright (c) All Rights Reserved, Navié
//
// This does not touch the license for the Cinema 4D specific code functions used
// Please see the Cinema 4D license correspondingly. All other rights reserved.
//
// Author:	Samir Kharchi
// Date:	2014-09-01 (2.5)
// Update:	2016-02-15 (2.7)

#ifndef API_EFFEX_H
#define API_EFFEX_H

#include "api_effex_to_c4d.h"
#include "api_effex_lib.h"
#include "api_effex_node_constraint.h"
#include "api_effex_node_operator.h"
#include "api_effex_node_force.h"
#include "api_effex_channel.h"
#include "api_effex_volume.h"
#include "kdNeighbor.h"

#include "customgui_inexclude.h"

class EffexHook;

#define NAVIE	NAVIE_GLOBAL
#define EFFEX	NAVIE_GLOBAL::NAVIE_EFFEX
#define FXAPI	NAVIE_GLOBAL::NAVIE_EFFEX::NAVIE_API

namespace NAVIE_GLOBAL
{
	template < typename T, typename Tspace>  class EGrid; typedef EGrid<double,double> EGridd;
	namespace NAVIE_EFFEX
	{
		class iNodeBaseWrapper;
		class DirtyCheck;
		class iLinkList;
		class Scene;
		class iBase;
		class ParticleGroup;
		class Constraint;		
		class ParticleIterator;
		class MeshIterator;
		class VolumeBase;
		class VolumeMesh;
		class ImplicitMesher;
		template < typename T, typename C > class CellIterator;
		template < typename DATATYPE, typename GRIDTYPE> class ChannelBase_Scalar;
		template < typename DATATYPE, typename GRIDTYPE> class ChannelBase_Vector;
		template < typename DATATYPE, typename GRIDTYPE> class FuelGridChannel;
		template < typename DATATYPE, typename GRIDTYPE> class FireGridChannel;
		typedef ChannelBase_Scalar<double,EGridd> ChannelScalar;
		typedef ChannelBase_Vector<vector3d,NAVIE_GLOBAL::EGridd> ChannelVector;
		typedef FireGridChannel<double,EGridd> ChannelFire;
		typedef FuelGridChannel<double,EGridd> ChannelFuel;
		typedef CellIterator<double, ChannelScalar > ScalarIterator;
		typedef CellIterator<vector3d, ChannelVector > VectorIterator;
		typedef CellIterator<double, VolumeBase > VolumeIterator;
		
		namespace NAVIE_API
		{
			/* Candidate Button Structures */
			typedef std::pair	<Int32_C4D,String>	FXTypeInfo;
			typedef std::vector < FXTypeInfo >	FXTypeInfos;

			struct ProcessData
			{
				//Some useful global data
				BaseThread* bt;
				bool islast_thread;
				int thread_index;
				void* cast_data;
				unsigned int mode;
			};

			struct ProcessDataGrids : public ProcessData
			{ 
				//For Grid Operators
				VecInt3D start, end;

				//Cell Coordinate
				VecInt3D xyz;
				/* Cell index - One for collocated grids and three for staggered grids */
				Int32_C4D center_index;
				std::vector<Int32_C4D> indices;

				//Cell Volume Fractions
				double frac_c,frac_u,frac_v,frac_w;				
				double constraint_value;				//current constraint value
				vector3d physical_position; //cell's physical position
				vector3d world_position;	//cell's world position
				vector3d op_result;			//Resulting value - Can be changed
			};

			struct ProcessDataParticles : public ProcessData
			{ 
				//For Particle Operators
				unsigned int start;		//Particle Index to start from
				unsigned int end;		//Particle Index to end

				//For Particle Forces
				double constraint_value; //current constraint value
				uInt32_C4D index; //Particle Index
				unsigned char type;  //Particle Type
				vector3d physical_position; //constains the physical particle position
				vector3d world_position; //contains the world particle position
				vector3d op_result; //Resulting value - Can be changed
			};

			/* Should be called once at system start */
			Bool InitEffex(void);
			/* Global Functions */
			void HandleInexcludeBits	(InExcludeData* include, std::vector<Int32>& oldflags);
			bool OpenCandidatePopup		(bool is_node_group, std::vector<FXBase*> &items, FXTypeInfos& types, BaseObject* caller, Int32_C4D linkfield_id, bool is_inexclude, bool create_menu, Int32_C4D inex_flags);
			
			void PhysicalToWorld		(FXScene* scene, vector3d& physical_position); /* Converts a physical position (e.g. particle position) into a Cinema 4D world position */
			void WorldToPhysical		(FXScene* scene, vector3d& world_position);	/* Converts a Cinema 4D world position into a physical position*/
			bool GridToWorld			(FXBase* channel, const NAVIE_GLOBAL::VecInt3D& grid_pos, vector3d& world_position, bool local);	/* Converts a grid position (e.g. channel) into a Cinema 4D world position */
			bool GridToPhysical			(FXBase* channel, const NAVIE_GLOBAL::VecInt3D& grid_pos, vector3d& physical_position, bool local);		/* Converts a grid position (e.g. channel) into a physical position*/
			bool WorldToGrid			(FXBase* channel, NAVIE_GLOBAL::vector3d world_pos, NAVIE_GLOBAL::VecInt3D& grid_pos, bool local);	/* Converts a C4D world position into a grid position (e.g. channel) */
			bool PhysicalToGrid			(FXBase* channel, NAVIE_GLOBAL::vector3d physical_pos, NAVIE_GLOBAL::VecInt3D& grid_pos, bool local);		/* Converts a physical position into a grid position (e.g. channel)*/
			
			iNodeBaseWrapper* CreateWrapper(BaseObject* op);
			void DeleteWrapper			(iNodeBaseWrapper*& ptr_wrapper);
			void UpdateWrapper			(iNodeBaseWrapper* ptr_wrapper, BaseObject* op);

			enum NodeRetrieveType
			{
				NodeRetrieveType_ParticleGroup,
				NodeRetrieveType_Volume,
				NodeRetrieveType_ScalarChannel,
				NodeRetrieveType_VectorChannel,
				NodeRetrieveType_Mesher,
				NodeRetrieveType_Duration,

				NodeRetrieveType_Unknown
			};

			FXBase*	GetNode				(FXScene* scene, BaseObject* node, NodeRetrieveType type);
			void	GetNodes			(FXScene* scene, InExcludeData* filter, std::vector<FXBase*>& result, NodeRetrieveType type);
		}
	}

}
/************************************************************************/
/* INTERNAL                                                             */
/************************************************************************/
using namespace NAVIE_GLOBAL::NAVIE_EFFEX;

const NAVIE_GLOBAL::vector3d zerovector(0.0);

struct EffexParticleLib
{
	/* Particle */
	const NAVIE_GLOBAL::vector3d&	(EffexParticle::*GetPosition)			(void) const;
	const NAVIE_GLOBAL::vector3d&	(EffexParticle::*GetVelocity)			(void) const;
	double			(EffexParticle::*GetAge)				(void) const;
	double			(EffexParticle::*GetProperty_Scalar)	(const double& _default		, const ParticleProperty & prop, const iNodeBaseWrapper* node_interface) const;
	NAVIE_GLOBAL::vector3d		(EffexParticle::*GetProperty_Vector)	(const NAVIE_GLOBAL::vector3d& _default	, const ParticleProperty & prop, const iNodeBaseWrapper* node_interface) const;
	bool			(EffexParticle::*GetProperty_State)		(const bool& _default		, const ParticleProperty & prop, const iNodeBaseWrapper* node_interface) const;

	void			(EffexParticle::*SetPosition)			(const NAVIE_GLOBAL::vector3d& pos);
	void			(EffexParticle::*SetVelocity)			(const NAVIE_GLOBAL::vector3d& vel);
	void			(EffexParticle::*SetAge)				(const int age);
	bool			(EffexParticle::*SetProperty_Scalar)	(const double val		, const ParticleProperty & prop, const iNodeBaseWrapper* node_interface);
	bool			(EffexParticle::*SetProperty_Vector)	(const NAVIE_GLOBAL::vector3d& val	, const ParticleProperty & prop, const iNodeBaseWrapper* node_interface);
	bool			(EffexParticle::*SetProperty_State)		(const bool val			, const ParticleProperty & prop, const iNodeBaseWrapper* node_interface);

};

struct EffexParticleGroupLib
{
	/* Particle Group */
	EffexParticle*	(ParticleGroup::*GetParticle)			(Int32_C4D index, ParticleFactoryTypes subgroup);
	EffexParticle*	(ParticleGroup::*AddParticle)			(ParticleFactoryTypes subgroup, bool multithreaded);
	Int32_C4D			(ParticleGroup::*GetParticleCount)		(ParticleFactoryTypes subgroup) const;
	void			(ParticleGroup::*ComputeNeighbors)		(ParticleFactoryTypes subgroup, const NAVIE_GLOBAL::vector3d& global_position, double radius, std::vector<NAVIE::NeighborData>& neighbors, const int cpu);
	void			(ParticleGroup::*SetDirtySearch)		(const ParticleFactoryTypes subgroup);
	bool			(ParticleGroup::*IsCached)				(const ParticleFactoryTypes subgroup) const;
	void			(ParticleGroup::*UpdateBounds)			(void);
};

struct EffexParticleIteratorLib
{
	/* Particle Group */
	EffexParticle*	(ParticleIterator::*GetParticle)		(const int cpu);
	EffexParticle*	(ParticleIterator::*GetFirstParticle)	(const int cpu);
	EffexParticle*	(ParticleIterator::*GetLastParticle)	(const int cpu);

	bool			(ParticleIterator::*Init)				(ParticleGroup* group, const ParticleFactoryTypes m_factory, const int cpus);
	void			(ParticleIterator::*Restart)			(const int cpu);
	bool			(ParticleIterator::*SetNext)			(const int cpu);
	bool			(ParticleIterator::*SetPrev)			(const int cpu);
	void			(ParticleIterator::*Offset)				(const int cpu, Int32_C4D offset);
	bool			(ParticleIterator::*OffsetSafe)			(const int cpu, Int32_C4D offset);
	bool			(ParticleIterator::*IsValid)			(const int cpu) const;

	ParticleIterator* (*Alloc)();
	void (*Free)(ParticleIterator*& p);
};

struct EffexSceneLib
{
	/* Scene */
	iNodeBaseWrapper* (Scene::*GetInterface)				(void);
	int				(Scene::*GetCPUCount)				(void) const;
	bool			(Scene::*IsActive)					(void) const;
	const NAVIE_GLOBAL::vector3d& (Scene::*GetGravity)	(void) const;
	const SimulationInfo* (Scene::*GetSimulationInfo)	(void) const;
};

struct EffexServerLib
{
	/* Server */
	const int		(EffexHook::*GetSceneCount)				(void) const;
	const int		(EffexHook::*GetActiveSceneCount)		(void) const;
	Scene*			(EffexHook::*GetEffexScene)				(BaseObject* node);
	Scene*			(EffexHook::*nvGetEffexScene)			(iNodeBaseWrapper* node);
	ParticleGroup*	(EffexHook::*GetParticleGroup)			(iNodeBaseWrapper* node);
	const ParticleGroup* (EffexHook::*GetParticleGroupR)	(iNodeBaseWrapper* node) const;

	void			(EffexHook::*GetConstraints)			(iLinkList* filter, std::vector<Constraint*>& result);
};

struct EffexBaseLib
{
	void				(iBase::*Initialise)				(iNodeBaseWrapper* ptr_interface, Scene* server);
	iNodeBaseWrapper*	(iBase::*GetInterface)				(void);
	const int			(iBase::*GetType)					(void) const;
	NodeBaseType		(iBase::*GetBaseType)				(void) const;
	void				(iBase::*GetSubType)				(int& subtype) const;
	bool				(iBase::*IsCached)					(void) const;
	bool				(iBase::*IsDirty)					(DirtyCheck* checklist);
	Scene*				(iBase::*GetScene)					(void) const;
};

struct EffexConstraintLib
{
	bool				(Constraint::*IsInverted)			(void) const;
	bool				(Constraint::*IsParticleConstraint)	(void) const;
	bool				(Constraint::*GetConstraint)		(const NAVIE_GLOBAL::vector3d& position, double& src_value, int blendmode, void* local_data, int cpu);
	bool				(Constraint::*GetConstraintParticle)(const NAVIE_GLOBAL::vector3d& position, double& src_value, int blendmode, void* local_data, int cpu, const void* t_particle);
};

struct EffexScalarChannelLib
{
	double				(ChannelScalar::*GetRangeMinimum)	(void) const;
	double				(ChannelScalar::*GetRangeMaximum)	(void) const;
	double				(ChannelScalar::*GetResetValue)	(void) const;

	void				(ChannelScalar::*GetBounds)		(NAVIE_GLOBAL::vector3d& ref_minimum, NAVIE_GLOBAL::vector3d& ref_maximum);
	bool				(ChannelScalar::*Inside)			(const NAVIE_GLOBAL::vector3d& physical_position, const bool excludeborders);
	bool				(ChannelScalar::*InsideGrid)		(const NAVIE_GLOBAL::vector3d& physical_position, const bool excludeborders);

	double				(ChannelScalar::*GetValue)			(const NAVIE_GLOBAL::vector3d& physical_position) const;
	bool				(ChannelScalar::*Resize)			(NAVIE_GLOBAL::vector3d& ref_minimum, NAVIE_GLOBAL::vector3d& ref_maximum);
	void				(ChannelScalar::*SetValue)			(const NAVIE_GLOBAL::vector3d& physical_position, double value);
	void				(ChannelScalar::*UpdateBounds)		(void);

	double				(ChannelFuel::*GetIgnitionTemperature) (void)	const;
	double				(ChannelFire::*GetCoolingPoint)		(void)	const;
	double				(ChannelFire::*GetDeathRate)		(void)		const;
	double				(ChannelFire::*GetAfterLife)		(void)		const;
};

struct EffexVectorChannelLib
{
	const NAVIE_GLOBAL::vector3d&		(ChannelVector::*GetRangeMinimum)	(void) const;
	const NAVIE_GLOBAL::vector3d&		(ChannelVector::*GetRangeMaximum)	(void) const;
	const NAVIE_GLOBAL::vector3d&		(ChannelVector::*GetResetValue)	(void) const;

	void				(ChannelVector::*GetBounds)		(NAVIE_GLOBAL::vector3d& ref_minimum, NAVIE_GLOBAL::vector3d& ref_maximum);
	bool				(ChannelVector::*Inside)			(const NAVIE_GLOBAL::vector3d& physical_position, const bool excludeborders);
	bool				(ChannelVector::*InsideGrid)		(const NAVIE_GLOBAL::vector3d& physical_position, const bool excludeborders);

	NAVIE_GLOBAL::vector3d (ChannelVector::*GetValue)		(const NAVIE_GLOBAL::vector3d& physical_position) const;
	bool				(ChannelVector::*Resize)			(NAVIE_GLOBAL::vector3d& ref_minimum, NAVIE_GLOBAL::vector3d& ref_maximum);
	void				(ChannelVector::*SetValue)		(const NAVIE_GLOBAL::vector3d& physical_position, const NAVIE_GLOBAL::vector3d& value);
	void				(ChannelVector::*UpdateBounds)	(void);

};

struct EffexVolumeLib
{
	void		(VolumeBase::*GetBounds)		(NAVIE_GLOBAL::vector3d& ref_minimum, NAVIE_GLOBAL::vector3d& ref_maximum);
	bool		(VolumeBase::*Inside)			(const NAVIE_GLOBAL::vector3d& physical_position) const;
	double		(VolumeBase::*GetValue)			(const NAVIE_GLOBAL::vector3d& physical_position) const;
	void		(VolumeBase::*UpdateBounds)		(void);
	bool		(VolumeBase::*IsObstacle)		(void) const;
	bool		(VolumeBase::*IsGridObstacle)	(void) const;
	double		(VolumeBase::*GetMaxDistance)	(void) const;
	bool		(VolumeBase::*InsideVolume)		(const NAVIE_GLOBAL::vector3d& physical_position, float offset) const;
	NAVIE_GLOBAL::vector3d	(VolumeBase::*GetNormal) (const NAVIE_GLOBAL::vector3d& physical_position) const;
	double		(VolumeBase::*LinearFalloff)	(const NAVIE_GLOBAL::vector3d& physical_position) const;
	bool		(VolumeBase::*ProjectPoint)		(NAVIE_GLOBAL::vector3d &global_physical_position, NAVIE_GLOBAL::vector3d &result_grid_position, NAVIE_GLOBAL::vector3d& result_coll_normal, double projection) const;				

	Int32_C4D		(*GetTriangleCount)				(const VolumeMesh* meshvolume);
	Int32_C4D		(*GetVertexCount)				(const VolumeMesh* meshvolume);
	bool		(*HasUVdata)					(const VolumeMesh* meshvolume);
};

struct EffexMesherLib
{
	Matrix		(ImplicitMesher::*GetMg)		(void) const;
	bool		(ImplicitMesher::*UpdateMesh)	(void);
	Int32_C4D		(*GetTriangleCount)				(const ImplicitMesher* meshvolume);
	Int32_C4D		(*GetVertexCount)				(const ImplicitMesher* meshvolume);
	bool		(*HasUVdata)					(const ImplicitMesher* meshvolume);
};

template < typename T, typename C >
struct EffexCellIteratorLib
{
	NAVIE_GLOBAL::VecInt3D	(CellIterator<T, C >::*GetCoordinate)		(const int cpu);
	Int32_C4D	(CellIterator<T, C >::*GetLinearCoordinate)		(const int cpu);
	T			(CellIterator<T, C >::*GetValue)			(const int cpu);
	void		(CellIterator<T, C >::*SetValue)			(const int cpu, const T& value);
	T			(CellIterator<T, C >::*GetNeighborValue)	(const int cpu, short x, short y, short z) ;
	bool		(CellIterator<T, C >::*Init)				(C* channel);
	bool		(CellIterator<T, C >::*InitMP)				(C* channel, int cpus, bool include_borders);
	void		(CellIterator<T, C >::*Start)				(const int cpu, bool reverse);
	bool		(CellIterator<T, C >::*SetNext)				(const int cpu);
	bool		(CellIterator<T, C >::*SetPrev)				(const int cpu);
	void		(CellIterator<T, C >::*Offset)				(Int32_C4D offset);
	bool		(CellIterator<T, C >::*OffsetSafe)			(Int32_C4D offset);
	bool		(CellIterator<T, C >::*IsValid)				(void) const;

	CellIterator<T, C >* (*Alloc)();
	void (*Free)(CellIterator<T, C >*& p);
};

struct EffexMeshIteratorLib
{
	NAVIE_GLOBAL::vector3d	(MeshIterator::*GetVertex)();
	NAVIE_GLOBAL::vector3d	(MeshIterator::*GetVertexByIndex)(Int32_C4D index);
	NAVIE_GLOBAL::VecInt3D	(MeshIterator::*GetTriangle)();
	NAVIE_GLOBAL::VecInt3D	(MeshIterator::*GetTriangleByIndex)(Int32_C4D index);

	double					(MeshIterator::*GetProperty_Scalar)(const ParticleProperty type, BaseObject* node) const;
	NAVIE_GLOBAL::vector3d	(MeshIterator::*GetProperty_Vector)(const ParticleProperty type, BaseObject* node) const;
	void					(MeshIterator::*SetProperty_Scalar)(const double new_value, const ParticleProperty type, BaseObject* node) const;
	void					(MeshIterator::*SetProperty_Vector)(const NAVIE_GLOBAL::vector3d& new_value, const ParticleProperty type, BaseObject* node) const;

	bool					(MeshIterator::*Init)		(VolumeMesh* mesh);
	bool					(MeshIterator::*InitMesher)	(ImplicitMesher* mesh);
	void					(MeshIterator::*Restart)	(bool tri, bool);
	bool					(MeshIterator::*SetNext)	(bool tri);
	bool					(MeshIterator::*SetPrev)	(bool tri);
	void					(MeshIterator::*Offset)		(bool tri, Int32_C4D offset);
	bool					(MeshIterator::*IsValid)	(bool tri) const;
	bool					(MeshIterator::*OffsetSafe)	(bool tri, Int32_C4D offset);

	MeshIterator* (*Alloc)();
	void (*Free)(MeshIterator*& p);
};

struct EffexLibrary : public C4DLibrary
{
	EffexMesherLib*			fx_mesher;
	EffexCellIteratorLib<double,ChannelScalar>*	fx_csiterator;
	EffexCellIteratorLib<double,VolumeBase>*	fx_cvoliterator;
	EffexCellIteratorLib<NAVIE_GLOBAL::vector3d,ChannelVector>*	fx_cviterator;
	EffexMeshIteratorLib*	fx_miterator;
	EffexVolumeLib*			fx_volume;
	EffexVectorChannelLib*	fx_channelvector;
	EffexScalarChannelLib*	fx_channelscalar;
	EffexConstraintLib*		fx_constraint;
	EffexBaseLib*			fx_base;
	EffexParticleGroupLib*	fx_pgroup;
	EffexParticleIteratorLib* fx_piterator;
	EffexParticleLib*		fx_particle;
	EffexSceneLib*			fx_scene;
	EffexServerLib*			fx_server;

	/* Global Functions */
	void	(*HandleInexcludeBits)	(InExcludeData* include, std::vector<Int32>& oldflags);
	bool 	(*OpenCandidatePopup)	(bool is_node_group, std::vector<iBase*> &items, FXAPI::FXTypeInfos& types, BaseObject* caller, Int32_C4D linkfield_id, bool is_inexclude, bool create_menu, Int32_C4D inex_flags);
	void	(*PhysicalToWorld)		(Scene* scene, NAVIE_GLOBAL::vector3d& physical_position);
	void	(*WorldToPhysical)		(Scene* scene, NAVIE_GLOBAL::vector3d& world_position);	
	bool	(*GridToWorld)			(iBase* channel, const NAVIE_GLOBAL::VecInt3D& grid_pos, NAVIE_GLOBAL::vector3d& world_position, bool local);	/* Converts a grid position (e.g. channel) into a Cinema 4D world position */
	bool	(*GridToPhysical)		(iBase* channel, const NAVIE_GLOBAL::VecInt3D& grid_pos, NAVIE_GLOBAL::vector3d& physical_position, bool local);		/* Converts a grid position (e.g. channel) into a physical position*/
	bool	(*WorldToGrid)			(iBase* channel, NAVIE_GLOBAL::vector3d world_pos, NAVIE_GLOBAL::VecInt3D& grid_pos, bool local);	/* Converts a C4D world position into a grid position (e.g. channel) */
	bool	(*PhysicalToGrid)		(iBase* channel, NAVIE_GLOBAL::vector3d physical_pos, NAVIE_GLOBAL::VecInt3D& grid_pos, bool local);

	iBase*	(*GetNode)				(Scene* scene, BaseObject* node, FXAPI::NodeRetrieveType type);
	void	(*GetNodes)				(Scene* scene, InExcludeData* filter, std::vector<iBase*>& result, FXAPI::NodeRetrieveType type);
	iNodeBaseWrapper* (*CreateWrapper) (BaseObject* op);
	void	(*DeleteWrapper)		(iNodeBaseWrapper*& ptr_wrapper);
	void	(*UpdateWrapper)		(iNodeBaseWrapper* ptr_wrapper, BaseObject* op);
};

Bool RegisterFXForcePlugin		(Int32_C4D id, const String &str, Int32_C4D objectinfo, DataAllocator *npalloc, const String &description, BaseBitmap *icon, Int32_C4D disklevel);
Bool RegisterFXOperatorPlugin	(Int32_C4D id, const String &str, Int32_C4D objectinfo, DataAllocator *npalloc, const String &description, BaseBitmap *icon, Int32_C4D disklevel);
Bool RegisterFXConstraintPlugin(Int32_C4D id, const String &str, Int32_C4D objectinfo, DataAllocator *npalloc, const String &description, BaseBitmap *icon, Int32_C4D disklevel);

// INTERNAL
#endif
