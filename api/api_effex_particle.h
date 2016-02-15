// Copyright (c) All Rights Reserved, Navié
//
// This does not touch the license for the Cinema 4D specific code functions used
// Please see the Cinema 4D license correspondingly. All other rights reserved.
//
// Author: Samir Kharchi
#ifndef API_EFFEX_PARTICLE_H
#define API_EFFEX_PARTICLE_H

#include "c4d.h"
#include "vector/vector3d.h"
#include "fx_property.h"

namespace NAVIE_GLOBAL
{
	namespace NAVIE_EFFEX
	{	
		class iNodeBaseWrapper;

		namespace NAVIE_API
		{
			class FXParticle
			{
			private:
				FXParticle();
				~FXParticle();

			public:
				const vector3d&	GetPosition			(void) const;
				const vector3d&	GetVelocity			(void) const;
				double	GetAge				(void) const; //Given in seconds
				double	GetProperty_Scalar	(const double& _default	, const ParticleProperty & prop, const iNodeBaseWrapper* node_interface = nullptr) const;
				vector3d GetProperty_Vector	(const vector3d& _default	, const ParticleProperty & prop, const iNodeBaseWrapper* node_interface = nullptr) const;
				bool	GetProperty_State	(const bool& _default	, const ParticleProperty & prop, const iNodeBaseWrapper* node_interface = nullptr) const;

				void	SetPosition			(const vector3d& pos);
				void	SetVelocity			(const vector3d& vel);
				void	SetAge				(const int age); //Given in frames
				bool	SetProperty_Scalar	(const double val	, const ParticleProperty &prop, const iNodeBaseWrapper* node_interface = nullptr);
				bool	SetProperty_Vector	(const vector3d& val , const ParticleProperty & prop, const iNodeBaseWrapper* node_interface = nullptr);
				bool	SetProperty_State	(const bool val	, const ParticleProperty & prop, const iNodeBaseWrapper* node_interface = nullptr);
			};
		}
	}
}

#endif