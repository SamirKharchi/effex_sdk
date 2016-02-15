#ifndef DUALFORCE_H
#define DUALFORCE_H

#include "api_effex.h"

/* Example shows how to create a custom Effex Dual force
Dual because it can be used for particles and grids 
- How to apply the constraint value
- How to define this force as dual, grid or particle force 
- How to read and use particle and grid specific process data 
- How to work with the vector3d class */
class DualForce : public FXAPI::FXForceData
{
private:
	typedef FXAPI::FXForceData Base;

	Float_C4D intensity;
	NAVIE_GLOBAL::vector3d cam_pos;
public:
	virtual Bool Init(GeListNode *node);

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

	static NodeData *Alloc(void) { return NewObj(DualForce); }
};

#endif