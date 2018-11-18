//ExecuterUnit.h

#include <iostream>
#include <string>
#include <string.h>

#ifndef PROCESSINFO_H
#define PROCESSINFO_H

using namespace std;
struct NodeInfo
{
	public:
		string IpAddress;
		int MemoryTotal; // not important for some form of scheduler
		int MemoryRemained; // not important for some form of scheduler
		int CpuTotal;
		int CpuRemained;
		int Load;
		//int 
		NodeInfo(string ipAddress) 
        {
			IpAddress = ipAddress;
			MemoryTotal = 100;
			MemoryRemained = 100;
			CpuTotal = 100;
			CpuRemained = 100;
			Load = 0;
        }
		NodeInfo(){};
		
		//pid_t Pid;
};

#endif
