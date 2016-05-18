// Copyright (c) All Rights Reserved, Navié
//
// This does not touch the license for the Cinema 4D specific code functions used
// Please see the Cinema 4D license correspondingly. All other rights reserved.
//
// Author:	Samir Kharchi

#include "voxel_generator.h"
#include "fxp_voxelgen.h"
#include "api_effex.h"

/************************************************************************/
/* Requires at least Effex v2.70.77										*/
/*																		*/
/* This object generator creates render instances of a cube in each		*/
/* cell of a scalar grid channel (smoke,fire,fuel,temperature,custom)	*/
/*																		*/
/* It uses an FXScalarCellIterator to browse all cells of that channel	*/
/* the user provides the channel via link field in the Attribute Manager*/
/************************************************************************/
Bool VoxelGenerator::Init(GeListNode* node)
{
	BaseObject*		 op = (BaseObject*)node;
	BaseContainer* data = op->GetDataInstance();
	
	data->SetFloat(VGEN_SCALE, 0.95);
	data->SetFloat(VGEN_THRESHOLD,0.01);
	return true;
}

BaseObject* VoxelGenerator::GetVirtualObjects(BaseObject* op, HierarchyHelp* hh)
{	
	BaseContainer* data = op->GetDataInstance();
	BaseDocument* doc = op->GetDocument();

	/************************************************************************/
	Bool dirty = op->CheckCache(hh) || op->IsDirty(DIRTYFLAGS_DATA);
	if (!dirty)
		return op->GetCache(hh);
	
	/************************************************************************/
	Float t_scale		= data->GetFloat(VGEN_SCALE); if(t_scale == 0.0) return nullptr;
	Float t_threshold	= data->GetFloat(VGEN_THRESHOLD);

	Vector scale(t_scale); //Just the vector version of the uniform scale
		
	/************************************************************************/
	//Get the Effex Server (which contains all effex scenes)
	FXAPI::FXServer *server		= FXAPI::FXServer::Get(doc); if(!server) return nullptr;

	//Get the scalar channel's BaseObject interface from the link field
	BaseObject* channel_object	= op->GetDataInstance()->GetObjectLink(VGEN_CHANNEL, doc); if(!channel_object) return nullptr;
	
	//Find the Effex scene the scalar channel belongs to
	FXAPI::FXScene* effex_scene = server->GetEffexScene(channel_object); if(!effex_scene) return nullptr;	
	
	//Finally retrieve the scalar channel node from the effex scene */
	FXAPI::FXScalarChannel* ptr_channel = static_cast<FXAPI::FXScalarChannel*>(FXAPI::GetNode(effex_scene,channel_object,FXAPI::NodeRetrieveType_ScalarChannel));
	if(!ptr_channel) return nullptr;

	/************************************************************************/
	//We wanna place all voxel cubes under this null object
	BaseObject* ret = BaseObject::Alloc(Onull); if(!ret) { return nullptr; }
	//Create a reference cube
	BaseObject* voxel_cube = BaseObject::Alloc(Ocube); if(!voxel_cube) return ret;
	//Set Normal scale
	voxel_cube->GetDataInstance()->SetVector(PRIM_CUBE_LEN, Vector(1.0));
	//Renaming the cube
	voxel_cube->SetName("Voxel Reference");
	//Tell the cube to update bounding box etc.
	voxel_cube->Message(MSG_UPDATE);
	//Finally place the cube under our null object
	voxel_cube->InsertUnder(ret);
	
	/************************************************************************/
	//Now we create a scalar cell iterator which lets us browse all cells of a scalar channel
	//You can use C4D's AutoAlloc class for scope based construction/destruction
	//Otherwise just use FXAPI::FXScalarCellIterator::Alloc/Free
	AutoAlloc<FXAPI::FXScalarCellIterator> iterator;

	//Initialise it with our scalar channel, the cpu threads count we use and if grid border cells should be browsed as well
	if(iterator->Init(ptr_channel, 1, true)) 
	{
		/************************************************************************/
		/* The following part could be called from multiple cpu threads			*/
		/* but here we stay single-threaded										*/
		/************************************************************************/
		Int32 cpu_index = 0; //First cpu = 0

		//Call once per thread
		iterator->Start(cpu_index,false); //passing true would give a reverse iterator

		do //Now we browse with a do...while loop all cells of this cpu
		{
			//The iterator gives us the current cell value 
			double cell_scalar_value = iterator->GetValue(cpu_index);

			//Example: check for value threshold to only create instances in cells containing a value (e.g. smoke density)
			if(cell_scalar_value <= t_threshold)
				continue; //don't process this cell

			//Get the current cell's coordinate (in grid cell space)
			NAVIE_GLOBAL::VecInt3D xyz_cell = iterator->GetCoordinate(cpu_index);

			//Now convert coordinates from grid cell space to world space coordinates
			//which we will use to set the cube instances's position
			NAVIE_GLOBAL::vector3d xyz_global;
			if(FXAPI::GridToWorld(ptr_channel, xyz_cell, xyz_global, false)) 
			{
				//Conversion was fine. Now we create an instance object for this cell				
				BaseObject* voxel_instance = BaseObject::Alloc(Oinstance); if(!voxel_instance) continue;	
				//Set the reference voxel cube as source
				voxel_instance->GetDataInstance()->SetLink(INSTANCEOBJECT_LINK, voxel_cube);
				//Make it a render instance
				voxel_instance->GetDataInstance()->SetBool(INSTANCEOBJECT_RENDERINSTANCE, true); 
				//Renaming the instance to Voxel + its linear coordinate index
				voxel_instance->SetName("Voxel Reference" + String::IntToString(iterator->GetLinearCoordinate(cpu_index)));	

				//Set position (converting from an Effex vector3d to a c4d Vector on the fly)
				voxel_instance->SetAbsPos(FXAPI::Vec3DToVector(xyz_global));			
				//We also control the scale by the scalar cell value
				voxel_instance->SetAbsScale(scale * cell_scalar_value);
				
				//Tell the instance to update all its data
				voxel_instance->Message(MSG_UPDATE);
				//Finally place the instance under our null object
				voxel_instance->InsertUnderLast(ret);				
			}

		} while(iterator->SetNext(cpu_index)); //Go to next cell..
		/************************************************************************/
	}

	return ret;
}

