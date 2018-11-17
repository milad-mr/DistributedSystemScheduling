


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
		int MemoryNeeded;
		int CpuNeeded;
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
