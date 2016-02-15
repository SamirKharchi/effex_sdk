// Copyright (c) All Rights Reserved, Navié
//
// This does not touch the license for the Cinema 4D specific code functions used
// Please see the Cinema 4D license correspondingly. All other rights reserved.
//
// Author: Samir Kharchi
#ifndef API_EFFEX_PARTICLEGROUP_H
#define API_EFFEX_PARTICLEGROUP_H

#include "api_effex_particle.h"
#include "api_effex_base.h"
#include "global_particles.h"
#include "kdNeighbor.h"
#include <vector>

namespace NAVIE_GLOBAL
{
	namespace NAVIE_EFFEX
	{
		class EffexParticle;
		class ParticleIterator;

		namespace NAVIE_API
		{			
			/* Particle Group - holds all types of particles */
			class FXParticleGroup : public FXBase
			{
			private:
				FXParticleGroup();
				~FXParticleGroup();

			public:
				FXParticle* GetParticle		(Int32_C4D index, ParticleFactoryTypes subgroup);
				FXParticle*	AddParticle		(ParticleFactoryTypes subgroup, bool multithreaded = true);
				Int32_C4D		GetParticleCount(ParticleFactoryTypes subgroup);
				void		UpdateBounds	(void);

				void		FindNeighbors	(const ParticleFactoryTypes subgroup, const vector3d& global_position, const double radius, std::vector<NeighborData>& neighbors, const int cpu = 0);
				void		SetDirtySearch	(const ParticleFactoryTypes subgroup);
				bool		IsCached		(const ParticleFactoryTypes subgroup) const;
			};
			/************************************************************************/
			/* Particle Iterator - for browsing of particles */
			class FXParticleIterator
			{
			public:
				FXParticle* GetParticle		(const int cpu);
				FXParticle* GetFirstParticle(const int cpu);
				FXParticle* GetLastParticle	(const int cpu);

				bool Init			(FXParticleGroup* group, const ParticleFactoryTypes m_factory, const int cpus);
				void Restart		(const int cpu);
				bool SetNext		(const int cpu);
				bool SetPrev		(const int cpu);
				void Offset			(const int cpu, Int32_C4D offset);
				bool OffsetSafe		(const int cpu, Int32_C4D offset);
				bool IsValid		(const int cpu) const;

				static FXParticleIterator* Alloc();
				static void Free(FXParticleIterator*& p);
			};

		}
	}
}

#endif //API_EFFEX_PARTICLE_H