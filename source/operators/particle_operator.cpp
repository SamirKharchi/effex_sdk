#include "particle_operator.h"
#include "c4d_symbols.h"
#include "fxp_particleoperator.h"

// initialize settings
Bool ParticleOperator::Init(GeListNode *node)
{
	BaseObject		*op		= (BaseObject*)node;
	BaseContainer *data = op->GetDataInstance();

	data->SetFloat	(POP_MAX,10.0);
	data->SetFloat	(POP_DRAG,0.2);
	data->SetVector	(POP_COLOR,Vector(1.0,0.6,0.2));
	
	ptr_particles = nullptr;
	m_min.SetFloat(0.2);
	m_max.SetFloat(10.0);
	m_color = NAVIE_GLOBAL::Color(1.0,0.6,0.2);

	return Base::Init(node);
}

Bool ParticleOperator::Message( GeListNode *node, Int32_C4D type, void *t_data )
{
	switch(type)
	{
	case MSG_DESCRIPTION_COMMAND:
		{
			DescriptionCommand *dc = (DescriptionCommand*)t_data;

			/* Handle Candidate buttons */
			FXAPI::FXServer *server = FXAPI::FXServer::Get(node->GetDocument());
			if(!server) break;

			if(dc->id[0].id==POP_PARTICLEGROUP_SELECTOR)
			{
				/* Create a list of particle groups that are already in the scene that the user may want to use */
				std::vector<FXAPI::FXBase*> items;
				FXAPI::GetNodes(server->GetEffexScene(get_wrapper()),NULL,items,FXAPI::NodeRetrieveType_ParticleGroup);

				/* Create a list of types that can be created */
				FXAPI::FXTypeInfos t_types;
				t_types.push_back(FXAPI::FXTypeInfo(EFFEX_PARTICLEGROUP,"Particle Group")); //The naming part is only for safe-guarding
				
				/* Pass all the info to the Candidate Popup */
				BaseObject *op = (BaseObject*)node;
				FXAPI::OpenCandidatePopup(false,items,t_types,op,POP_PARTICLEGROUP,false,true,0);
				return true;
			}
		}
		break;
	}
	return Base::Message(node,type,t_data);
}

/* Retrieve the interface settings */
bool ParticleOperator::FillData( BaseObject* node )
{
	GeData t_value;
	node->GetParameter(POP_DRAG,m_min,DESCFLAGS_GET_0);
	node->GetParameter(POP_MAX,m_max,DESCFLAGS_GET_0);
	node->GetParameter(POP_COLOR,t_value,DESCFLAGS_GET_0);

	m_color = FXAPI::VectorToVec3d<double>(t_value.GetVector());

	//We store the squared maximum
	m_max.SetFloat(m_max.GetFloat() * m_max.GetFloat());
	return true;
}

/* Retrieve interface port data */
bool ParticleOperator::FillPorts( BaseObject* node , FXAPI::FXServer* server)
{
	GeData t_value;
	node->GetParameter(POP_PARTICLEGROUP,t_value,DESCFLAGS_GET_0);

	BaseObject* particlegroup_obj = static_cast<BaseObject*>(t_value.GetLink(node->GetDocument()));
	if(!particlegroup_obj) return false;

	/* Ask the server for the particle group node that belongs to the BaseObject interface */
	ptr_particles = static_cast<FXAPI::FXParticleGroup*>(FXAPI::GetNode(server->GetEffexScene(node),particlegroup_obj,FXAPI::NodeRetrieveType_ParticleGroup));
	return ptr_particles != nullptr;
}

void ParticleOperator::GetSubType( int& subtype ) const
{
	subtype |= (1 << nst_particle); //We set the particle bit
}

bool ParticleOperator::PortsDirty( FXAPI::FXServer* server ) const
{
	/* Here you can check ports if they are dirty and return true if so */
	if(ptr_particles && ptr_particles->IsDirty(nullptr))
		return true;
	return false;
}

bool ParticleOperator::Precompute( FXAPI::FXServer* server )
{
	if(!ptr_particles) return false; //Don't run without particles

	return true; //All is fine
}

bool ParticleOperator::PrecomputeMP( FXAPI::FXServer* server )
{
	if(!ptr_particles) return false; //Don't run without particles

	FXAPI::FXScene* scene = server->GetEffexScene(ptr_particles->GetInterface());
	//Initialise the particle iterator with the particle group and the particle subgroup type (liquid particles hard coded). 
	//We also pass the cpu thread count retrieved from the Effex scene
	if(!iterator->Init(ptr_particles,ParticleFactoryTypes_Liquid,scene->GetCPUCount()))
		return false;
		
	return true; //All is fine
}

/* This is called by multiple processors */
void ParticleOperator::Process( void* t_data )
{
	//This is the thread data
	FXAPI::ProcessData* pdata = static_cast<FXAPI::ProcessData*>(t_data); if(!pdata) return;
	
	do //Now we browse with a do...while loop all particles of this cpu
	{
		//The iterator gives us the current particle
		FXAPI::FXParticle* particle = iterator->GetParticle(pdata->thread_index); if(!particle) continue;
		
		const NAVIE_GLOBAL::vector3d& velocity = particle->GetVelocity();

		//Here we simply calculate an intensity based on particle speed..
		double velocity_len_mapped	= FMax(velocity.getSquaredLength() / m_max.GetFloat(), 1.0);
		
		//..and set it as the particle 'color' property. 
		//Be aware that SetProperty_ will create the property if it's not yet attached to the particle. So it's always safe to call
		particle->SetProperty_Vector(m_color * velocity_len_mapped,PROPERTY_TYPE_COLOR);
		
		//And at the same time we add more drag to the particle's velocity the faster it becomes...noise modulated
		NAVIE_GLOBAL::vector3d final_drag = velocity * (m_min.GetFloat() * velocity_len_mapped) * Noise(FXAPI::Vec3DToVector(velocity));
		particle->SetVelocity(velocity - final_drag);

	} while(iterator->SetNext(pdata->thread_index)); //Go to next particle..

}

void ParticleOperator::FreePrecompute( void )
{
	/* Free precomputed data */
}

void ParticleOperator::ClearPorts( void )
{
	/* Clear any interface port data */
	ptr_particles = nullptr;
}

/************************************************************************/
// be sure to use a unique ID obtained from www.plugincafe.com
#define ID_PARTICLEOPERATOR 1001154

Bool RegisterParticleOperator(void)
{
	return RegisterFXOperatorPlugin
		(ID_PARTICLEOPERATOR
		,GeLoadString(IDS_PARTICLEOPERATOR)
		,OBJECT_GENERATOR
		,ParticleOperator::Alloc
		,"fxp_particleoperator"
		,AutoBitmap("operator.tif"),0);
}
