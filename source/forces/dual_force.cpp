#include "dual_force.h"
#include "fxp_dualforce.h"
#include "c4d_symbols.h"

// initialize settings
Bool DualForce::Init(GeListNode *node)
{
	BaseObject		*op		= (BaseObject*)node;
	BaseContainer *data = op->GetDataInstance();

	data->SetFloat(DF_NOISEGRADIENT_INTENSITY,1.0);
	return Base::Init(node);
}

bool DualForce::FillData( BaseObject* node )
{
	/* Retrieve the interface settings */
	BaseContainer *data = node->GetDataInstance();
	intensity		= data->GetFloat(DF_NOISEGRADIENT_INTENSITY);
	return true;
}

bool DualForce::FillPorts( BaseObject* node , FXAPI::FXServer* server )
{
	/* Retrieve interface port data */
	return true;
}

void DualForce::ClearPorts( void )
{
	/* Free any interface port data */
}

void DualForce::GetSubType( int& subtype ) const
{
	// By default a force is always dual (this is the same as not overloading this function at all)
	Base::GetSubType(subtype);

	// If you want a pure grid force (e.g. used in the fluid dynamics nodes) uncomment the following line:
	//subtype = 0; subtype |= (1 << nst_grid); //We set the grid bit

	// If you want a pure particle force (e.g. used in the POP::Forces) uncomment the following line:
	//subtype = 0; subtype |= (1 << nst_particle); //We set the particle bit
}

bool DualForce::PortsDirty( FXAPI::FXServer* server ) const
{
	/* Here you can check ports if they are dirty and return true if so */
	return false;
}

/* Precompute any data */
bool DualForce::Precompute( FXAPI::FXServer* server )
{
	BaseObject* cam = GetActiveDocument()->GetActiveBaseDraw()->GetSceneCamera(GetActiveDocument());
	cam_pos = FXAPI::VectorToVec3d<double>(cam->GetMg().off); //Convert into Effex vector3d

	FXAPI::FXScene* scene = server->GetEffexScene(this->get_wrapper()); //Retrieve the Effex Scene from server that this node belongs to
	//FXAPI::FXScene* scene = server->GetEffexScene((BaseObject*)this->Get()); //Same as above but using the C4D BaseObject pointer
	
	FXAPI::WorldToPhysical(scene,cam_pos); //Convert from world space into physical space
	return true; //All is fine
}

/* Precompute any multiprocessor specific data */
bool DualForce::PrecomputeMP( FXAPI::FXServer* server )
{
	return true; //All is fine
}

/* Evaluate your code here */
void DualForce::Process( void* t_data )
{
	FXAPI::ProcessData* base_data = static_cast<FXAPI::ProcessData*>(t_data);
	switch(base_data->mode)
	{
	case 0: //Grid Force
		{
			FXAPI::ProcessDataGrids* plugindata = static_cast<FXAPI::ProcessDataGrids*>(base_data);
			NAVIE_GLOBAL::vector3d final_force = (cam_pos - plugindata->physical_position).normal();

			//Assign the normalised final force multiplied by the current constraint value
			plugindata->op_result += final_force * plugindata->constraint_value * intensity;
		}
		break;
	case 1: //Particle Force
		{
			FXAPI::ProcessDataParticles* plugindata = static_cast<FXAPI::ProcessDataParticles*>(base_data);

			NAVIE_GLOBAL::vector3d final_force = (cam_pos - plugindata->physical_position).normal();

			//Assign the normalised final force multiplied by the current constraint value
			plugindata->op_result += final_force * plugindata->constraint_value * intensity;
		}
	}
}

void DualForce::FreePrecompute( void )
{
	/* Free precomputed data */
}

/************************************************************************/
// be sure to use a unique ID obtained from www.plugincafe.com
#define ID_DualForce 1001155

Bool RegisterDualForce(void)
{
	return RegisterFXForcePlugin
		(ID_DualForce
		,GeLoadString(IDS_DUALFORCE)
		,OBJECT_GENERATOR
		,DualForce::Alloc
		,"fxp_dualforce"
		,AutoBitmap("force.tif"),0);
}
