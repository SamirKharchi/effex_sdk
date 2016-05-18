// Copyright (c) All Rights Reserved, Navié
//
// This does not touch the license for the Cinema 4D specific code functions used
// Please see the Cinema 4D license correspondingly. All other rights reserved.
//
// Author:	Samir Kharchi

#include "c4d.h"

/************************************************************************/
/* Requires at least Effex v2.70.77 */
/************************************************************************/

class VoxelGenerator : public ObjectData
{
public:
	virtual Bool Init		(GeListNode* node);
	//virtual void GetDimension		(BaseObject* op, Vector* mp, Vector* rad);
	virtual BaseObject* GetVirtualObjects(BaseObject* op, HierarchyHelp* hh);
	virtual Bool Message(GeListNode* node, Int32 type, void* t_data);

	static NodeData* Alloc(void) { return NewObjClear(VoxelGenerator); }
};