/************************************************************************/
/* This shows how to create an Effex Candidate button which works		*/
/* in this non-effex object by letting the user provide the Effex Scene */
/* via a link field in the attribute manager							*/	
/*																		*/
/* See effector_sampler.cpp for a more automatic approach				*/
/************************************************************************/
Bool VoxelGenerator::Message(GeListNode* node, Int32 type, void* t_data)
{
	switch(type)
	{
	case MSG_DESCRIPTION_COMMAND:
		{
			DescriptionCommand *dc = (DescriptionCommand*)t_data;

			/* Handle Candidate button */
			FXAPI::FXServer *server = FXAPI::FXServer::Get(node->GetDocument());
			if(!server) break;

			BaseObject* op = (BaseObject *)node;
			//Effex Scene BaseObject interface from the link field
			BaseObject* scene = op->GetDataInstance()->GetObjectLink(VGEN_SCENE, node->GetDocument());

			if(dc->id[0].id==VGEN_CHANNEL_SELECTOR && scene)
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
				FXAPI::OpenCandidatePopup(false,items,t_types,op,VGEN_CHANNEL,false,true,0);
				return true;
			}
		}
		break;
	}
	return ObjectData::Message(node,type,t_data);
}

// be sure to use a unique ID obtained from www.plugincafe.com
#define ID_VOXELGENERATOR 1001156

Bool RegisterVoxelGenerator(void)
{
	return RegisterObjectPlugin(ID_VOXELGENERATOR, "VoxelGenerator", OBJECT_GENERATOR, VoxelGenerator::Alloc, "fxp_voxelgen", AutoBitmap("constraint.tif"), 0);
}
