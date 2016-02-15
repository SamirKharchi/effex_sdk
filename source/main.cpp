#include "api_effex.h"

Bool RegisterParticleConstraint(void);
Bool RegisterParticleOperator(void);
Bool RegisterDualForce(void);

Bool PluginStart(void)
{
	if(FXAPI::InitEffex()) //Must be called before registering
	{
		RegisterParticleConstraint();
		RegisterDualForce();
		RegisterParticleOperator();
	}	
	return true;
}

void PluginEnd(void)
{
}

Bool PluginMessage(Int32_C4D id, void *data)
{
	switch (id)
	{
		case C4DPL_INIT_SYS:
			if (!resource.Init()) return false; // don't start plugin without resource
			return true;
	}

	return false;
}
