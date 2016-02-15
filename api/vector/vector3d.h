// Copyright (c) All Rights Reserved, Navié
//
// This does not touch the license for the Cinema 4D specific code functions used
// Please see the Cinema 4D license correspondingly. All other rights reserved.
//
// Author: Samir Kharchi

#ifndef __VECTOR3D_H__
#define __VECTOR3D_H__

#include <utility>
#include <cmath>

namespace NAVIE_GLOBAL
{	
	class VecInt3D;

	template < typename T >
	class Vec3D
	{
	public:
		/************************************************************************/
		/*								Constructors							*/
		/************************************************************************/	
		Vec3D() : x(0), y(0), z(0)
		{
		}
		Vec3D(const Vec3D<T> & v) : x(v.x), y(v.y), z(v.z)
		{
		}
		Vec3D(const Vec3D<T> && v) : x(std::move(v.x)), y(std::move(v.y)), z(std::move(v.z))
		{
		}
		Vec3D(const float x_, const float y_, const float z_) : x(x_), y(y_), z(z_)
		{
		} 
		Vec3D(const double x_, const double y_, const double z_) : x(x_), y(y_), z(z_)
		{
		} 
		Vec3D(const int x_, const int y_, const int z_)
		{
			mValue[0] = static_cast < T >(x_);
			mValue[1] = static_cast < T >(y_);
			mValue[2] = static_cast < T >(z_);
		}
		explicit Vec3D(const float f) : x(f), y(f), z(f)
		{
		}
		explicit Vec3D(const double f) : x(f), y(f), z(f)
		{
		}
		explicit Vec3D(const int f)
		{
			mValue[0] = mValue[1] = mValue[2] = static_cast < T >(f);
		}
		/************************************************************************/
		/*								Operators								*/
		/************************************************************************/		
		T &operator[] (const int& i) 
		{ 
			return mValue[i];
		}
		const T &operator[] (const int& i) const
		{ 
			return mValue[i];
		}
		const T &operator() (const int& i) const 
		{ 
			return mValue[i]; 
		}
		inline bool operator==(const T & v) const
		{
			return (mValue[0] == v) && (mValue[1] == v) && (mValue[2] == v);
		}
		inline bool operator==(const Vec3D<T> & v) const
		{
			return (mValue[0] == v.x) && (mValue[1] == v.y) && (mValue[2] == v.z);
		}
		inline bool operator!=(const Vec3D<T> & v) const
		{
			return (mValue[0] != v.x) || (mValue[1] != v.y) || (mValue[2] != v.z);
		}
		inline bool operator!=(const double &v) const
		{
			return ((mValue[0]!=v) || (mValue[1]!=v) || (mValue[2] !=v));
		}
		inline bool operator<(const Vec3D<T> & v) const
		{
			return (mValue[0] < v.x) && (mValue[1] < v.y) && (mValue[2] < v.z);
		}
		inline bool operator<=(const Vec3D<T> & v) const
		{
			return (mValue[0] <= v.x) && (mValue[1] <= v.y) && (mValue[2] <= v.z);
		}
		inline bool operator>(const Vec3D<T> & v) const
		{
			return (mValue[0] > v.x) && (mValue[1] > v.y) && (mValue[2] > v.z);
		}
		inline bool operator>=(const Vec3D<T> & v) const
		{
			return (mValue[0] >= v.x) && (mValue[1] >= v.y) && (mValue[2] >= v.z);
		}
		/* Reference operators */
		inline Vec3D<T> & operator=(const Vec3D<T> & v)
		{
			mValue[0] = v.x;
			mValue[1] = v.y;
			mValue[2] = v.z;
			return *this;
		}
		inline Vec3D<T> & operator=(const float& f)
		{
			mValue[0] = mValue[1] = mValue[2] = (T)f;
			return *this;
		}
		inline Vec3D<T> & operator=(const double& f)
		{
			mValue[0] = mValue[1] = mValue[2] = f;
			return *this;
		}
		inline Vec3D<T> & operator=(const VecInt3D& f);
		
		inline Vec3D<T> & operator+=(const Vec3D<T> & v)
		{
			mValue[0] += v.x;
			mValue[1] += v.y;
			mValue[2] += v.z;
			return *this;
		}
		inline Vec3D<T> & operator-=(const Vec3D<T> & v)
		{
			mValue[0] -= v.x;
			mValue[1] -= v.y;
			mValue[2] -= v.z;

			return *this;
		}
		inline Vec3D<T> & operator*=(const T& f)
		{
			mValue[0] *= f;
			mValue[1] *= f;
			mValue[2] *= f;
			return *this;
		}
		inline Vec3D<T> & operator/=(const double& f)
		{
			T rec = T(1.)/f;
			mValue[0] *= rec;
			mValue[1] *= rec;
			mValue[2] *= rec;
			return *this;
		}
		inline Vec3D<T> & operator/=(const Vec3D<T>& f)
		{
			mValue[0] /= f.x;
			mValue[1] /= f.y;
			mValue[2] /= f.z;
			return *this;
		}
		/* Instance operators */
		inline Vec3D<T> operator/(const Vec3D<T>& v) const
		{
			return Vec3D<T>(mValue[0]/v.x,mValue[1]/v.y,mValue[2]/v.z);
		}
		inline Vec3D<T> operator/(const VecInt3D& v) const;

