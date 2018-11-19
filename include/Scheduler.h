#include "NodeInfo.h"
#include "FunctionInfo.h"
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

#ifndef SCHEDULER_H
#define SCHEDULER_H
class Scheduler
{
    vector<NodeInfo> nodes;
    queue<FunctionInfo> unAssignedJobs;
    vector<pair <NodeInfo, FunctionInfo>> assignedJobs;
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
	float marginal_cost(FunctionInfo j, NodeInfo node);
	float alpha_pc(NodeInfo node);
	float l_pc(NodeInfo node);
	bool is_stable(FunctionInfo j, NodeInfo node);
	NodeInfo getBestNode(FunctionInfo j); // new algorithm
public:
	Scheduler();
    Scheduler(int functionCount, int memoryNeeded, int cpuNeeded);
    Scheduler(int functionCount, int memoryNeeded, int cpuNeeded, int priority);
    bool reSchedule(NodeInfo& oldNode, NodeInfo& newNode, FunctionInfo& job);
    bool schedule(NodeInfo& node, FunctionInfo& job); // new algorithm
    ScheduleResult getNext(); // old algorithm
    bool hasNext();
    void updateNodeState(NodeInfo newState);
    void addNode(string IpAddress);
    void addJob(FunctionInfo newJob);
    void addNode(NodeInfo newNode);
};

#endif
