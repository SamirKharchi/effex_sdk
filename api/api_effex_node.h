// Copyright (c) All Rights Reserved, Navié
//
// This does not touch the license for the Cinema 4D specific code functions used
// Please see the Cinema 4D license correspondingly. All other rights reserved.
//
// Author: Samir Kharchi
#ifndef API_EFFEX_NODE_H
#define API_EFFEX_NODE_H

#include "c4d_objectdata.h"
#include "c4d_objectplugin.h"
#include "api_effex_scene.h"
#include "api_effex_base.h"

namespace NAVIE_GLOBAL
{
	namespace NAVIE_EFFEX
	{
		class iNodeBaseWrapper;

		namespace NAVIE_API
		{
			class FXNodeData : public ObjectData
			{
			private:
				std::vector<Int32_C4D> m_csmode_oldflag;

			protected:
				bool m_is_rendering;
				bool m_is_rendering_external;
				bool m_link_dropped;
				
				iNodeBaseWrapper* m_wrapper;

			public:
				FXNodeData();
				~FXNodeData();

				virtual Bool IsInstanceOf				(const GeListNode *node, Int32_C4D type) const;
				virtual BaseObject* GetVirtualObjects	(BaseObject *op, HierarchyHelp *hh);	
				virtual Bool Init						(GeListNode *node);
				virtual void Free						(GeListNode *node);
				virtual Bool Message					(GeListNode *node, Int32_C4D type, void *t_data);

				virtual Bool Read(GeListNode *node, HyperFile *hf, Int32_C4D level);
				virtual Bool Write(GeListNode *node, HyperFile *hf);
				virtual Bool CopyTo(NodeData *dest, GeListNode *snode, GeListNode *dnode, COPYFLAGS flags, AliasTrans *trn);

				virtual void GetSubType					(int& subtype) const;
				virtual bool PortsDirty					(FXServer* server) const;
				virtual DRAWRESULT DrawNode				(BaseObject* op, DRAWPASS drawpass, BaseDraw* bd, BaseDrawHelp* bh);

				/* Base */
				virtual bool FillData					(BaseObject* node);
				virtual bool FillPorts					(BaseObject* node , FXServer* server);
				virtual void ClearPorts					(void);
				
				iNodeBaseWrapper* get_wrapper			(void);
				const iNodeBaseWrapper* get_wrapper		(void) const;
			};

			struct FXNODEPLUGIN : public OBJECTPLUGIN
			{
				// generator
				void			(FXNodeData::*GetSubType)				(int& subtype) const;
				bool			(FXNodeData::*PortsDirty)				(FXServer* server) const;

				bool			(FXNodeData::*FillData)					(BaseObject* node);
				bool			(FXNodeData::*FillPorts)				(BaseObject* node , FXServer* server);
				void			(FXNodeData::*ClearPorts)				(void);
				DRAWRESULT		(FXNodeData::*DrawNode)					(BaseObject* op, DRAWPASS drawpass, BaseDraw* bd, BaseDrawHelp* bh);
								
				iNodeBaseWrapper*		(FXNodeData::*get_wrapper)		(void);

				void*	reserved[(32-7)*C4DPL_MEMBERMULTIPLIER-1];
			};

		}
	}
}

#endif //API_EFFEX_PARTICLE_H