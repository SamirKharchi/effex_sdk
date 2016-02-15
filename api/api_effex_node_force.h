// Copyright (c) All Rights Reserved, Navié
//
// This does not touch the license for the Cinema 4D specific code functions used
// Please see the Cinema 4D license correspondingly. All other rights reserved.
//
// Author: Samir Kharchi
#ifndef API_EFFEX_NODE_FORCE_H
#define API_EFFEX_NODE_FORCE_H

#include "api_effex_node.h"

namespace NAVIE_GLOBAL
{
	namespace NAVIE_EFFEX
	{
		namespace NAVIE_API
		{
#define EFFEX_FORCE 1300170
			class FXForceData : public FXNodeData
			{
			private:
				typedef FXNodeData Base;

			public:	
				virtual Bool IsInstanceOf			(const GeListNode *node, Int32_C4D type) const;
				virtual void GetSubType				(int& subtype) const;

				virtual bool Precompute				(FXServer* server);
				virtual bool PrecomputeMP			(FXServer* server);
				virtual void Process				(void* t_data);
				virtual void FreePrecompute			(void);

				virtual Bool Message(GeListNode *node, Int32_C4D type, void *t_data) override;

			};

			struct FXFORCEPLUGIN : public FXNODEPLUGIN
			{
				bool			(FXForceData::*Precompute)				(FXServer* server);
				bool			(FXForceData::*PrecomputeMP)			(FXServer* server);
				void			(FXForceData::*Process)					(void* t_data);
				void			(FXForceData::*FreePrecompute)			(void);

				void*	reserved[(32-4)*C4DPL_MEMBERMULTIPLIER-1];
			};

		}
	}
}

#endif //API_EFFEX_PARTICLE_H