		inline Vec3D<T> operator/(const float& s) const
		{
			T rec = T(1.)/s;
			return Vec3D<T>(mValue[0] * rec,mValue[1] * rec,mValue[2] * rec);
		}
		inline Vec3D<T> operator/(const double& s) const
		{
			T rec = T(1.)/s;
			return Vec3D<T>(mValue[0] * rec,mValue[1] * rec,mValue[2] * rec);
		}
		inline Vec3D<T> operator/(const int& s) const
		{
			T rec = T(1.)/s;
			return Vec3D<T>(mValue[0] * rec,mValue[1] * rec,mValue[2] * rec);
		}
		inline Vec3D<T> operator/(const long& s) const
		{
			T rec = T(1.)/s;
			return Vec3D<T>(mValue[0] * rec,mValue[1] * rec,mValue[2] * rec);
		}
		inline Vec3D<T> operator*(const float& f) const
		{
			return Vec3D<T>(mValue[0]*f,mValue[1]*f,mValue[2]*f);
		}
		inline Vec3D<T> operator*(const double& f) const
		{
			return Vec3D<T>(mValue[0]*f,mValue[1]*f,mValue[2]*f);
		}
		inline Vec3D<T> operator ^(const Vec3D<T>& v) const
		{
			return Vec3D<T>(mValue[0]*v.x,mValue[1]*v.y,mValue[2]*v.z);
		}
		inline Vec3D<T> operator ^(const double& v) const
		{
			return Vec3D<T>(mValue[0]*v,mValue[1]*v,mValue[2]*v);
		}
		inline Vec3D<T> operator ^(const VecInt3D& v) const;
		inline Vec3D<T> operator+(const Vec3D<T> & v) const
		{
			return Vec3D<T>(mValue[0]+v.x,mValue[1]+v.y,mValue[2]+v.z);
		}
		inline Vec3D<T> operator+(const float v) const
		{
			return Vec3D<T>(mValue[0]+v,mValue[1]+v,mValue[2]+v);
		}
		inline Vec3D<T> operator+(const double v) const
		{
			return Vec3D<T>(mValue[0]+v,mValue[1]+v,mValue[2]+v);
		}
		inline Vec3D<T> operator+(const VecInt3D & v) const;

		inline Vec3D<T> operator-(const Vec3D<T> & v) const
		{
			return Vec3D<T>(mValue[0]-v.x,mValue[1]-v.y,mValue[2]-v.z);
		}
		inline Vec3D<T> operator-(const float & v) const
		{
			return Vec3D<T>(mValue[0]-v,mValue[1]-v,mValue[2]-v);
		}
		inline Vec3D<T> operator-(const double & v) const
		{
			return Vec3D<T>(mValue[0]-v,mValue[1]-v,mValue[2]-v);
		}
		inline Vec3D<T> operator-(const VecInt3D & v) const;

		/* Dot product */
		inline T operator*(const Vec3D<T> & v) const
		{
			return (mValue[0] * v.x) + (mValue[1] * v.y) + (mValue[2] * v.z);
		}

		/************************************************************************/
		/*                        friend operators                              */
		/************************************************************************/
		friend const Vec3D<T> operator * (T s,const Vec3D<T> &v)
		{
			return Vec3D<T>(v.x*s,v.y*s,v.z*s);
		}
		/** Calculate Cross product */
		friend const Vec3D<T> operator % (const Vec3D<T> &v1,const Vec3D<T> &v2)
		{
			return Vec3D<T>((v1.y*v2.z)-(v1.z*v2.y), (v1.z*v2.x)-(v1.x*v2.z), (v1.x*v2.y-v1.y*v2.x));
		}

		friend const Vec3D<T> operator ! (const Vec3D<T> &v)
		{			
			return v.normal();
		}
		/************************************************************************/
		/*                        useful operations                             */
		/************************************************************************/
		inline Vec3D<T> normal() const
		{
			T l=sqrt(mValue[0]*mValue[0]+mValue[1]*mValue[1]+mValue[2]*mValue[2]);
			if (l == 0.0) return Vec3D<T>(0.0);
			l = 1.0/l;
			return Vec3D<T>(mValue[0]*l,mValue[1]*l,mValue[2]*l);
		}
		inline void Normalize()
		{
			T l=sqrt(mValue[0]*mValue[0]+mValue[1]*mValue[1]+mValue[2]*mValue[2]);
			if (l!=0.0)
			{
				l = 1.0/l;
				mValue[0]*=l;
				mValue[1]*=l;
				mValue[2]*=l;
			}
		}
		inline T getSquaredLength() const
		{
			return (mValue[0] * mValue[0]) + (mValue[1] * mValue[1]) + (mValue[2] * mValue[2]);
		}
		inline T Len() const
		{ 
            return std::sqrt( mValue[0]*mValue[0] + mValue[1]*mValue[1] + mValue[2]*mValue[2] );
		}
		inline bool is_zero() const { return (x==0.0 && y==0.0 && z==0.0); }

	public:
		union {
			T mValue[3];
			struct
			{
				T x;
				T y;
				T z;
			};
			struct
			{
				T r;
				T g;
				T b;
			};
		};
	};

	/* Useful helper functions */
	template < typename T , typename Tfloat>
	inline T MixV(const T& a, const T& b, const Tfloat mix)
	{
		return T(tmix(a.x, b.x, mix), tmix(a.y, b.y, mix), tmix(a.z, b.z, mix));
	}

	typedef Vec3D<float> vector3f;
	typedef Vec3D<double> vector3d;
	typedef vector3d Color;
}

#endif													// __VECTOR3D_H__
