// Copyright (c) All Rights Reserved, Navié
//
// This does not touch the license for the Cinema 4D specific code functions used
// Please see the Cinema 4D license correspondingly. All other rights reserved.
//
// Author:	Samir Kharchi

#include "c4d.h"
#include "c4d_baseeffectorplugin.h"
#include "api_effex.h"

class Effector_Sampler : public EffectorData
{
private:
	Float size{ 0.01 }; //Effector global intensity
	Int32 smode{ 0 };	//Effector strengths mode - user defines which strength to control
	Float channel_max_rec{ 1.0 }; //Stores the reciprocal of the maximum value the scalar channel can take

	FXAPI::FXScalarChannel* channel_to_sample	{ nullptr }; //The channel we want to sample
	FXAPI::FXScene*			effex_scene			{ nullptr }; //The effex scene the channel belongs to

public:
	virtual Bool	InitEffector	(GeListNode* node);
	virtual void	InitPoints		(BaseObject* op, BaseObject* gen, BaseDocument* doc, EffectorDataStruct* data, MoData* md, BaseThread* thread);
	virtual void	CalcPointValue	(BaseObject* op, BaseObject* gen, BaseDocument* doc, EffectorDataStruct* data, Int32 index, MoData* md, const Vector& globalpos, Float fall_weight);
	virtual Vector	CalcPointColor	(BaseObject* op, BaseObject* gen, BaseDocument* doc, EffectorDataStruct* data, Int32 index, MoData* md, const Vector& globalpos, Float fall_weight);
	
	virtual Bool	Message			(GeListNode* node, Int32 type, void* t_data) override;

	static NodeData* Alloc(void) { return NewObjClear(Effector_Sampler); }
};