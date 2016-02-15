// Copyright (c) All Rights Reserved, Navié
//
// This does not touch the license for the Cinema 4D specific code functions used
// Please see the Cinema 4D license correspondingly. All other rights reserved.
//
// Author: Samir Kharchi
#ifndef API_EFFEX_NODE_CONSTRAINT_H
#define API_EFFEX_NODE_CONSTRAINT_H

#include "api_effex_node.h"

namespace NAVIE_GLOBAL
{
	namespace NAVIE_EFFEX
	{
		namespace NAVIE_API
		{
#define EFFEX_CONSTRAINT	1300139
			class FXConstraintData : public FXNodeData
			{
			private:
				typedef FXNodeData Base;

			public:	
				virtual Bool IsInstanceOf				(const GeListNode *node, Int32_C4D type) const;
				virtual Bool Init					(GeListNode *node);
				virtual void GetSubType				(int& subtype) const;

				/* Constraint */
				virtual bool IsParticleConstraint	(void) const;				
				virtual void PrecomputeConstraint	(void* t_data);
				virtual void FreePrecomputeConstraint(void);
				virtual bool GetConstraint			(const vector3d& position, double& src_value, void* local_data, int cpu = 0);
				virtual bool GetParticleConstraint	(const vector3d& position, double& src_value, void* local_data, int cpu = 0, const void* t_particle = nullptr);
			};

			struct FXCONSTRAINTPLUGIN : public FXNODEPLUGIN
			{
				// generator
				bool			(FXConstraintData::*IsParticleConstraint)		(void) const;				
				void			(FXConstraintData::*PrecomputeConstraint)		(void* t_data);
				void			(FXConstraintData::*FreePrecomputeConstraint)	(void);
				bool			(FXConstraintData::*GetConstraint)			(const NAVIE_GLOBAL::vector3d& position, double& src_value, void* local_data, int cpu);
				bool			(FXConstraintData::*GetParticleConstraint)	(const NAVIE_GLOBAL::vector3d& position, double& src_value, void* local_data, int cpu, const void* t_particle);

				void*	reserved[(32-5)*C4DPL_MEMBERMULTIPLIER-1];
			};

		}
	}
}

#endif //API_EFFEX_PARTICLE_H