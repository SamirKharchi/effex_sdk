// Copyright (c) All Rights Reserved, Navié
//
// This does not touch the license for the Cinema 4D specific code functions used
// Please see the Cinema 4D license correspondingly. All other rights reserved.
//
// Author: Samir Kharchi

#ifndef __VECINT3D_H__
#define __VECINT3D_H__

#include "vector3d.h"

namespace NAVIE_GLOBAL
{
	class VecInt3D
	{
	public:
		VecInt3D() : x(0), y(0), z(0)
		{			
		}
		VecInt3D(int x_, int y_, int z_)
		{
			mValue[0] = x_;
			mValue[1] = y_;
			mValue[2] = z_;
		}
		VecInt3D(const VecInt3D & v)
		{
			mValue[0] = v.x;
			mValue[1] = v.y;
			mValue[2] = v.z;
		}
		explicit VecInt3D(int x_)
		{
			mValue[0] = mValue[1] = mValue[2] = x_;
		}
		explicit VecInt3D(const vector3f & v)
		{
			mValue[0] = static_cast<int>(v.x);
			mValue[1] = static_cast<int>(v.y);
			mValue[2] = static_cast<int>(v.z);
		}
		explicit VecInt3D(const vector3d & v)
		{
			mValue[0] = static_cast<int>(v.x);
			mValue[1] = static_cast<int>(v.y);
			mValue[2] = static_cast<int>(v.z);
		}

		inline const int &operator() (int i) const
		{
			return mValue[i];
		}
		inline int &operator[] (int i)
		{
			return mValue[i];
		}
		inline const int &operator[] (int i) const
		{
			return mValue[i];
		}
		inline bool operator==(const VecInt3D & v) const
		{
			return (mValue[0] == v.x) && (mValue[1] == v.y) && (mValue[2] == v.z);
		}
		inline bool operator!=(const VecInt3D & v) const
		{
			return (mValue[0] != v.x) || (mValue[1] != v.y) || (mValue[2] != v.z);
		}
		inline bool operator<(const VecInt3D & v) const
		{
			return (mValue[0] < v.x) && (mValue[1] < v.y) && (mValue[2] < v.z);
		}
		inline bool operator<=(const VecInt3D & v) const
		{
			return (mValue[0] <= v.x) && (mValue[1] <= v.y) && (mValue[2] <= v.z);
		}
		inline bool operator>(const VecInt3D & v) const
		{
			return (mValue[0] > v.x) && (mValue[1] > v.y) && (mValue[2] > v.z);
		}
		inline bool operator>=(const VecInt3D & v) const
		{
			return (mValue[0] >= v.x) && (mValue[1] >= v.y) && (mValue[2] >= v.z);
		}
		inline VecInt3D & operator=(const VecInt3D & v)
		{
			mValue[0] = v.x;
			mValue[1] = v.y;
			mValue[2] = v.z;
			return *this;
		}

		inline VecInt3D & operator+=(const VecInt3D & v)
		{
			mValue[0] += v.x;
			mValue[1] += v.y;
			mValue[2] += v.z;
			return *this;
		}
		inline VecInt3D & operator-=(const VecInt3D & v)
		{
			mValue[0] -= v.x;
			mValue[1] -= v.y;
			mValue[2] -= v.z;
			return *this;
		}

		/* Dot product.*/
		inline int operator*(const VecInt3D & v) const
		{
			return (x * v.x) + (y * v.y) + (z * v.z);
		}
		inline VecInt3D operator*(const int & v) const
		{
			return VecInt3D(x*v,y*v,z*v);
		}
		inline VecInt3D operator+(const VecInt3D & v) const
		{
			return VecInt3D(x+v.x,y+v.y,z+v.z);
		}
		inline VecInt3D operator-(const VecInt3D & v) const
		{
			return VecInt3D(x-v.x,y-v.y,z-v.z);
		}
		inline VecInt3D operator/(const int& v) const
		{
			return VecInt3D(x/v,y/v,z/v);
		}

		inline VecInt3D ClampToZero(void) const
		{
			return VecInt3D((x < 0) ? 0 : x, (y < 0) ? 0 : y, (z < 0) ? 0 : z);
		}
		inline VecInt3D ClampToValue(const VecInt3D& c) const
		{
			return VecInt3D((x > c.x) ? c.x : x,(y > c.y) ? c.y : y, (z > c.z) ? c.z : z);
		}
		inline int Norm2_2() const
		{
			return x * x + y * y + z * z;
		}
		inline bool is_zero() const
		{
			return (x==0 && y==0 && z==0);
		}

	public:
		union {
			int mValue[3];
			struct  
			{
				int x;
				int y;
				int z;
			};
			struct
			{
				int a;
				int b;
				int c;
			};
			struct
			{
				int red;
				int green;
				int blue;
			};
		};
	};
	
	/* Post definitions */
	template < typename T >
	inline NAVIE_GLOBAL::Vec3D<T> NAVIE_GLOBAL::Vec3D<T>::operator/(const VecInt3D& v) const
	{
		return Vec3D<T>(mValue[0]/v.x,mValue[1]/v.y,mValue[2]/v.z);
	}
	template < typename T >
	inline NAVIE_GLOBAL::Vec3D<T> NAVIE_GLOBAL::Vec3D<T>::operator+(const VecInt3D& v) const
	{
		return Vec3D<T>(mValue[0]+v.x,mValue[1]+v.y,mValue[2]+v.z);
	}
	template < typename T >
	inline NAVIE_GLOBAL::Vec3D<T> NAVIE_GLOBAL::Vec3D<T>::operator-(const VecInt3D & v) const
	{
		return Vec3D<T>(mValue[0]-v.x,mValue[1]-v.y,mValue[2]-v.z);
	}
	template < typename T >
	inline NAVIE_GLOBAL::Vec3D<T> & NAVIE_GLOBAL::Vec3D<T>::operator=(const VecInt3D& f)
	{
		mValue[0] = f.x;
		mValue[1] = f.y;
		mValue[2] = f.z;
		return *this;
	}
	template < typename T >
	inline NAVIE_GLOBAL::Vec3D<T> NAVIE_GLOBAL::Vec3D<T>::operator ^(const VecInt3D& v) const
	{
		return NAVIE_GLOBAL::Vec3D<T>(mValue[0]*v.x,mValue[1]*v.y,mValue[2]*v.z);
	};

	/* Useful conversions */
	template < typename T >
	inline VecInt3D ToVecInt3d(const NAVIE_GLOBAL::Vec3D<T>& src)
	{
		return VecInt3D(floor(src.x),floor(src.y),floor(src.z));
	}
	template < typename T >
	inline NAVIE_GLOBAL::Vec3D<T> ToVec3d(const VecInt3D& src)
	{
		return NAVIE_GLOBAL::Vec3D<T>(src.x,src.y,src.z);
	}
}

#endif
