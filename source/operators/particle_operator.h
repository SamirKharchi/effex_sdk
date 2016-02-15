#ifndef PARTICLEOPERATOR_H
#define PARTICLEOPERATOR_H

#include "api_effex.h"

/* Example shows how to create a custom particle operator
that is natively called by the Effex framework with multiple processors.

It includes:
- Retrieving and handling ports and settings
- How to define the operator as a Particle operator (instead of a grid operator)
- How to precompute particle ranges for multiprocessor support
- Browse all particles of a particle group range using a particle iterator
- Change particles and their properties arbitrarily
- Convert an Effex vector3d to a C4D Vector
- Creating a working candidate button
*/
class ParticleOperator : public FXAPI::FXOperatorData
{
private:
	typedef FXAPI::FXOperatorData Base;

	AutoAlloc<FXAPI::FXParticleIterator> iterator;
	FXAPI::FXParticleGroup* ptr_particles;
	GeData m_max,m_min;
	NAVIE_GLOBAL::Color m_color;

public:
	virtual Bool Init(GeListNode *node);
	virtual Bool Message( GeListNode *node, Int32_C4D type, void *t_data );

	virtual bool FillData	(BaseObject* node);
	virtual bool FillPorts	(BaseObject* node , FXAPI::FXServer* server);
	virtual void ClearPorts	(void);

	virtual void GetSubType				(int& subtype) const;
	virtual bool PortsDirty				(FXAPI::FXServer* server) const;

	/* Operator */
	virtual bool Precompute				(FXAPI::FXServer* server);
	virtual bool PrecomputeMP			(FXAPI::FXServer* server);
	virtual void Process				(void* t_data);
	virtual void FreePrecompute			(void);
	
	static NodeData *Alloc(void) { return NewObj(ParticleOperator); }
	
};

#endif