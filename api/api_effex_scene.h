// Copyright (c) All Rights Reserved, Navié
//
// This does not touch the license for the Cinema 4D specific code functions used
// Please see the Cinema 4D license correspondingly. All other rights reserved.
//
// Author: Samir Kharchi
#ifndef API_EFFEX_SCENE_H
#define API_EFFEX_SCENE_H

#include "api_effex_particlegroup.h"
#include "api_effex_constraint.h"
#include "global_simulationtime.h"

class InExcludeData;

namespace NAVIE_GLOBAL
{
	namespace NAVIE_EFFEX
	{
		class iLinkList;

		namespace NAVIE_API
		{
			/************************************************************************/
			/* Scene access */
			class FXScene
			{
			private:
				FXScene();
				~FXScene();

			public:
				iNodeBaseWrapper* GetInterface		(void);
				int			GetCPUCount			(void) const;
				bool		IsActive			(void) const;
				const vector3d& GetGravity		(void) const;
				const SimulationInfo* GetSimulationInfo(void) const;
			};
			
			/************************************************************************/
			/* Server - holds all scenes */
			class FXServer : public BaseSceneHook
			{
			private:
				FXServer();
				~FXServer();

			public:
				const int GetSceneCount() const;
				const int GetActiveSceneCount() const;
				FXScene* GetEffexScene(BaseObject* node);
				FXScene* GetEffexScene(iNodeBaseWrapper* node);

				FXParticleGroup* GetParticleGroup(iNodeBaseWrapper* node); 
				const FXParticleGroup* GetParticleGroup(iNodeBaseWrapper* node) const; 

				void	GetConstraints(iLinkList* filter, std::vector<FXConstraint*>& result);

				static FXServer* Get(BaseDocument* doc);
			};
		}
	}
}

#endif //API_EFFEX_PARTICLE_H