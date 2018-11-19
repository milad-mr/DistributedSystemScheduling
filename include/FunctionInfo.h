


//ExecutionUnit.h
#include <iostream>
#include <string.h>
#include "NodeInfo.h"

#ifndef FUNCTIONINFO_H
#define FUNCTIONINFO_H

using namespace std;

struct FunctionInfo
{
	public:
		int memoryNeeded; // not used for some schedulers
		int cpuNeeded = 1; //weight of CPU required
		int functionsCount;
		int pid;
		FunctionInfo(int pid, int functionsCount){
			this -> pid = pid;
			this -> functionsCount = functionsCount;
			
		}
		FunctionInfo(){};
	};

struct ScheduleResult
{
	public:
	ScheduleResult(NodeInfo n, int start, int end){
		node = n;
		startIndex = start;
		endIndex = end;
	}
	ScheduleResult(){};
		NodeInfo node;
		int startIndex;
		int endIndex;
};

#endif
