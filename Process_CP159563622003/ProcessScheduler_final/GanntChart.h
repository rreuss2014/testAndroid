
/*@author Alphanso Walker & Anthony Spark Piris
*/
/*@description GanntChart.h contains the class and functions needed to implement the display of the
  Gannt Chart.
*/
#ifndef GANNTCHART_H_
#define GANNTCHART_H_
#include "ProcessScheduler.h"
#include "Utility.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
typedef std::vector<ProcessControlBlock>::iterator itrPTable;

/*@class GanntChart
*/
/*@description This class encapsulates all the printing and other logistics regarding displaying the
  Gannt Chart.  It computes all the necessary data needed from the ProcessScheduler's Processtable
  and AlgorithmParameters members.  The purpose of the start and end iterators is to handle
  algorithms such as the Shortest Time Remaining First and Round Robin algorithms where processes appear
  in the chart more than once (due to switching).
*/
class GanntChart
{
	public:
		/*@method GanntChart::GanntChart */
		/*@description Constructor that takes in a ProcessScheduler class to obtain the the processtable
		   info and the algorithm's parameters given at runtime */
		GanntChart( ProcessScheduler &processScheduler );

		/*@method GanntChart::DisplayChart */
		/*@description Displays the chart (the times when the processes start, end/switch and the csp's) */
		void DisplayChart();
		/*@method GanntChart::DisplayTable */
		/*@description Displays the table containing the wait time and turnaround time information */
		void DisplayTable();
		/*@method GanntChart::DisplaySummary */
		/*@description Displays the runtime summary (Total run time of the simulation in terms of ticks
		   and the time spent in overhead/switching processes)
		*/
		void DisplaySummary();
	private:
		ProcessTable *processTable;
		SchedulingAlgorithmParameters *algorithmParams;
		itrPTable itrBegin;
		itrPTable itrEnd;
		int iTotalTime;
};

/*@method Calculate() */
/*@description A free function whose purpose is to calculate the wait time and turnaround time.
   This is really used for the pre-emptive algorithms since, in our implementation, processes appear
   twice because they were ran then switched.
*/
std::vector< ProcessControlBlock > Calculate(std::vector< ProcessControlBlock > readyProcesses)
{
	std::vector< ProcessControlBlock > tempVect;

	int i = 0;
	for ( itrPTable itr = readyProcesses.begin(); itr != readyProcesses.end(); ++itr )
	{
		if (itr->iProcessID == 0)
			continue;

		tempVect.push_back(*itr);
		itr->iProcessID = 0;
		for ( itrPTable itr2 = readyProcesses.begin(); itr2 != readyProcesses.end(); ++itr2)
		{
			if (itr2->iProcessID == tempVect[i].iProcessID)
			{
				if (tempVect[i].iWaitTime < itr2->iWaitTime)
				{
					tempVect[i].iWaitTime = itr2->iWaitTime;
				    tempVect[i].iTurnAroundTime = (itr2 -> iWaitTime + itr2 -> iTrueTotalRunTime);//+(itr2->iEndTime - itr2->iActualStartTime - 2);
				}
				itr2->iProcessID = 0;
			}
		}
		++i;

	}
	return tempVect;
}


GanntChart::GanntChart( ProcessScheduler &processScheduler ) : processTable(NULL)
{
	processTable = processScheduler.GetProcessTable();
	algorithmParams = processScheduler.GetSchedulingAlgorithmParameters();
	if( algorithmParams->swappedProcesses.size() > 0 )
	{		
		itrBegin = algorithmParams->swappedProcesses.begin();
		itrEnd   = algorithmParams->swappedProcesses.end();
		std::vector<ProcessControlBlock> temp;
		int count = 0;
		while(itrBegin != itrEnd)
		{
			for(itrPTable a = processTable->vectProcesses.begin(); a != processTable->vectProcesses.end(); a++)
			{	if(itrBegin->iProcessID == a->iProcessID)
				{
					temp.push_back(*itrBegin);count++;
				}
			}
			itrBegin++;
		}
		processTable->vectProcesses.insert(processTable->vectProcesses.begin() ,temp.begin(),temp.end());		
	}
	std::sort((processTable->vectProcesses).begin(), (processTable->vectProcesses).end(), 
		SortProcessEntryForDisplay());
}

void GanntChart::DisplayChart()
{
	
	int count = 0, x = 0;
	int tableSize = processTable->vectProcesses.size();
	std::cout <<"Gannt Chart:\n"
		 <<"-------------------------------------------------------------------\n";
	while (count < tableSize)
	{
		for( x = 0; x < 4 && (count != tableSize) ; x++, count++ )
			std::cout << processTable->vectProcesses[count].iProcessID 
			<< ((count+1 != tableSize) ? "\tCSP" : "\tDone") << '\t';
		std::cout << std::endl ;
		count -= x;
		for( int z = 0; z < 4 && (count != tableSize); count++, z++ )
		std::cout << processTable->vectProcesses[count].iActualStartTime
		<< '\t' << (processTable->vectProcesses[count].iEndTime) << '\t';		
		std::cout << std::endl << std::endl;
	}	
}


void GanntChart::DisplayTable()
{
	int vectSize = processTable->vectProcesses.size();
	iTotalTime = processTable->vectProcesses[((vectSize>0) ? (vectSize - 1) : 0)].iEndTime;
	if( algorithmParams->swappedProcesses.size() > 0 )
	{
		processTable->vectProcesses = Calculate(processTable->vectProcesses);
	}
	int count = 0;
	double totalTurnAroundTime = 0.0, totalWaitTime = 0.0;
	std::sort((processTable->vectProcesses).begin(), (processTable->vectProcesses).end(), 
		SortProcessEntryByIDForDisplay());
	
	int tableSize = processTable->vectProcesses.size();
	std::cout <<"Process Table:\n"
		 <<"-------------------------------------------------------------------\n"
         <<"Process id\t"<<"Wait time\t"<<"Turn around time\n" << std::endl;

	while ( count < tableSize)
	{		
		std::cout << processTable->vectProcesses[count].iProcessID <<"\t\t"
			<< processTable->vectProcesses[count].iWaitTime <<"\t\t"
			<< processTable->vectProcesses[count].iTurnAroundTime   << std::endl; 
		totalTurnAroundTime += processTable->vectProcesses[count].iTurnAroundTime;
		totalWaitTime += processTable->vectProcesses[count].iWaitTime;
		count++;
	}
	std::cout.setf(std::ios::fixed | std::ios::showpoint);
	std::cout.precision(1);
	std::cout << "Average\t\t" << (totalWaitTime/tableSize) << "\t\t" << (totalTurnAroundTime/tableSize) << std::endl << std::endl;
}


void GanntChart::DisplaySummary()
{
	int vectSize = processTable->vectProcesses.size();
	std::cout <<"Summary:\n"
		 <<"-------------------------------------------------------------------\n"
         <<"Total time needed for execution:\t"<< 
			iTotalTime << std::endl
		 <<"Time spent in overhead:\t\t\t" << algorithmParams->iOverHead << std::endl << std::endl;
}


#endif 