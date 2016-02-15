// Copyright (c) All Rights Reserved, Navié
//
// This does not touch the license for the Cinema 4D specific code functions used
// Please see the Cinema 4D license correspondingly. All other rights reserved.
//
// Author: Samir Kharchi
#ifndef GLOBAL_PARTICLES_H
#define GLOBAL_PARTICLES_H

/************************************************************************/
/* PARTICLES                                                            */
/************************************************************************/

namespace NAVIE_GLOBAL
{
	namespace NAVIE_EFFEX
	{	
		const int FACTORYTYPES = 4;

		enum ParticleFactoryTypes
		{
			ParticleFactoryTypes_Passive = 0,
			ParticleFactoryTypes_Vorticity,
			ParticleFactoryTypes_Liquid,
			ParticleFactoryTypes_Foam,

			ParticleFactoryTypes_Unknown = 100
		};
		
		const Int32_C4D PARTICLEGROUP_BITS_PASSIVE = 1;
		const Int32_C4D PARTICLEGROUP_BITS_LIQUID = 2;
		const Int32_C4D PARTICLEGROUP_BITS_VORTEX = 4;
		const Int32_C4D PARTICLEGROUP_BITS_DIFFUSE = 8;

		inline NAVIE_GLOBAL::NAVIE_EFFEX::ParticleFactoryTypes  FlagsToParticleFactory(const Int32_C4D flags)
		{
			if(flags&PARTICLEGROUP_BITS_LIQUID)
				return NAVIE_GLOBAL::NAVIE_EFFEX::ParticleFactoryTypes_Liquid;
			else if(flags&PARTICLEGROUP_BITS_PASSIVE)
				return NAVIE_GLOBAL::NAVIE_EFFEX::ParticleFactoryTypes_Passive;
			else if(flags&PARTICLEGROUP_BITS_VORTEX)
				return NAVIE_GLOBAL::NAVIE_EFFEX::ParticleFactoryTypes_Vorticity;

			return NAVIE_GLOBAL::NAVIE_EFFEX::ParticleFactoryTypes_Foam;
		}

		inline Int32_C4D ParticleFactoryToFlags(const NAVIE_GLOBAL::NAVIE_EFFEX::ParticleFactoryTypes factory)
		{
			Int32_C4D flags = 0;
			switch(factory) {
				case NAVIE_GLOBAL::NAVIE_EFFEX::ParticleFactoryTypes_Foam:
				flags |= PARTICLEGROUP_BITS_DIFFUSE;
				break;
				case NAVIE_GLOBAL::NAVIE_EFFEX::ParticleFactoryTypes_Liquid:
				flags |= PARTICLEGROUP_BITS_LIQUID;
				break;
				case NAVIE_GLOBAL::NAVIE_EFFEX::ParticleFactoryTypes_Passive:
				flags |= PARTICLEGROUP_BITS_PASSIVE;
				break;
				case NAVIE_GLOBAL::NAVIE_EFFEX::ParticleFactoryTypes_Vorticity:
				flags |= PARTICLEGROUP_BITS_VORTEX;
				break;
                default: break;
			}
			return flags;
		}
	}
}
#endif