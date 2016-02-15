#ifndef PARTICLECONSTRAINT_H
#define PARTICLECONSTRAINT_H

#include "api_effex.h"

/* Example shows how to create a custom Effex Constraint */
class ParticleConstraint : public FXAPI::FXConstraintData
{
private:
	typedef FXAPI::FXConstraintData Base;
	Float_C4D offset;
public:
	virtual Bool Init(GeListNode *node);

	virtual bool FillData	(BaseObject* node);
	virtual bool FillPorts	(BaseObject* node , FXAPI::FXServer* server);
	virtual void ClearPorts	(void);

	virtual bool IsParticleConstraint	(void) const;				
	virtual void PrecomputeConstraint	(void* t_data);
	virtual void FreePrecomputeConstraint(void);

	virtual bool GetConstraint			(const NAVIE_GLOBAL::vector3d& position, double& src_value, void* local_data, int cpu = 0);
	virtual bool GetParticleConstraint	(const NAVIE_GLOBAL::vector3d& position, double& src_value, void* local_data, int cpu = 0, const void* t_particle = NULL);

	static NodeData *Alloc(void) { return NewObj(ParticleConstraint); }
};

#endif