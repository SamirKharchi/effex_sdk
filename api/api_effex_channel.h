// Copyright (c) All Rights Reserved, Navié
//
// This does not touch the license for the Cinema 4D specific code functions used
// Please see the Cinema 4D license correspondingly. All other rights reserved.
//
// Author: Samir Kharchi
#ifndef API_EFFEX_CHANNEL_H
#define API_EFFEX_CHANNEL_H

#include "api_effex_base.h"

namespace NAVIE_GLOBAL
{
	namespace NAVIE_EFFEX
	{
		class EffexParticle;
		class ParticleIterator;

		namespace NAVIE_API
		{
			class FXScalarChannel : public FXBase
			{
			private:
				FXScalarChannel();
				~FXScalarChannel();

			public:
				double		GetRangeMinimum	(void) const;
				double		GetRangeMaximum	(void) const;
				double		GetResetValue	(void) const;

				void		GetBounds		(vector3d& ref_minimum, vector3d& ref_maximum);
				bool		Inside			(const vector3d& physical_position, const bool excludeborders = false);
				bool		InsideGrid		(const vector3d& physical_position, const bool excludeborders = false);

				double		GetValue		(const vector3d& physical_position) const;
				bool		Resize			(vector3d& ref_minimum, vector3d& ref_maximum);
				void		SetValue		(const vector3d& physical_position, const double value);
				void		UpdateBounds	(void);
			};

			class FXFuelChannel : public FXScalarChannel
			{
			private:
				FXFuelChannel();
				~FXFuelChannel();

			public:
				double GetIgnitionTemperature()	const;
			};

			class FXFireChannel : public FXScalarChannel
			{
			private:
				FXFireChannel();
				~FXFireChannel();

			public:
				double GetCoolingPoint()	const;
				double GetDeathRate()		const;
				double GetAfterLife()		const;
			};

			class FXVectorChannel : public FXBase
			{
			private:
				FXVectorChannel();
				~FXVectorChannel();

			public:
				const vector3d&		GetRangeMinimum	(void) const;
				const vector3d&		GetRangeMaximum	(void) const;
				const vector3d&		GetResetValue	(void) const;

				void		GetBounds		(vector3d& ref_minimum, vector3d& ref_maximum);
				bool		Inside			(const vector3d& physical_position, const bool excludeborders = false);
				bool		InsideGrid		(const vector3d& physical_position, const bool excludeborders = false);

				vector3d	GetValue		(const vector3d& physical_position) const;
				bool		Resize			(vector3d& ref_minimum, vector3d& ref_maximum);
				void		SetValue		(const vector3d& physical_position, const vector3d& value);
				void		UpdateBounds	(void);
			};

			/************************************************************************/
			/* Cell Iterator - for browsing of internal grid cells */
			class FXScalarCellIterator
			{
			public:
				double	GetValue(const int cpu) ;
				double	GetNeighborValue(const int cpu, short x, short y, short z);
				void	SetValue(const int cpu, const double& value) ;

				bool Init				(FXScalarChannel* channel);
				bool Init				(FXScalarChannel* channel, int cpus, bool include_borders = false);

				inline void Start		(const int cpu, bool reverse = false) ;
				inline bool SetNext		(const int cpu) ;
				inline bool SetPrev		(const int cpu) ;

				inline void Offset		(Int32_C4D offset);
				inline bool IsValid		(void) const;
				inline bool OffsetSafe	(Int32_C4D offset);

				static FXScalarCellIterator* Alloc();
				static void Free(FXScalarCellIterator*& p);
			};

			class FXVectorCellIterator
			{
			public:
				vector3d GetValue(const int cpu) ;
				vector3d GetNeighborValue(const int cpu, short x, short y, short z);
				void	SetValue(const int cpu, const vector3d& value) ;

				bool Init				(FXVectorChannel* channel);
				bool Init				(FXVectorChannel* channel, int cpus, bool include_borders = false);

				inline void Start		(const int cpu, bool reverse = false) ;
				inline bool SetNext		(const int cpu) ;
				inline bool SetPrev		(const int cpu) ;

				inline void Offset		(Int32_C4D offset);
				inline bool IsValid		(void) const;
				inline bool OffsetSafe	(Int32_C4D offset);

				static FXVectorCellIterator* Alloc();
				static void Free(FXVectorCellIterator*& p);
			};
		}
	}
}

#endif //API_EFFEX_PARTICLE_H