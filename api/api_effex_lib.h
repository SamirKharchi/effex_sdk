// Copyright (c) All Rights Reserved, Navié
//
// This does not touch the license for the Cinema 4D specific code functions used
// Please see the Cinema 4D license correspondingly. All other rights reserved.
//
// Author: Samir Kharchi
#ifndef API_EFFEX_LIB_H
#define API_EFFEX_LIB_H

#include "api_effex_scene.h"
#include "api_effex_nodeids.h"

/************************************************************************/
/* Trigger a library call */
#define EFFEXPARTICLE_LIBID 1033628
template < typename CUSTOMLIB_CLASS >
CUSTOMLIB_CLASS* CheckCustomLib(Int32_C4D offset, C4DLibrary* lib)
{
	return static_cast<CUSTOMLIB_CLASS*>(CheckLib(EFFEXPARTICLE_LIBID, offset, &lib));
}

namespace NAVIE_GLOBAL
{
	namespace NAVIE_EFFEX
	{	
		namespace NAVIE_API
		{
#define get_library(Tlibrary, _func,_default,libcache)\
	Tlibrary* vlib = CheckCustomLib<Tlibrary>(LIBOFFSET(Tlibrary, _func),libcache); \
	if (!vlib || !vlib->_func) return _default;

#define get_library_set(Tlibrary, _func,libcache)\
	Tlibrary* vlib = CheckCustomLib<Tlibrary>(LIBOFFSET(Tlibrary, _func),libcache); \
	if (!vlib || !vlib->_func) return;

#define get_library_sub(Tlibrary,  Tsub,_func,_default,libcache)\
	Tlibrary* vlib = static_cast<Tlibrary*>(libcache); \
	if (!vlib || !vlib->Tsub || !vlib->Tsub->_func) return _default;

#define get_library_set_sub(Tlibrary, Tsub, _func,libcache)\
	Tlibrary* vlib = static_cast<Tlibrary*>(libcache); \
	if (!vlib || !vlib->Tsub || !vlib->Tsub->_func) return;

/************************************************************************/
#define get_library_value_0(tlib,Twrapper,_func) (((Twrapper*)this)->*(tlib->_func))(); 
#define get_library_value_1(tlib,Twrapper,_func,_arg1) (((Twrapper*)this)->*(tlib->_func))(_arg1); 
#define get_library_value_2(tlib,Twrapper,_func,_arg1,_arg2) (((Twrapper*)this)->*(tlib->_func))(_arg1,_arg2); 
#define get_library_value_3(tlib,Twrapper,_func,_arg1,_arg2,_arg3) (((Twrapper*)this)->*(tlib->_func))(_arg1,_arg2,_arg3); 
#define get_library_value_4(tlib,Twrapper,_func,_arg1,_arg2,_arg3,_arg4) (((Twrapper*)this)->*(tlib->_func))(_arg1,_arg2,_arg3,_arg4); 
#define get_library_value_5(tlib,Twrapper,_func,_arg1,_arg2,_arg3,_arg4,_arg5) (((Twrapper*)this)->*(tlib->_func))(_arg1,_arg2,_arg3,_arg4,_arg5); 
#define get_library_value_6(tlib,Twrapper,_func,_arg1,_arg2,_arg3,_arg4,_arg5,_arg6) (((Twrapper*)this)->*(tlib->_func))(_arg1,_arg2,_arg3,_arg4,_arg5,_arg6); 
/************************************************************************/
#define get_library_internalvalue_0(tlib,Twrapper,_internalfunc,_func) (((Twrapper*)this->_internalfunc)->*(tlib->_func))(); 
#define get_library_internalvalue_1(tlib,Twrapper,_internalfunc,_func,_arg1) (((Twrapper*)this->_internalfunc)->*(tlib->_func))(_arg1); 
#define get_library_internalvalue_2(tlib,Twrapper,_internalfunc,_func,_arg1,_arg2) (((Twrapper*)this->_internalfunc)->*(tlib->_func))(_arg1,_arg2); 
#define get_library_internalvalue_3(tlib,Twrapper,_internalfunc,_func,_arg1,_arg2,_arg3) (((Twrapper*)this->_internalfunc)->*(tlib->_func))(_arg1,_arg2,_arg3); 
#define get_library_internalvalue_4(tlib,Twrapper,_internalfunc,_func,_arg1,_arg2,_arg3,_arg4) (((Twrapper*)this->_internalfunc)->*(tlib->_func))(_arg1,_arg2,_arg3,_arg4); 
#define get_library_internalvalue_5(tlib,Twrapper,_internalfunc,_func,_arg1,_arg2,_arg3,_arg4,_arg5) (((Twrapper*)this->_internalfunc)->*(tlib->_func))(_arg1,_arg2,_arg3,_arg4,_arg5); 
/************************************************************************/
#define get_library_value_0_cast(tlib,Twrapper,Tcast,_func) (Tcast*)(((Twrapper*)this)->*(tlib->_func))(); 
#define get_library_value_1_cast(tlib,Twrapper,Tcast,_func,_arg1) (Tcast*)(((Twrapper*)this)->*(tlib->_func))(_arg1); 
#define get_library_value_2_cast(tlib,Twrapper,Tcast,_func,_arg1,_arg2) (Tcast*)(((Twrapper*)this)->*(tlib->_func))(_arg1,_arg2); 
#define get_library_value_3_cast(tlib,Twrapper,Tcast,_func,_arg1,_arg2,_arg3) (Tcast*)(((Twrapper*)this)->*(tlib->_func))(_arg1,_arg2,_arg3); 
#define get_library_value_4_cast(tlib,Twrapper,Tcast,_func,_arg1,_arg2,_arg3,_arg4) (Tcast*)(((Twrapper*)this)->*(tlib->_func))(_arg1,_arg2,_arg3,_arg4); 
#define get_library_value_5_cast(tlib,Twrapper,Tcast,_func,_arg1,_arg2,_arg3,_arg4,_arg5) (Tcast*)(((Twrapper*)this)->*(tlib->_func))(_arg1,_arg2,_arg3,_arg4,_arg5); 
/************************************************************************/
#define get_library_internalvalue_0_cast(tlib,Twrapper,_internalfunc,Tcast,_func) (Tcast*)(((Twrapper*)this->_internalfunc)->*(tlib->_func))(); 
#define get_library_internalvalue_1_cast(tlib,Twrapper,_internalfunc,Tcast,_func,_arg1) (Tcast*)(((Twrapper*)this->_internalfunc)->*(tlib->_func))(_arg1); 
#define get_library_internalvalue_2_cast(tlib,Twrapper,_internalfunc,Tcast,_func,_arg1,_arg2) (Tcast*)(((Twrapper*)this->_internalfunc)->*(tlib->_func))(_arg1,_arg2); 
#define get_library_internalvalue_3_cast(tlib,Twrapper,_internalfunc,Tcast,_func,_arg1,_arg2,_arg3) (Tcast*)(((Twrapper*)this->_internalfunc)->*(tlib->_func))(_arg1,_arg2,_arg3); 
#define get_library_internalvalue_4_cast(tlib,Twrapper,_internalfunc,Tcast,_func,_arg1,_arg2,_arg3,_arg4) (Tcast*)(((Twrapper*)this->_internalfunc)->*(tlib->_func))(_arg1,_arg2,_arg3,_arg4); 
#define get_library_internalvalue_5_cast(tlib,Twrapper,_internalfunc,Tcast,_func,_arg1,_arg2,_arg3,_arg4,_arg5) (Tcast*)(((Twrapper*)this->_internalfunc)->*(tlib->_func))(_arg1,_arg2,_arg3,_arg4,_arg5); 
/************************************************************************/
#define get_library_funcvalue_0(tlib,_func) tlib->_func();
#define get_library_funcvalue_1(tlib,_func,_arg1) tlib->_func(_arg1); 
#define get_library_funcvalue_2(tlib,_func,_arg1,_arg2) tlib->_func(_arg1,_arg2); 
#define get_library_funcvalue_3(tlib,_func,_arg1,_arg2,_arg3) tlib->_func(_arg1,_arg2,_arg3); 
#define get_library_funcvalue_4(tlib,_func,_arg1,_arg2,_arg3,_arg4) tlib->_func(_arg1,_arg2,_arg3,_arg4); 
#define get_library_funcvalue_5(tlib,_func,_arg1,_arg2,_arg3,_arg4,_arg5) tlib->_func(_arg1,_arg2,_arg3,_arg4,_arg5); 
#define get_library_funcvalue_6(tlib,_func,_arg1,_arg2,_arg3,_arg4,_arg5,_arg6) tlib->_func(_arg1,_arg2,_arg3,_arg4,_arg5,_arg6); 
#define get_library_funcvalue_7(tlib,_func,_arg1,_arg2,_arg3,_arg4,_arg5,_arg6,_arg7) tlib->_func(_arg1,_arg2,_arg3,_arg4,_arg5,_arg6,_arg7); 
#define get_library_funcvalue_8(tlib,_func,_arg1,_arg2,_arg3,_arg4,_arg5,_arg6,_arg7,_arg8) tlib->_func(_arg1,_arg2,_arg3,_arg4,_arg5,_arg6,_arg7,_arg8); 
/************************************************************************/
#define get_library_funcvalue_0_cast(tlib,Tcast,_func) (Tcast*)tlib->_func();
#define get_library_funcvalue_1_cast(tlib,Tcast,_func,_arg1) (Tcast*)tlib->_func(_arg1); 
#define get_library_funcvalue_2_cast(tlib,Tcast,_func,_arg1,_arg2) (Tcast*)tlib->_func(_arg1,_arg2); 
#define get_library_funcvalue_3_cast(tlib,Tcast,_func,_arg1,_arg2,_arg3) (Tcast*)tlib->_func(_arg1,_arg2,_arg3); 
#define get_library_funcvalue_4_cast(tlib,Tcast,_func,_arg1,_arg2,_arg3,_arg4) (Tcast*)tlib->_func(_arg1,_arg2,_arg3,_arg4); 
#define get_library_funcvalue_5_cast(tlib,Tcast,_func,_arg1,_arg2,_arg3,_arg4,_arg5) (Tcast*)tlib->_func(_arg1,_arg2,_arg3,_arg4,_arg5); 
#define get_library_funcvalue_6_cast(tlib,Tcast,_func,_arg1,_arg2,_arg3,_arg4,_arg5,_arg6) (Tcast*)tlib->_func(_arg1,_arg2,_arg3,_arg4,_arg5,_arg6); 
#define get_library_funcvalue_7_cast(tlib,Tcast,_func,_arg1,_arg2,_arg3,_arg4,_arg5,_arg6,_arg7) (Tcast*)tlib->_func(_arg1,_arg2,_arg3,_arg4,_arg5,_arg6,_arg7); 
#define get_library_funcvalue_8_cast(tlib,Tcast,_func,_arg1,_arg2,_arg3,_arg4,_arg5,_arg6,_arg7,_arg8) (Tcast*)tlib->_func(_arg1,_arg2,_arg3,_arg4,_arg5,_arg6,_arg7,_arg8); 
		}
	}
}
#endif