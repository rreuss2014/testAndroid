/*@Authors: Alphanso Walker & Anthony Spark Piris*/
/*@Description:File: ProcessTable.h Holds the definitions for the ProcessControlBlock and ProcessTable objects and
  the running state of the process.
*/
#ifndef PROCESSTABLE_H_
#define PROCESSTABLE_H_

#include <vector>

/*@description ProcessState--an enumerated type used for the running state of the processes in the algorithm.
   It can have the states of READY, RUNNING, NOT_LOADED, and COMPLETED*/
enum ProcessState { READY, RUNNING, NOT_LOADED, COMPLETED };

/*@class (struct) ProcessControlBlock*/
/*@description Contains all the elements for our process control block for simulating the algorithm.
   some of the members include the id, the submitted time of the process, the lenght of the process as well
   as how long it waited, the turnaround time, etc.
*/
struct ProcessControlBlock
{
	ProcessControlBlock(int procID = 0, int iArrv = 0, int iTotlRun = 0, int iWait = 0, ProcessState st = NOT_LOADED, 
		int et = 0, int currRunTime = 0, int iTurnAround = 0, int actStart = 0)
		: iProcessID(procID), iTimeSubmitted(iArrv), iTotalRunTime(iTotlRun), iWaitTime(iWait), state(st), iEndTime(et), 
		iCurrentRunningTime(currRunTime), iTurnAroundTime(iTurnAround), iActualStartTime(actStart), iQuantum(0),
		iTrueTotalRunTime(iTotlRun)
	{
	}

	int iProcessID;
	int iTimeSubmitted;
	int iTotalRunTime;
	int iActualStartTime;
	int iWaitTime;
	int iQuantum;
	int iEndTime;
	ProcessState state;
	int iCurrentRunningTime;
	int iTurnAroundTime;
	int iTrueTotalRunTime;
};

/*@class (struct) ProcessTable*/
/*@description a wrapper that just holds a vector of ProcessControlBlocks*/
struct ProcessTable
{
	std::vector<ProcessControlBlock> vectProcesses;
};


#endif


