#ifndef GLOBAL_SIMULATIONINFO_H
#define GLOBAL_SIMULATIONINFO_H

namespace NAVIE_GLOBAL
{
	namespace NAVIE_EFFEX
	{
		struct SubstepInfo
		{
			SubstepInfo() : delta(0.033), stepfrac(1.0), substep(1), substeps(1),min_substeps(0), laststep(true) {}

			double delta;			//The delta time to the previous substep
			double stepfrac;		//The fractional time step: (e.g. 1.0-(step/maxsteps))
			unsigned char substep;	//current substep
			unsigned char substeps; //How many substeps: 1 = no substeps
			unsigned char min_substeps;
			bool laststep;
		};

		struct SimulationInfo
		{
			SimulationInfo() : cframe(0), csecond(0.033), simtime(0.0), time(0.033), stepsimtime(0.0),fps(30) {}
			
			int cframe;		//The current frame
			double csecond;		//The current second
			double simtime;		//The simulation time
			double time;		//The current time step
			double stepsimtime; //The current step simulation time
			int fps;			//The current frames per second
			SubstepInfo sub;
		};
	}
}
#endif