#include "Scheduler.h"


Scheduler::Scheduler(int functionCount, int memoryNeeded, int cpuNeeded){
    nextProcessId = 1;
    nextFunctionIndex = 0;
    this -> memoryNeeded = memoryNeeded;
    this -> cpuNeeded = cpuNeeded;
    this->functionCount = functionCount;

}

Scheduler::Scheduler(int functionCount, int memoryNeeded, int cpuNeeded, int priority){
    nextProcessId = 1;
    nextFunctionIndex = 0;
    this->functionCount = functionCount;
    this->priority = priority;

}
bool Scheduler::hasNext(){

    cout << "has next : " << nextFunctionIndex << functionCount<<endl;
    return nextFunctionIndex < functionCount - 1;


}

ScheduleResult Scheduler::getNext(){
    ScheduleResult result;
    int estimatedFunctionMemoryNeeded = memoryNeeded / functionCount;
    int estimatedFunctionCpuNeeded = cpuNeeded / functionCount; // in percent
    cout <<"in getNext";
    for (int i = 0; i < nodes.size() && nextFunctionIndex < functionCount - 1; ++i ){
		cout <<"in foorr i is: "<< i;
         if (nodes.at(i).MemoryRemained > estimatedFunctionMemoryNeeded && nodes.at(i).CpuRemained > estimatedFunctionCpuNeeded ){
             int count;
             int remainedFunctions = functionCount - nextFunctionIndex;
             if(priority == 0){
               count = min(min(nodes.at(i).MemoryRemained / estimatedFunctionMemoryNeeded,
                          nodes.at(i).CpuRemained / estimatedFunctionMemoryNeeded), remainedFunctions);
             }else{
                count = min( min(nodes.at(i).MemoryRemained / estimatedFunctionMemoryNeeded,
                          nodes.at(i).CpuRemained / estimatedFunctionCpuNeeded),(remainedFunctions / (int)nodes.size()));
             }
             if(count > 0){
                 nodes.at(i).MemoryRemained -= count * estimatedFunctionMemoryNeeded;
                 nodes.at(i).CpuRemained -= count * estimatedFunctionCpuNeeded;

                 ScheduleResult result(nodes.at(i), nextFunctionIndex, nextFunctionIndex + count);
                 nextFunctionIndex += count;
                 return result;
             }
        }
    }
}


void Scheduler::addNode(NodeInfo newNode){
    nodes.push_back(newNode);
}

