#include "ProcessAlgorithms.h"
#include "Utility.h"
#include <algorithm>
#include <iostream>
#include <functional>


void FirstComeFirstServe::RunAlgorithm(ProcessTable &processTable, SchedulingAlgorithmParameters &params, std::vector<ProcessControlBlock> &readyProcesses)
{
	// if there are more than two processes that have been submitted at the same
	// time, sort them by process ID
	do
	{
		params.iCountNewReadyProcesses = 
			GetNewlyReadyProcesses(processTable, params, readyProcesses);

		if (!params.iInContextSwitch)
		{
			
			if (params.iCountNewReadyProcesses > 1)
				std::sort(readyProcesses.begin(), readyProcesses.end(), SortProcessEntryByID()); 
			itrReadyProcesses itr = readyProcesses.begin();	
			itr -> state = RUNNING;
			for (++itr; itr != readyProcesses.end(); itr++)
				itr -> iWaitTime ++;	
			itr = readyProcesses.begin();		
			if ( ++(itr -> iCurrentRunningTime) == itr -> iTotalRunTime )
			{
				OnProcessComplete(itr,params);
				UpdateProcesses(processTable, readyProcesses);
				readyProcesses.erase(readyProcesses.begin());
			}
		}
		else
			ContextSwitch(params, readyProcesses);
		params.iCurrentTime++;
	} while ( !ProcessesCompleted(processTable) ); //while all the processes are not done
}

int FirstComeFirstServe::GetNewlyReadyProcesses(ProcessTable &processTable, SchedulingAlgorithmParameters &params, std::vector<ProcessControlBlock> &readyProcesses)
{
	int iCountNewReadyProcesses = 0;
	for (int i = 0; i < processTable.vectProcesses.size(); ++i)
	{
		if (params.iCurrentTime == processTable.vectProcesses[i].iTimeSubmitted)
		{
			processTable.vectProcesses[i].state = READY;
			readyProcesses.push_back(processTable.vectProcesses[i]);
			++iCountNewReadyProcesses;
		}
	}
	return iCountNewReadyProcesses;
}


//-------------------------------------------------------------------------------------------------------------------------

void ShortestJobFirst::RunAlgorithm(ProcessTable &processTable, SchedulingAlgorithmParameters &params, std::vector<ProcessControlBlock> &readyProcesses)
{
	// if there are more than two processes that have been submitted at the same
	// time, sort them by process ID
	do
	{
		params.iCountNewReadyProcesses = 
			GetNewlyReadyProcesses(processTable, params, readyProcesses);

		if (!params.iInContextSwitch)
		{
			
			if (readyProcesses.size() > 1)
				std::sort(readyProcesses.begin(), readyProcesses.end(), SortProcessEntryByTotalRunTime()); 
			itrReadyProcesses itr = readyProcesses.begin();	
			itr -> state = RUNNING;
			for (++itr; itr != readyProcesses.end(); itr++)
				itr -> iWaitTime ++;	
			itr = readyProcesses.begin();		
			if ( ++(itr -> iCurrentRunningTime) == itr -> iTotalRunTime )
			{
				OnProcessComplete(itr,params);
				UpdateProcesses(processTable, readyProcesses);
				readyProcesses.erase(readyProcesses.begin());
			}
		}
		else
			ContextSwitch(params, readyProcesses);
		params.iCurrentTime++;
	} while ( !ProcessesCompleted(processTable) ); //while all the processes are not done
}

int ShortestJobFirst::GetNewlyReadyProcesses(ProcessTable &processTable, SchedulingAlgorithmParameters &params, std::vector<ProcessControlBlock> &readyProcesses)
{
	int iCountNewReadyProcesses = 0;
	for (int i = 0; i < processTable.vectProcesses.size(); ++i)
	{
		if (params.iCurrentTime == processTable.vectProcesses[i].iTimeSubmitted)
		{
			processTable.vectProcesses[i].state = READY;
			readyProcesses.push_back(processTable.vectProcesses[i]);
			++iCountNewReadyProcesses;
		}
	}
	return iCountNewReadyProcesses; 
}

//*********************************************************************************************************
void ShortestTimeRemaingNext::RunAlgorithm(ProcessTable &processTable, SchedulingAlgorithmParameters &params, std::vector<ProcessControlBlock> &readyProcesses)
{	// if there are more than two processes that have been submitted at the same
	// time, sort them by their execution time
	do
	{
		params.iCountNewReadyProcesses = 
			GetNewlyReadyProcesses(processTable, params, readyProcesses);
		
		if (!params.iInContextSwitch)
		{
			
			itrReadyProcesses itr = readyProcesses.begin();	
			if(readyProcesses.size() > 1)
			{	
				itr->state = READY;	
				if ( readyProcesses[0].iTotalRunTime - readyProcesses[0].iCurrentRunningTime > 
					readyProcesses[1].iTotalRunTime - readyProcesses[1].iCurrentRunningTime)
				{			
					std::swap(*itr,*(itr+1));			
					if(readyProcesses[1].state != READY)
					{							
						(itr+1) -> iEndTime = params.iCurrentTime;
						(itr+1) -> iActualStartTime = (itr+1) -> iEndTime - (itr+1) -> iCurrentRunningTime;
						(itr+1) -> iTurnAroundTime = (itr+1) -> iWaitTime + (itr+1) -> iCurrentRunningTime;						
						(itr+1) ->iTotalRunTime = (itr+1) ->iTotalRunTime - (itr+1) ->iCurrentRunningTime;
						(itr+1) ->iCurrentRunningTime = 0;
						params.swappedProcesses.push_back(*(itr+1));
						params.iInContextSwitch = params.iCsp;
						params.iOverHead++;
						goto SWITCH;
					}			
				}		
			}	
			itr -> state = RUNNING;	
			for (++itr; itr != readyProcesses.end(); itr++)
				itr -> iWaitTime ++;
			itr = readyProcesses.begin();	
			if ( ++(itr -> iCurrentRunningTime) == itr -> iTotalRunTime )
			{
				OnProcessComplete(itr,params);
				UpdateProcesses(processTable, readyProcesses);
				readyProcesses.erase(readyProcesses.begin());
			}
		}
		else
		SWITCH:	ContextSwitch(params, readyProcesses);
		params.iCurrentTime++;
	} while ( !ProcessesCompleted(processTable) ); //while all the processes are not done
}


