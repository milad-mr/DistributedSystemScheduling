//#include "Client.h"
//g++ Server.cpp ../Communication/Sender.cpp ../Models/ExecuterUnit.pb.cc -lzmq -lprotobuf -o Server

#include <iostream>
//#include "../Communication/Sender.h"
#include "Scheduler.h"
#include "Sender.h"
#include "Message.h"
#include <unistd.h>

using namespace std;

void notifyScheduleChanged(){

}

int main()
{
	
	Sender sender;
	int pid, functionCount;
	pid = 1;
	functionCount = 4;
	Scheduler scheduler(functionCount, 200, 200);
	cout << "after create scheduler";
	NodeInfo sampleNode = NodeInfo("127.1.1.1");
	NodeInfo sampleNode2 = NodeInfo("127.1.1.2");
	cout << "before  add node";
	scheduler.addNode(sampleNode);
	scheduler.addNode(sampleNode2);
	cout << "before schedule";
	while(scheduler.hasNext()){
		ScheduleResult scheduled = scheduler.getNext();
		Command command;
		command.Type = "run";
		command.PID = pid;
		command.StartIndex = scheduled.startIndex;
		command.EndIndex = scheduled.endIndex;
		cout << "indexes are" << scheduled.startIndex << scheduled.endIndex;
		cout << "before send";
		sender.Send(scheduled.node.IpAddress, command);

		sleep(2);


	}
		Command command;
		command.StartIndex = 0;
		command.StartIndex = 2;
		command.Type = "migrate";
		command.PID = 0;
		command.DestIP = "127.1.1.2";
		sender.Send("127.1.1.1", command);
		

	return 0;
	//Sender::SendCommand("127.0.0.1", "5001", "migrate");
}
