// Copyright (c) All Rights Reserved, Navié
//
// This does not touch the license for the Cinema 4D specific code functions used
// Please see the Cinema 4D license correspondingly. All other rights reserved.
//
// Author: Samir Kharchi
#ifndef API_EFFEX_BASE_H
#define API_EFFEX_BASE_H

#include "c4d_baseobject.h"
#include "vector/vector3d.h"
#include "global_nodes.h"
#include "navie_memory_c4d.h"

namespace NAVIE_GLOBAL
{
	namespace NAVIE_EFFEX
	{
		class Constraint;
		class iNodeBaseWrapper;
		class DirtyCheck;

		namespace NAVIE_API
		{
			class FXScene;

			/* Base Node */
			class FXBase
			{
			public:
				iNodeBaseWrapper* GetInterface();

				const int			GetType			(void) const;
				NodeBaseType		GetBaseType		(void) const;
				void				GetSubType		(int& subtype) const;
				void				Initialise		(iNodeBaseWrapper* ptr_interface, FXScene* server);
				bool				IsCached		(void) const;
				bool				IsDirty			(DirtyCheck* checklist);
				FXScene*			GetScene		(void) const;
			};
		}
	}
}


#endif //API_EFFEX_PARTICLE_H