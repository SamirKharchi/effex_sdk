#include "particle_constraint.h"
#include "c4d_symbols.h"
#include "fxp_particleconstraint.h"

// initialize settings
Bool ParticleConstraint::Init(GeListNode *node)
{
	BaseObject		*op		= (BaseObject*)node;
	BaseContainer *data = op->GetDataInstance();

	data->SetFloat(PARTICLECONSTRAINT_OFFSET,0.0);
	return Base::Init(node);
}

bool ParticleConstraint::FillData( BaseObject* node )
{
	/* Retrieve the interface settings */
	BaseContainer *data = node->GetDataInstance();
	offset = data->GetFloat(PARTICLECONSTRAINT_OFFSET);
	return true;
}

bool ParticleConstraint::FillPorts( BaseObject* node , FXAPI::FXServer* server )
{
	/* Retrieve interface port data */
	return true;
}

void ParticleConstraint::ClearPorts( void )
{
	/* Free any interface port data */
}

bool ParticleConstraint::IsParticleConstraint( void ) const
{
	/* true if this is a particle constraint */
	return true;
}

void ParticleConstraint::PrecomputeConstraint( void* t_data )
{
	/* precompute data if necessary */
}

void ParticleConstraint::FreePrecomputeConstraint( void )
{
	/* free any precomputed data */
}

inline double get_simulation_time(void* local_data)
{
	FXAPI::FXBase* calling_node = static_cast<FXAPI::FXBase*>(local_data); 
	if(calling_node) 
	{
		/* Retrieve the scene the node belongs to */
		FXAPI::FXScene* scene = calling_node->GetScene();
		if(scene) 
		{
			/* Retrieve the current simulation info from the scene */
			const SimulationInfo* info = calling_node->GetScene()->GetSimulationInfo();
			return info->simtime;
		}
	}
	return 0.0;
}

/* Local data holds the node that called this constraint */
bool ParticleConstraint::GetConstraint( const NAVIE_GLOBAL::vector3d& position, double& src_value, void* local_data, int cpu /*= 0*/ )
{
	double full_offset = get_simulation_time(local_data) + offset;

	/* Evaluate your code here and set src_value */
	src_value = (sin(position.x + full_offset) + sin(position.y + full_offset) + sin(position.z + full_offset)) * 0.3333;
	return src_value != 0.0;
}

bool ParticleConstraint::GetParticleConstraint( const NAVIE_GLOBAL::vector3d& position, double& src_value, void* local_data, int cpu /*= 0*/, const void* t_particle /*= NULL*/ )
{
	double full_offset = get_simulation_time(local_data) + offset;

	/* Evaluate your code here and set src_value */
	src_value = (sin(position.x + full_offset) + sin(position.y + full_offset) + sin(position.z + full_offset)) * 0.3333;
	return src_value != 0.0;
}

/************************************************************************/
// be sure to use a unique ID obtained from www.plugincafe.com
#define ID_PARTICLECONSTRAINT 1001153

Bool RegisterParticleConstraint(void)
{
	return RegisterFXConstraintPlugin
		(ID_PARTICLECONSTRAINT
		,GeLoadString(IDS_PARTICLECONSTRAINT)
		,OBJECT_GENERATOR
		,ParticleConstraint::Alloc
		,"fxp_particleconstraint"
		,AutoBitmap("constraint.tif"),0);
}