int ShortestTimeRemaingNext::GetNewlyReadyProcesses(ProcessTable &processTable, 
													SchedulingAlgorithmParameters &params, std::vector<ProcessControlBlock> &readyProcesses)
{
	int iCountNewReadyProcesses = 0;
	for (int i = 0; i < processTable.vectProcesses.size(); ++i)
	{
		if (params.iCurrentTime == processTable.vectProcesses[i].iTimeSubmitted)
		{
			params.bRecentNewProcess = true;
			processTable.vectProcesses[i].state = READY;
			readyProcesses.push_back(processTable.vectProcesses[i]);
			std::sort(readyProcesses.begin(), readyProcesses.end(), SortProcessEntryByTotalRunTimeRemaining());
			++iCountNewReadyProcesses;
		}
	}
	return iCountNewReadyProcesses; 
}

//*********************************************************************************************************
void RoundRobin::RunAlgorithm(ProcessTable &processTable, SchedulingAlgorithmParameters &params, std::vector<ProcessControlBlock> &readyProcesses)
{	// if there are more than two processes that have been submitted at the same
	// time, sort them by their execution time
	do
	{
		params.iCountNewReadyProcesses = 
			GetNewlyReadyProcesses(processTable, params, readyProcesses);		
		if (!params.iInContextSwitch)
		{
			itrReadyProcesses itr = readyProcesses.begin();	
			while(itr != readyProcesses.end() && params.degreeOfMultiprogramming.IsRunnable() )
			{
				params.degreeOfMultiprogramming.Insert(*itr);
				readyProcesses.erase(itr);
				itr = readyProcesses.begin();
			}			
			if(params.degreeOfMultiprogramming.Size() > 0) // if we have anything to run
			{	
				itrRunnableProcesses deqItr = params.degreeOfMultiprogramming.GetRunnableProcesses().begin();
				deqItr-> state = RUNNING;		
				
				itrReadyProcesses itr = readyProcesses.begin();
				for (;itr != readyProcesses.end(); itr++)
					itr -> iWaitTime ++;		
				++deqItr;
				for (; deqItr != params.degreeOfMultiprogramming.GetRunnableProcesses().end(); deqItr++)
					deqItr -> iWaitTime ++;
				deqItr = params.degreeOfMultiprogramming.GetRunnableProcesses().begin();
				//if the execution time for this process is over
				if(++(deqItr->iCurrentRunningTime) == deqItr->iTotalRunTime)
				{
					ProcessControlBlock taskBlock = params.degreeOfMultiprogramming.Remove();			
					readyProcesses.insert(readyProcesses.begin(),taskBlock);			
					OnProcessComplete(readyProcesses.begin(),params);
					UpdateProcesses(processTable, readyProcesses);
					readyProcesses.erase(readyProcesses.begin());
					goto TIME;
					//goto SWITCH;
					
				}
				//else check that quantum is not zero
				else if(--(deqItr->iQuantum) == 0)
				{
					deqItr -> state = READY;
					params.iOverHead++;
					deqItr -> iEndTime = params.iCurrentTime+1;
					deqItr -> iActualStartTime = deqItr -> iEndTime - deqItr -> iCurrentRunningTime;
					deqItr -> iTurnAroundTime = deqItr -> iWaitTime + deqItr -> iCurrentRunningTime;
					deqItr ->iTotalRunTime = deqItr ->iTotalRunTime - deqItr ->iCurrentRunningTime;
					deqItr ->iCurrentRunningTime = 0;
					params.swappedProcesses.push_back(*deqItr);
					
					deqItr->iQuantum = params.iQuantum; // reset quantum
					ProcessControlBlock temp = *(params.degreeOfMultiprogramming.GetRunnableProcesses().begin());
					params.degreeOfMultiprogramming.Rotate();
					ProcessControlBlock temp2 = *(params.degreeOfMultiprogramming.GetRunnableProcesses().begin());
					params.iInContextSwitch = params.iCsp;
					goto TIME;
				}
			}			
		}
		else
			ContextSwitch(params, readyProcesses);
			TIME:params.iCurrentTime++;
	} while ( !ProcessesCompleted(processTable) ); //while all the processes are not done
	
}


int RoundRobin::GetNewlyReadyProcesses(ProcessTable &processTable, 
										SchedulingAlgorithmParameters &params, std::vector<ProcessControlBlock> &readyProcesses)
{
	int iCountNewReadyProcesses = 0;
	for (int i = 0; i < processTable.vectProcesses.size(); ++i)
	{
		if (params.iCurrentTime == processTable.vectProcesses[i].iTimeSubmitted)
		{
			processTable.vectProcesses[i].iQuantum = params.iQuantum;
			processTable.vectProcesses[i].state = READY;
			readyProcesses.push_back(processTable.vectProcesses[i]);
			itrReadyProcesses itr = readyProcesses.begin();	
			if(params.degreeOfMultiprogramming.IsRunnable())
			{
				params.degreeOfMultiprogramming.Insert(*itr);
				readyProcesses.erase(itr);
			}
			++iCountNewReadyProcesses;
		}
	}
	return iCountNewReadyProcesses; 
}