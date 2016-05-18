// Copyright (c) All Rights Reserved, Navié
//
// This does not touch the license for the Cinema 4D specific code functions used
// Please see the Cinema 4D license correspondingly. All other rights reserved.
//
// Author:	Samir Kharchi

#include "effector_sampler.h"
#include "fxp_sampleeffector.h"

/************************************************************************/
/* This implements a value driven MoGraph Effector						*/
/* It shows how to sample an Effex grid channel at an arbitrary position*/
/* in space and how to check if that position is inside the grid at all */
/************************************************************************/

Bool Effector_Sampler::InitEffector(GeListNode* node)
{
	BaseObject* op = (BaseObject*)node;
	if (!op) return false;

	BaseContainer* bc = op->GetDataInstance();
	if (!bc) return false;

	bc->SetFloat(ID_MG_BASEEFFECTOR_MINSTRENGTH, -1.0);
	bc->SetBool(ID_MG_BASEEFFECTOR_POSITION_ACTIVE, true);
	bc->SetVector(ID_MG_BASEEFFECTOR_POSITION, Vector(50.0));

	bc->SetFloat(SEFF_SCALE, 0.01);
	bc->SetInt32(SEFF_WEIGHT_TARGET,SEFF_WEIGHT_TARGET_ALL);
	return true;
}

void Effector_Sampler::InitPoints(BaseObject* op, BaseObject* gen, BaseDocument* doc, EffectorDataStruct* data, MoData* md, BaseThread* thread)
{
	BaseContainer* bc = op->GetDataInstance(); if (!bc) return;

	size = bc->GetFloat(SEFF_SCALE);
	smode = bc->GetInt32(SEFF_WEIGHT_TARGET);

	effex_scene = nullptr;
	channel_to_sample = nullptr;
	
	/************************************************************************/
	//Get the Effex Server (which contains all effex scenes)
	FXAPI::FXServer *server		= FXAPI::FXServer::Get(doc); if(!server) return;

	//Get the scalar channel's BaseObject interface from the link field
	BaseObject* channel_object	= op->GetDataInstance()->GetObjectLink(SEFF_CHANNEL, doc); if(!channel_object) return;
	
	//Find the Effex scene the scalar channel belongs to
	effex_scene = server->GetEffexScene(channel_object); if(!effex_scene) return;	
	
	//Finally retrieve the scalar channel node from the effex scene */
	channel_to_sample = static_cast<FXAPI::FXScalarChannel*>(FXAPI::GetNode(effex_scene,channel_object,FXAPI::NodeRetrieveType_ScalarChannel));
	if(!channel_to_sample) return;
	
	//Store the (channel's range) maximum that values in this channel can have
	channel_max_rec = 1.0 / channel_to_sample->GetRangeMaximum();

	AddEffectorDependence(channel_object);
}

void Effector_Sampler::CalcPointValue(BaseObject* op, BaseObject* gen,	BaseDocument* doc, EffectorDataStruct* data, Int32 index, MoData* md, const Vector& globalpos, Float fall_weight)
{
	//Don't operate without a channel to sample
	if(!channel_to_sample || !effex_scene) return;

	//First convert from c4d Vector to an Effex vector3d
	NAVIE_GLOBAL::vector3d fx_physicalpos = FXAPI::VectorToVec3d<double>(globalpos);
		
	//Then we transform the global space c4d position into a global physical (simulation) space position
	FXAPI::WorldToPhysical(effex_scene, fx_physicalpos);
	
	//Now let's ask the channel if this position is inside the grid bounds
	if(channel_to_sample->Inside(fx_physicalpos, true)) 
	{
		//The position is inside, so now we can sample a value from the scalar channel's grid
		//at the given physical position (and therefore at the original globalpos)
		double channel_value_sample = channel_to_sample->GetValue(fx_physicalpos);

		//Bring value into normalized range [0.0-1.0)
		channel_value_sample *= channel_max_rec;
		//And also the size and falloff weight can be multiplied already here
		channel_value_sample *= size * fall_weight;

		//This casts the EffectorStrengths structure for setting of values
		EffectorStrengths* es = (EffectorStrengths*)data->strengths;

		switch(smode) {
			default:
			{
				//This one just iterates through the "blends" which are the raw driver values and is slightly faster
				Float* buf = data->strengths;
				for(Int32 i = 0; i < BLEND_COUNT; i++, buf++) 
					(*buf) = channel_value_sample;
			} 
			break;
			case SEFF_WEIGHT_TARGET_POS:		es->pos			= Vector(channel_value_sample); break;
			case SEFF_WEIGHT_TARGET_ROT:		es->rot			= Vector(channel_value_sample); break;
			case SEFF_WEIGHT_TARGET_SCALE:		es->scale		= Vector(channel_value_sample); break;
			case SEFF_WEIGHT_TARGET_COLOROPACITY:es->col		= Vector(channel_value_sample); break;
			case SEFF_WEIGHT_TARGET_VISIBILITY:	es->other.z		= channel_value_sample; break;
			case SEFF_WEIGHT_TARGET_WEIGHT:		es->other2.x	= channel_value_sample; break;
			case SEFF_WEIGHT_TARGET_INDEX:		es->other2.y	= channel_value_sample; break;
			case SEFF_WEIGHT_TARGET_TIME:		es->other2.z	= channel_value_sample; break;
		}
	}
}

