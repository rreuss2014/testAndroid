/*@author Alphanso Walker & Anthony Spark Piris*/
/*@description ProcessScheduler.h declares the ProcessScheduler class*/
#ifndef PROCESSSCHEDULER_H_
#define PROCESSSCHEDULER_H_
#include "ProcessTable.h"
#include "ProcessAlgorithms.h"
#include <string>
#include <vector>

/*@class ProcessScheduler*/
/*@description The meat 'n taters of the program.  It handles the initialization and creation of the 
  algorithm being simulated and also runs them.*/
class ProcessScheduler
{
	public:
		/*@method ProcessScheduler::ProcessScheduler*/
		/*@description Constructor; initializes the algorithm pointer (creates an instance based on the name)
		  and initilizes the parameters for the algorithm.
		*/
		ProcessScheduler(const std::string &strAlgorithmName, int csp, int quantum = 0, int m = 0);
		/*@method ProcessScheduler::~ProcessScheduler*/
		/*@description Destructor; deallocates the algorithm object that was created of the base class Scheduling Algorithm*/
		~ProcessScheduler();
		/*@method ProcessScheduler::LoadFile*/
		/*@description Loads the file containing the process data.  Done before the simulation actually starts 'cause we're such
		  cheaters.
		*/
		void LoadFile(const std::string &strFilename);
		/*@method ProcessScheduler::RunProcesses*/
		/*@description Calls the algorithm's run function and exits upon the simulation's completion*/
		void RunProcesses();		
		/*@method ProcessScheduler::GetProcessTable*/
		/*@description An accessor method for the private member processTable.*/
		ProcessTable *GetProcessTable() { return &processTable; }
		/*@method ProcessScheduler::GetSchedulingAlgorithmParameters*/
		/*@description An accessor method for the private member algorithmParams.*/
		SchedulingAlgorithmParameters * GetSchedulingAlgorithmParameters() { return &algorithmParams; }

	private:
		ProcessTable processTable;
		SchedulingAlgorithm *algorithm;
		SchedulingAlgorithmParameters algorithmParams;
		/*@method ProcessScheduler::SpawnAlgorithm*/
		/*@description SOMEBODY'S brainchild; This method is responsible for creating the correct
		  algorithm for the simulation based on the name (initials, really) that's passed in (case insensitive).  Returns
		  a pointer to the newly created algorithm.*/
		SchedulingAlgorithm *SpawnAlgorithm(const std::string &strAlgoName);
		std::vector<ProcessControlBlock> readyProcesses;		
};


#endif
