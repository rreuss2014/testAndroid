/*@author Alphanso Walker & Anthony Spark Piris*/
/*@description ProcessAlgorithms.h file; contains the classes used for implementing the algorithms*/

#ifndef PROCESSALGORITHMS_H_
#define PROCESSALGORITHMS_H_
#include <vector>
#include <deque>
#include "ProcessTable.h"
typedef std::vector<ProcessControlBlock>::iterator itrReadyProcesses;
typedef std::deque<ProcessControlBlock>::iterator itrRunnableProcesses;

/*@class DegreeOfMultiprogramming*/
/*@description Handles the runnable queue used in implementing the Round Robin Algorithm.  
  If there's enough memory available (i.e., the degree has not been reached), processes are
  inserted into the queue via the class' methods*/
class DegreeOfMultiprogramming
{
	public:
		/*@method DegreeOfMultiprogramming::DegreeOfMultiProgramming */
		/*@description Constructor which takes in the degree of multiprogramming as a parameter */
		DegreeOfMultiprogramming(int m)
			: degree(m)
		{

		}
		/*@method DegreeOfMultiprogramming::IsRunnable */
		/*@description This method determines whether there's enough space in the queue to store
		   another process.  It returns a boolean value.
		*/
		bool IsRunnable() 
		{ 
			return runnableProcesses.size() < degree; 
		}
		/*@method DegreeOfMultiprogramming::Insert */
		/*@description This method accepts a process as a parameter and inserts it into the queue.  
		   This is more or less a wrapper for the queue's push_back function
		*/
		void Insert( ProcessControlBlock &runbleProcesses )
		{
			runnableProcesses.push_back(runbleProcesses);
		}
		/*@method DegreeOfMultiprogramming::Rotate */
		/*@description This method rotates the members of the queue so that the next process in line 
		   is placed in the front and so forth.
		*/
		void Rotate() 
		{ 
			if( runnableProcesses.size() > 1)
			{
				Insert(*(runnableProcesses.begin()));
				runnableProcesses.pop_front();
			}
		}
		/*@method DegreeOfMultiprogramming::Remove */
		/*@description This method removes the process that's in front of the queue.  This is mainly used
		    to pop off the newly completed process and make room for another one.  It returns a copy
			of the removed process for later calculations.  If there's nothing inside, it'll return a
			default process control block (with everything initialized to zero).
		*/
		ProcessControlBlock Remove() 
		{ 
			ProcessControlBlock taskBlock;
			if( runnableProcesses.size() > 0)
			{
				taskBlock = *(runnableProcesses.begin());
				runnableProcesses.pop_front();
				return taskBlock;
			}
			return taskBlock;
		}
		/*@method DegreeOfMultiprogramming::Size */
		/*@description Rather self explanitory, this method returns the size of the queue (which
		    really means, how much stuff is currently in it) 
		*/
		int Size() { return runnableProcesses.size(); }
		/*@method DegreeOfMultiprogramming::GetRunnableProcesses*/
		/*@description A getter function to access the queue for processing outside the class */
		std::deque<ProcessControlBlock> & GetRunnableProcesses() { return runnableProcesses; }
	private:
		int degree;
		std::deque<ProcessControlBlock> runnableProcesses;
};

/*@class Struct SchedulingAlgorithmParameters*/
/*@description This struct contains the necessary parameters needed for the process scheduler and the
  algorithms being simulated such as the context switch penalty, current time (clock tick) and the
  degree of multiprogramming (previously defined as a class of it's own).*/
struct SchedulingAlgorithmParameters
{
	SchedulingAlgorithmParameters(int m) : degreeOfMultiprogramming(m) {}
	int iCurrentTime;
	int iCsp;
	int iQuantum;
	int iInContextSwitch;
	int iCountNewReadyProcesses;
	int iOverHead;
	std::vector<ProcessControlBlock> swappedProcesses;
	DegreeOfMultiprogramming degreeOfMultiprogramming;
	bool bRecentNewProcess;
};

