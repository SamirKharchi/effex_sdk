#ifndef GLOBAL_NODES_H
#define GLOBAL_NODES_H

namespace NAVIE_GLOBAL
{
	namespace NAVIE_EFFEX
	{
		enum NodeBaseType
		{
			nbt_base,
			nbt_channel,
			nbt_body,
			nbt_source,
			nbt_operator,
			nbt_dynamics,
			nbt_particles,
			nbt_forces,
			nbt_cachers,

			nbt_objects_end,

			nbt_datacontainer,
			nbt_delegate,

			nbt_count,

			nbt_unknown = 200
		};

		enum NodeSubType
		{
			nst_none,
			nst_scalar,
			nst_vector,
			nst_state,
			nst_integer,
			nst_force,
			nst_grid,
			nst_particle,
			nst_constraint,
			nst_instant,
			nst_property,
			nst_vdb,
			nst_mesh,
			nst_obstacle,
			nst_volume,
			nst_custom,

			nst_count,

			nst_unknown = 31
		};
	}
}
#endif