Vector Effector_Sampler::CalcPointColor(BaseObject* op, BaseObject* gen, BaseDocument* doc, EffectorDataStruct* data, Int32 index, MoData* md, const Vector& globalpos, Float fall_weight)
{
	//Don't operate without a channel to sample
	if(!channel_to_sample || !effex_scene) return Vector(0.0);

	//First convert from c4d Vector to an Effex vector3d
	NAVIE_GLOBAL::vector3d fx_physicalpos = FXAPI::VectorToVec3d<double>(globalpos);
		
	//Then we transform the global space c4d position into a global physical (simulation) space position
	FXAPI::WorldToPhysical(effex_scene, fx_physicalpos);
	
	//Now let's ask the channel if this position is inside the grid bounds
	if(channel_to_sample->Inside(fx_physicalpos, true)) 
	{
		//The position is inside, so now we can sample a value from the scalar channel's grid
		//at the given physical position (and therefore at the original globalpos)
		double channel_value_sample = channel_to_sample->GetValue(fx_physicalpos);
		//Bring it into normalized range [0.0-1.0)
		channel_value_sample *= channel_max_rec;
		//And also the size and falloff weight can be multiplied already here
		channel_value_sample *= size * fall_weight;

		return Vector(FMin(1.0,channel_value_sample));
	}
	return Vector(0.0);
}

/************************************************************************/
/* This shows how to create an Effex Candidate button which works		*/
/* in this non-effex object by searching for effex scenes in the doc	*/	
/************************************************************************/
//recursively searches through the document to find an effex scene
static bool find_scene(BaseObject*& scene) 
{
	while(scene != nullptr) 
	{
		if(scene->GetType() == EFFEX_SCENE)
			return true;

		BaseObject* temp = scene->GetDown();
		if(find_scene(temp)) 
		{
			scene = temp;
			return true;
		}
		scene = scene->GetNext();
	}
	return false;
}

Bool Effector_Sampler::Message(GeListNode* node, Int32 type, void* t_data)
{
	switch(type)
	{
	case MSG_DESCRIPTION_COMMAND:
		{
			/* Handle Candidate button */
			DescriptionCommand *dc = (DescriptionCommand*)t_data;
			
			//Get the Effex Server (which contains all effex scenes)
			FXAPI::FXServer *server = FXAPI::FXServer::Get(node->GetDocument());
			if(!server) break;

			BaseObject* op = (BaseObject *)node;
			//Effex Scene BaseObject interface from the document
			BaseObject* scene = node->GetDocument()->GetFirstObject();
			if(!find_scene(scene)) break;			

			if(dc->id[0].id==SEFF_CHANNEL_SELECTOR)
			{
				//Get the Effex Scene node which should contain the scalar channel
				FXAPI::FXScene* effex_scene = server->GetEffexScene(scene); 
				if(!effex_scene) break;

				/* Create a list of scalar channels that are already in the scene that the user may want to use.
				We use GetNodes to search the scene for channels */
				std::vector<FXAPI::FXBase*> items;
				FXAPI::GetNodes(effex_scene,NULL,items,FXAPI::NodeRetrieveType_ScalarChannel);

				/* Create a list of compatible channel types (for the candidate buttons "Create.." submenu) */
				FXAPI::FXTypeInfos t_types;
				t_types.push_back(FXAPI::FXTypeInfo(EFFEX_CHANNEL_SCALAR,"Scalar Channel")); //The naming part is only for safe-guarding
				
				/* Pass all the info to the Candidate button Popup */
				BaseObject *op = (BaseObject*)node;
				FXAPI::OpenCandidatePopup(false,items,t_types,op,SEFF_CHANNEL,false,true,0);
			}
		}
		break;
	}
	return EffectorData::Message(node,type,t_data);
}
// be sure to use a unique ID obtained from www.plugincafe.com
#define ID_SAMPLEEFFECTOR 1001157

Bool RegisterSampleEffector(void)
{
	return RegisterEffectorPlugin(ID_SAMPLEEFFECTOR, "Sample Channel Effector", OBJECT_CALL_ADDEXECUTION, Effector_Sampler::Alloc, "fxp_sampleeffector", AutoBitmap("operator.tif"), 0);
}


