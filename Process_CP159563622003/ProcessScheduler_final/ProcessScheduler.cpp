#include "ProcessScheduler.h"
#include <fstream>
#include <iostream>
#include <cstring>

typedef std::vector<ProcessControlBlock>::iterator itrReadyProcesses;

ProcessScheduler::ProcessScheduler(const std::string &strAlgorithmName, int csp, int quantum, int degree)
:algorithmParams(degree)
{
	algorithmParams.iCsp = csp;
	algorithmParams.iOverHead = 0;
	algorithmParams.iQuantum = quantum;
	algorithmParams.iCurrentTime = 0;
	algorithmParams.iInContextSwitch = 0;
	algorithmParams.bRecentNewProcess = false;
	algorithm = SpawnAlgorithm(strAlgorithmName);
}

ProcessScheduler::~ProcessScheduler()
{
	delete algorithm;
}


SchedulingAlgorithm * ProcessScheduler::SpawnAlgorithm(const std::string &strAlgorithmName)
{
	_strlwr(const_cast<char *>(strAlgorithmName.c_str()));
	if( strAlgorithmName == "sjf" )
		return new ShortestJobFirst;
	else if( strAlgorithmName == "srtf" )
		return new ShortestTimeRemaingNext;
	else if( strAlgorithmName == "rr" )
		return new RoundRobin;

	return new FirstComeFirstServe;
}

void ProcessScheduler::LoadFile(const std::string &strFilename)
{
	std::ifstream in(strFilename.c_str()); 
	if(in.fail())
	{
		std::cerr <<"Failed to open file\n";
		exit(1);
	}

	ProcessControlBlock taskBlock;
	while( in >> taskBlock.iProcessID >> taskBlock.iTimeSubmitted >> taskBlock.iTotalRunTime )
	{
		taskBlock.iTrueTotalRunTime = taskBlock.iTotalRunTime;
		processTable.vectProcesses.push_back(taskBlock);
	}
}

void ProcessScheduler::RunProcesses()
{	
	algorithm->RunAlgorithm(processTable, algorithmParams, readyProcesses);	
	algorithmParams.iOverHead = (algorithmParams.iOverHead-1) * algorithmParams.iCsp;
}


