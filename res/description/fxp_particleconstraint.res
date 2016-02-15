CONTAINER fxp_particleconstraint
{
	NAME fxp_particleconstraint;
	INCLUDE fx_constraint_plugin;

	GROUP ID_FORCE_BASE
	{
		//PLACE IN PARAMETER GROUP OF CONSTRAINT
		GROUP CONSTRAINT_PARAMS_SID 
		{
			REAL PARTICLECONSTRAINT_OFFSET { STEP 0.1; }
		}
	}
}
