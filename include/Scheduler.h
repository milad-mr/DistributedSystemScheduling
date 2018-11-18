#include "NodeInfo.h"
#include "FunctionInfo.h"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

#ifndef SCHEDULER_H
#define SCHEDULER_H
class Scheduler
{
    vector<NodeInfo> nodes;
   // vector<FunctionInfo> functions;
    //queue<pair <NodeInfo, FunctionInfo>> pa;
   // int getUniqueProcessId();
    int getUniqueFunctionId();
    int nextProcessId ;
    int nextFunctionIndex ;
    int functionCount;
    int memoryNeeded;
    int cpuNeeded;
    int priority;
    int maxResultFunctionCunt;

	float virtualization_overhead();
	float fi_vm_j(FunctionInfo j);
	float fi_pcy_pc(FunctionInfo j);
	float p_pcy_pc(FunctionInfo j, NodeInfo node);
	float sigma_pcy_pc(FunctionInfo j);
	
	float a();
	float g_pc(FunctionInfo j, NodeInfo node);
	float h_pc(FunctionInfo j, NodeInfo node);
	float before_assignment_cost(FunctionInfo j, NodeInfo node);
	float after_assignment_cost(FunctionInfo j, NodeInfo node);
	
public:
    Scheduler(int functionCount, int memoryNeeded, int cpuNeeded);
    Scheduler(int functionCount, int memoryNeeded, int cpuNeeded, int priority);
    void reSchedule();
    
    ScheduleResult getNext(); // old algorithm
    NodeInfo getBestNode(FunctionInfo j); // new algorithm
    ScheduleResult schedule(); // new algorithm
   // ScheduleResult schedule();
    bool hasNext();
    void updateNodeState(NodeInfo newState);
    void addNode(string IpAddress);
    void addNode(NodeInfo newNode);
		//~ static void SendExecutable(std::string ip, std::string port, std::string path);
		//~ static void SendCommand(std::string ip, std::string port, std::string cmd);
};

#endif
