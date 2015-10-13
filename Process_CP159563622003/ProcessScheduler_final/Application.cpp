
/*@Project OS Project #1
 Section A CS 3224
 Submission Date: 2/19/03
*/
/*@author Alphanso O. Walker & Anthony Spark Piris
*/
/*@description Application.cpp  The main file that contains, well, main (duh).  Main accepts commandline arguments
  based on how many arguments passed and the name of he algorithm, creates the correct Algorithm class for the
  simulation.

  Design:
  The goal was to make this fully object oriented and in order to use the full capabilities of C++.
  The naming convention was based on hungarian notation: classes began with uppercase and, variables
  were prefixed with the first few letters of their type.  Even though this violates encapsulation,
  this aided in debugging a lot.

  Polymorphism was the foundation on which the algorithms were conceived.  Through this mean, we were
  able to define one interface under which all algorithms ran.  This enabled us to work on seperate modules (objects)
  that were independant of the interface.  This also aided in debugging the program as it was easy to identify exactly 
  what part of the program was wrong.

  The STL played a strong part in our design.  Rather than having to worry about writing algorithms and keeping track
  of memory allocated for containers, the STL provided these things for us.

  In closing we would like to say this was a challenging, yet enjoyable project which not only got us back into our
  coding "groove", we garnered much experience and insight on how process scheduling is implemented in operating
  systems.

  Now, break out the champagne 'cause we're finally done.'
*/
#include "ProcessScheduler.h"
#include "GanntChart.h"

/*@method PrintUsage
*/
/*@description Describes how to use the program when there aren't enough arguments passed from the commandline
*/
void PrintUsage();

void main(int argc, char **argv)
{
	if (argc >= 4)
	{
		ProcessScheduler *processScheduler;
		std::cout << "Running algorithm: " << argv[2] << "\nWith a CSP of: " << argv[3] << "\nFilename: " 
			      << argv[1] << std::endl << std::endl;

		if (argc == 4)
		{
			processScheduler = new ProcessScheduler(argv[2], atoi(argv[3]));
		}
		else
		{
			processScheduler = new ProcessScheduler(argv[2], atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
		}
		processScheduler -> LoadFile(argv[1]);

		processScheduler -> RunProcesses();
		GanntChart ganntChart(*processScheduler);
		ganntChart.DisplayChart();
		ganntChart.DisplayTable();
		ganntChart.DisplaySummary();
		system("pause");
		
		delete processScheduler;
	}
	else
		PrintUsage();
}

void PrintUsage()
{
	std::cout << "ProcessScheduler Usage \nthe parameters shoud be in the following order:\n1) data file"
		         "containing list of processes with their arrival and running times\n"
				 "2) algorithm to run, specified as FCFS, SJF, SRTF, or RR \n"
				 "3) The context switch penalty. \n"
				 "4) For round robin, the time quantum. \n"
				 "5) For round robin, the degree of multiprogramming. \n"
				 "example: ProcessScheduler processes.txt RR 2 4 3\n";
};
