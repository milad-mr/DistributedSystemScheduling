#include "NodeInfo.h"
#include "FunctionInfo.h"
#include <iostream>
#include <string>
#include <vector>
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

public:
    Scheduler(int functionCount, int memoryNeeded, int cpuNeeded);
    Scheduler(int functionCount, int memoryNeeded, int cpuNeeded, int priority);
    void reSchedule();
    ScheduleResult getNext();
    bool hasNext();
    void updateProcessState();
    void addNode(string IpAddress);
    void addNode(NodeInfo newNode);
		//~ static void SendExecutable(std::string ip, std::string port, std::string path);
		//~ static void SendCommand(std::string ip, std::string port, std::string cmd);
};

#endif
