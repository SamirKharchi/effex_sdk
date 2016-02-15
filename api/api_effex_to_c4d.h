// Copyright (c) All Rights Reserved, Navié
//
// This does not touch the license for the Cinema 4D specific code functions used
// Please see the Cinema 4D license correspondingly. All other rights reserved.
//
// Author: Samir Kharchi
#ifndef API_EFFEX_C4D_H
#define API_EFFEX_C4D_H

#include "ge_lvector.h"
#include "vector/vecint3d.h"

namespace NAVIE_GLOBAL
{
	namespace NAVIE_EFFEX
	{
		namespace NAVIE_API
		{
			/************************************************************************/
			/* Convenience Conversion between an Effex vector and a C4D Vector */
			/************************************************************************/
			template < typename T >
			inline NAVIE_GLOBAL::Vec3D<T> VectorToVec3d(const Vector& src)
			{
				return NAVIE_GLOBAL::Vec3D<T>(src.x,src.y,src.z);
			}

			inline NAVIE_GLOBAL::VecInt3D VectorToVecInt3D(const Vector& src)
			{
				return NAVIE_GLOBAL::VecInt3D(std::lrint(src.x),std::lrint(src.y),std::lrint(src.z));
			}

			template < typename T >
			inline Vector Vec3DToVector(const NAVIE_GLOBAL::Vec3D<T>& src)
			{
				return Vector(src.x,src.y,src.z);
			}

			inline Vector VecInt3DToVector(const NAVIE_GLOBAL::VecInt3D& src)
			{
				return Vector(src.x,src.y,src.z);
			}
		}
	}
}

#endif