/*@class SchedulingAlgorithm*/
/*@description This serves as the base class from which all the algorithms are derived.  Contains the
  basic functions that is common to all algorithms such as updating the process table on completion
  and if all processes in our table are completed.
*/
class SchedulingAlgorithm
/*
*/
{
    public:
		/*@method RunAlgorithm*/
		/*@description A pure vitual method in which all derived algorithm classes must define.  Makes sense
		  since each algorithm behaves in it's own special (annoying) way. This takes in a ProcessTable, SchedulingAlgorithmParameters and a vector
		  of control blocks.
		*/
		virtual void RunAlgorithm(ProcessTable &processTable, SchedulingAlgorithmParameters &params, std::vector<ProcessControlBlock> &readyProcesses) = 0;
		/*@method GetNewlyReadyProcesses*/
		/*@description A pure vitual method that all derived algorithms must define as well.  This is simply because
		  every algorithm has their own (sick) tastes in how they get the next ready process from the process table at the
		  time they were submitted.  This takes in a ProcessTable, SchedulingAlgorithmParameters and a vector
		  of control blocks.  Should return an integer value representing the number of ready processes that were
		  submitted at that tick. 
		*/
		virtual int GetNewlyReadyProcesses(ProcessTable &processTable, SchedulingAlgorithmParameters 
			&params, std::vector<ProcessControlBlock> &readyProcesses) = 0;

		/*@method ContextSwitch*/
		/*@description A virtual method that is optional for derived algorithms to override.  Some algorithms (the preemptive
		  picky little pains in the ...)  do things differently, hence this leeway is given for them.
		This takes in a ProcessTable, SchedulingAlgorithmParameters and a vector  of control blocks. */
		virtual
		void ContextSwitch(SchedulingAlgorithmParameters &params, std::vector<ProcessControlBlock> &readyProcesses)
		{
			if(params.iInContextSwitch)
			{
				--params.iInContextSwitch;
				for (itrReadyProcesses itr = readyProcesses.begin(); itr != readyProcesses.end(); itr++)
					itr -> iWaitTime ++;
			}
		}
		
	protected:	
		/*@method OnProcessComplete*/
		/*@description A method that sets the members of the completed process accordingly (such as total run time, end time,
		as well as the state).  This takes in an iterator vector of control blocks and a SchedulingAlgorithmParameters object.
		*/
		void OnProcessComplete(std::vector<ProcessControlBlock>::iterator itr, SchedulingAlgorithmParameters &params)
		{
			itr -> state = COMPLETED;			
			params.iInContextSwitch = params.iCsp;
			itr -> iEndTime = params.iCurrentTime+1;
			itr -> iActualStartTime = (itr -> iEndTime - itr -> iTotalRunTime);
			itr -> iTurnAroundTime = (itr -> iWaitTime + itr -> iTotalRunTime);
			//(itr) -> iTotalRunTime = (itr) -> iTotalRunTime - (itr) -> iCurrentRunningTime;
			params.iOverHead++;
		}
		/*@method ProcessCompleted*/
		/*@description Boolean method that takes and checks a ProcessTable to see if all the processes for the simulation have been completed.*/
		bool ProcessesCompleted(ProcessTable &processTable)
		{
			for (itrReadyProcesses itrTable = processTable.vectProcesses.begin(); itrTable != processTable.vectProcesses.end(); ++itrTable)
				if (itrTable -> state != COMPLETED)
					return false;

			return true;
		}	
		/*@method UpdateProcesses*/
		/*@description Takes in a ProcessTable and a vector of control blocks in order to update the information regarding the completed
		  processes in the vector and send it to the ProcessTable.
		*/
		void UpdateProcesses(ProcessTable &processTable, std::vector<ProcessControlBlock> &readyProcesses)
		{
			for (itrReadyProcesses itrTable = processTable.vectProcesses.begin(); itrTable != processTable.vectProcesses.end(); ++itrTable)
			{
				for (itrReadyProcesses itrList = readyProcesses.begin(); itrList != readyProcesses.end(); ++itrList)
				{
					if (itrTable -> iProcessID == itrList -> iProcessID)
					{
						*itrTable = *itrList;
						break;
					}
				}
			}
		}
};


//NON-PREEMPTIVE start
/*@class FirstComeFirstServe*/
/*@inherits SchedulingAlgorithm*/
/*@description the class that implements the first come first serve algorithm.  The methods are overidded accordingly*/
class FirstComeFirstServe : public SchedulingAlgorithm
/*
*/
{
	public:
		virtual void RunAlgorithm(ProcessTable &processTable, SchedulingAlgorithmParameters &params, std::vector<ProcessControlBlock> &readyProcesses);
		virtual int GetNewlyReadyProcesses(ProcessTable &processTable, SchedulingAlgorithmParameters 
			&params, std::vector<ProcessControlBlock> &readyProcesses);
};

/*@class ShortestJobFirst*/
/*@inherits SchedulingAlgorithm*/
/*@description the class that implements the shortest job first algorithm.  The methods are overidded accordingly*/
class ShortestJobFirst : public SchedulingAlgorithm
/*
*/
{
	public:
		virtual void RunAlgorithm(ProcessTable &processTable, SchedulingAlgorithmParameters &params, std::vector<ProcessControlBlock> &readyProcesses);
		virtual int GetNewlyReadyProcesses(ProcessTable &processTable, SchedulingAlgorithmParameters 
			&params, std::vector<ProcessControlBlock> &readyProcesses);
};
//NON-PREEMPTIVE end


//PREEMPTIVE start
/*@class ShortestTimeRemaingNext*/
/*@inherits SchedulingAlgorithm*/
/*@description the class that implements the Shortest Time Remaing Next algorithm.  The methods are overidded accordingly*/
class ShortestTimeRemaingNext : public SchedulingAlgorithm
/*
*/
{
	public:
		virtual void RunAlgorithm(ProcessTable &processTable, SchedulingAlgorithmParameters &params, std::vector<ProcessControlBlock> &readyProcesses);
		virtual int GetNewlyReadyProcesses(ProcessTable &processTable, SchedulingAlgorithmParameters 
			&params, std::vector<ProcessControlBlock> &readyProcesses);

};

/*@class RoundRobin*/
/*@inherits SchedulingAlgorithm*/
/*@description the class that implements the Round Robin algorithm.  The methods are overidded accordingly*/
class RoundRobin : public SchedulingAlgorithm
/*
*/
{
	public:
		virtual void RunAlgorithm(ProcessTable &processTable, SchedulingAlgorithmParameters &params, std::vector<ProcessControlBlock> &readyProcesses);
		virtual int GetNewlyReadyProcesses(ProcessTable &processTable, SchedulingAlgorithmParameters 
			&params, std::vector<ProcessControlBlock> &readyProcesses);
		virtual
		void ContextSwitch(SchedulingAlgorithmParameters &params, std::vector<ProcessControlBlock> &readyProcesses)
		{
			if(params.iInContextSwitch)
			{
				itrReadyProcesses itrPro = readyProcesses.begin();
				for (;itrPro != readyProcesses.end(); itrPro++)
					itrPro -> iWaitTime ++;

				--params.iInContextSwitch;
				for (itrRunnableProcesses itr = params.degreeOfMultiprogramming.GetRunnableProcesses().begin(); 
					itr != params.degreeOfMultiprogramming.GetRunnableProcesses().end(); itr++)
						if (itr -> state == READY)
						itr -> iWaitTime ++;
			}
		}
};
//PREEMPTIVE end

#endif