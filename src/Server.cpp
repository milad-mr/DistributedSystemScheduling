#include <iostream>
#include "Scheduler.h"
#include "Sender.h"
#include "Message.h"
#include "InformationHandler.h"
#include <unistd.h>

using namespace std;

void notifyScheduleChanged(){

}

void testNewAlgorithm(){
	Sender sender;
	int pid, functionCount;
	pid = 1;
	functionCount = 4;
	FunctionInfo newJob(pid, functionCount);
	Scheduler scheduler;
	InformationHandler infoHandler;
	cout << "after create scheduler";
	NodeInfo sampleNode = NodeInfo("192.168.68.139");
	//NodeInfo sampleNode2 = NodeInfo("192.168.68.140");
	cout << "before  add node";
	scheduler.addNode(sampleNode);
	scheduler.addJob(newJob);
	//scheduler.addJob(FunctionInfo(2,3));
	//scheduler.addJob(FunctionInfo(3,4));
	//scheduler.addNode(sampleNode2);
	

	scheduler.updateNodeState(infoHandler.getNodeState(sampleNode));
	//sleep(3);
	while(true){
		cout << "old info load is : " << sampleNode.CpuRemained << endl;
		scheduler.updateNodeState(infoHandler.getNodeState(sampleNode));
		
		
		NodeInfo oldNode, newNode;
		FunctionInfo funcInfo;
		while(scheduler.reSchedule(oldNode, newNode, funcInfo)) // if need rescheduling
		{
			Command command;
			command.Type = "migrate";
			command.PID = funcInfo.pid;
			command.StartIndex = 0;
			command.EndIndex = funcInfo.functionsCount;
			command.DestIP = newNode.IpAddress;
			sender.Send(oldNode.IpAddress, command);
			
		}
		while(scheduler.schedule(newNode, funcInfo)){
			
			Command command;
			command.Type = "run";
			command.PID = funcInfo.pid;
			command.StartIndex = 0;
			command.EndIndex = funcInfo.functionsCount;
			command.DestIP = newNode.IpAddress;
			sender.Send(newNode.IpAddress, command);
			
			
		}
		sleep(2);
	
	}
}

int main()
{
	testNewAlgorithm();
	return 0;
}
