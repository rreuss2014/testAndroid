/*@author Alphanso O. Walker & Anthony Spark Piris
*/
/*@description Utility.h  File containing the definitions of our handy-dandy functors used to simulate the
  algorithms.
*/
#ifndef UTILITY_H_
#define UTILITY_H_




/*@class SortProcessEntryByTotalRunTime*/
/*@description Functor used to help sort control blocks by total run time. Used by the shortest job
  first algorithm.*/
class SortProcessEntryByTotalRunTime
{
	public:
		bool operator() (const ProcessControlBlock &lhs, const ProcessControlBlock &rhs)
		{
			return (lhs.iTotalRunTime < rhs.iTotalRunTime && (lhs.state != RUNNING && rhs.state != RUNNING));
		}
};

/*@class SortProcessEntryByID*/
/*@description Functor used to help sort control blocks by ID. Used by the first come
  first serve algorithm*/
class SortProcessEntryByID
{
	public:
		bool operator() (const ProcessControlBlock &lhs, const ProcessControlBlock &rhs)
		{
			return (lhs.iTimeSubmitted == rhs.iTimeSubmitted && lhs.state == READY && 
				    rhs.state == READY && lhs.iProcessID < rhs.iProcessID);
		}
};

/*@class SortProcessEntryByTotalRunTimeRemaining*/
/*@description Functor used to help sort control blocks by total runtime remaining. Used by the shortest remaining
  time first algorithm*/
class SortProcessEntryByTotalRunTimeRemaining
{
	public:
		bool operator() (const ProcessControlBlock &lhs, const ProcessControlBlock &rhs)
		{
			return ((lhs.iTotalRunTime - lhs.iCurrentRunningTime) < 
				(rhs.iTotalRunTime - lhs.iCurrentRunningTime) &&
				    (rhs.state == READY && lhs.state == READY));
		}
};

/*@class SortProcessEntryForDisplay*/
/*@description Functor used to help sort control blocks for display by the gannt chart.*/ 
class SortProcessEntryForDisplay
{
	public:
		bool operator() (const ProcessControlBlock &lhs, const ProcessControlBlock &rhs)
		{
			return (lhs.iActualStartTime < rhs.iActualStartTime);
		}
};

/*@class SortProcessEntryByIDForDisplay*/
/*@description Functor used to help sort control blocks for display by the gannt chart as well.*/ 
class SortProcessEntryByIDForDisplay
{
	public:
		bool operator() (const ProcessControlBlock &lhs, const ProcessControlBlock &rhs)
		{
			return (lhs.iProcessID < rhs.iProcessID);
		}
};


#endif