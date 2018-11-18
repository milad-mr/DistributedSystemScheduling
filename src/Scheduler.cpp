#include "Scheduler.h"

float Scheduler::virtualization_overhead(){
	return 0;
	
	
}

float Scheduler::fi_vm_j(FunctionInfo j){
	
	
	
}

float Scheduler::fi_pcy_pc(FunctionInfo j){
	// The effective idling time of job j resulting in the resource idling
	// of physical core pcy, when j is assigned to the virtual core vc
	// that is mapped to physical core pc
	
	return fi_vm_j(j);
	
	
}

float Scheduler::p_pcy_pc(FunctionInfo j, NodeInfo node){
	// The effective load imposed on pc due to the 
	// assignment of job j to virtual core vc that
	// is mapped to the physical core pc
	return (j.CpuNeeded / node.CpuRemained) 
	+ virtualization_overhead() + sigma_pcy_pc(j) - fi_pcy_pc(j);
	
}

float Scheduler::sigma_pcy_pc(FunctionInfo j){
	
	
	
}

float Scheduler::a(){
	// a  = 1+γ/2
	return 1.5;
	
}

float Scheduler::g_pc(FunctionInfo j, NodeInfo node){
	
	
	
}

float Scheduler::h_pc(FunctionInfo j, NodeInfo node){
	
	
	
}

float Scheduler::before_assignment_cost(FunctionInfo j, NodeInfo node){
	
	
	
}

float Scheduler::after_assignment_cost(FunctionInfo j, NodeInfo node){
	
	
	
}



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

