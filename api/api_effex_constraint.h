// Copyright (c) All Rights Reserved, Navié
//
// This does not touch the license for the Cinema 4D specific code functions used
// Please see the Cinema 4D license correspondingly. All other rights reserved.
//
// Author: Samir Kharchi
#ifndef API_EFFEX_CONSTRAINT_H
#define API_EFFEX_CONSTRAINT_H

#include "api_effex_base.h"

namespace NAVIE_GLOBAL
{
	namespace NAVIE_EFFEX
	{		
		namespace NAVIE_API
		{			
			/* Base Node */
			class FXConstraint : public FXBase
			{
			public:
				bool IsInverted				(void) const;
				bool IsParticleConstraint	(void) const;

				bool GetConstraint			(const vector3d& position, double& src_value, int blendmode, void* local_data, int cpu = 0);
				bool GetConstraintParticle	(const vector3d& position, double& src_value, int blendmode, void* local_data, int cpu = 0, const void* t_particle = nullptr);
			};
		}
	}
}


#endif //API_EFFEX_PARTICLE_H