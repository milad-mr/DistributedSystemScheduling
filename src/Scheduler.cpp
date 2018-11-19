#include "Scheduler.h"

float Scheduler::virtualization_overhead(){
	return 0;
	
	
}

float Scheduler::fi_vm_j(FunctionInfo j){
	
	return 1;
	
	
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
	float x =  ((float)j.cpuNeeded / node.CpuRemained) 
	+ virtualization_overhead() + sigma_pcy_pc(j) - fi_pcy_pc(j);
	cout << "p_pcy_pc is : " << x<< endl;
	
}

float Scheduler::sigma_pcy_pc(FunctionInfo j){
	return 1; //like mosix processes
	
	
}

float Scheduler::a(){
	// a  = 1+γ/2
	return 1.5;
	
}

float Scheduler::g_pc(FunctionInfo j, NodeInfo node){
	
	
	return 0;
}

float Scheduler::h_pc(FunctionInfo j, NodeInfo node){
	
	return (float)node.Load / 100;
	
}

float Scheduler::before_assignment_cost(FunctionInfo j, NodeInfo node){
	
	return pow(a(), g_pc(j, node)) + pow(a(), h_pc(j, node)); 
	
}

float Scheduler::after_assignment_cost(FunctionInfo j, NodeInfo node){
	
	return pow(a(), g_pc(j, node) + fi_pcy_pc(j)) + pow(a(), h_pc(j, node) + p_pcy_pc(j, node)); 
	 
	
}

float Scheduler::alpha_pc(NodeInfo node){
	
	return 0;
	
}

float Scheduler::l_pc(NodeInfo node){
	
	return (float)node.Load / 100;
	
}

float Scheduler::marginal_cost(FunctionInfo j, NodeInfo node){
	
	cout << " after assign cost is :" << after_assignment_cost(j, node) <<endl;;
	cout << " before assign cost is :" << before_assignment_cost(j, node) <<endl;;
	return after_assignment_cost(j, node) - before_assignment_cost(j, node);
	
}


NodeInfo Scheduler::getBestNode(FunctionInfo j){
	float minCost = 99999;
	NodeInfo bestNode;
	// The chosen node will not delete from list
	for(auto const& node: nodes) {
		cout << " in nodeees for " << endl;
		float cost = marginal_cost(j, node);
		cout << " marginal cost is :" << cost <<endl;;
		if (cost < minCost){
			    cout << " node ip is :" << node.IpAddress << "Load is : " << node.Load << endl;
			minCost = cost;
			bestNode = node;
		}
	}
	//ScheduleResult result(bestNode, nextFunctionIndex, nextFunctionIndex + count);
                 
    cout << "best node ip is :" << bestNode.IpAddress << "Load is : " << bestNode.Load << endl;
	return bestNode;
	
	//return best node
}

bool Scheduler::is_stable(FunctionInfo j, NodeInfo node){
	return marginal_cost(j, node) <= 2 * (pow(a(), alpha_pc(node) + fi_pcy_pc(j)) + pow(a(), l_pc(node) +p_pcy_pc(j, node))
										- (pow(a(), alpha_pc(node) ) + pow(a(), l_pc(node)))); 
	
	
	
}

bool Scheduler::reSchedule(NodeInfo& oldNode, NodeInfo& newNode, FunctionInfo& job) {
	
	for(int i = 0; i < assignedJobs.size(); ++i) {
		if(!is_stable(assignedJobs[i].second, assignedJobs[i].first)){
			newNode = getBestNode(assignedJobs[i].second);
			oldNode = assignedJobs[i].first;
			assignedJobs.erase(assignedJobs.begin()  + i);
			return true;
		}
	}
	return false;
}


bool Scheduler::schedule(NodeInfo& node, FunctionInfo& job){
	
	if(unAssignedJobs.size() == 0 ) return false;
	job = unAssignedJobs.front();
	node = getBestNode(unAssignedJobs.front());
	unAssignedJobs.pop();
	assignedJobs.push_back(make_pair(node, job));
    return true;
}

Scheduler::Scheduler(){
	
	
}




void Scheduler::addNode(NodeInfo newNode){
    nodes.push_back(newNode);
}

void Scheduler::addJob(FunctionInfo newJob){
    unAssignedJobs.push(newJob);
}


 void Scheduler::updateNodeState(NodeInfo newState){
	 cout << "in update node state ips is " <<newState.IpAddress << endl; 
	 for(auto & node: nodes) {
		 if (node.IpAddress == newState.IpAddress){
			cout << "old State Load is :" << node.Load << endl;
			node = newState;
			
		 }
	 }
	 cout << "new State Load is :" << nodes[1].Load << endl;
	//zzz cout << "new State Load is :" << node.Load << endl;
 }
 
 
 //deprecated codes for old algorithm
 
 
 bool Scheduler::hasNext(){

    cout << "has next : " << nextFunctionIndex << functionCount<<endl;
    return nextFunctionIndex < functionCount - 1;


}


 Scheduler::Scheduler(int functionCount, int memoryNeeded, int cpuNeeded){
	 cout << "in update node state ips is ";// <<newState.IpAddress << endl; 
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




