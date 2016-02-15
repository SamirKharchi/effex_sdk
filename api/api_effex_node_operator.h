// Copyright (c) All Rights Reserved, Navié
//
// This does not touch the license for the Cinema 4D specific code functions used
// Please see the Cinema 4D license correspondingly. All other rights reserved.
//
// Author: Samir Kharchi
#ifndef API_EFFEX_NODE_OPERATOR_H
#define API_EFFEX_NODE_OPERATOR_H

#include "api_effex_node.h"

namespace NAVIE_GLOBAL
{
	namespace NAVIE_EFFEX
	{
		namespace NAVIE_API
		{
#define EFFEX_OPERATOR	1300169
			class FXOperatorData : public FXNodeData
			{
			private:
				typedef FXNodeData Base;

			public:	
				virtual Bool IsInstanceOf			(const GeListNode *node, Int32_C4D type) const;
				virtual void GetSubType				(int& subtype) const;
				
				/* Operator */
				virtual bool Precompute				(FXServer* server);
				virtual bool PrecomputeMP			(FXServer* server);
				virtual void Process				(void* t_data);
				virtual void FreePrecompute			(void);

				/* Threading */
				virtual bool UseOwnThread			(void) const;
				virtual bool IsMultiStep			(void) const;
				virtual bool IsMultiPrecompute		(void) const;
				virtual bool IsUpdateable			(void) const;

				virtual Bool Message(GeListNode *node, Int32_C4D type, void *t_data) override;

			};

			struct FXOPERATORPLUGIN : public FXNODEPLUGIN
			{
				bool			(FXOperatorData::*Precompute)				(FXServer* server);
				bool			(FXOperatorData::*PrecomputeMP)				(FXServer* server);
				void			(FXOperatorData::*Process)					(void* t_data);
				void			(FXOperatorData::*FreePrecompute)			(void);

				bool			(FXOperatorData::*UseOwnThread)				(void) const;
				bool			(FXOperatorData::*IsMultiStep)				(void) const;
				bool			(FXOperatorData::*IsMultiPrecompute)		(void) const;
				bool			(FXOperatorData::*IsUpdateable)				(void) const;

				void*	reserved[(32-8)*C4DPL_MEMBERMULTIPLIER-1];
			};

		}
	}
}

#endif //API_EFFEX_PARTICLE_H