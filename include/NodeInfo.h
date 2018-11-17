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
		int MemoryTotal;
		int MemoryRemained;
		int CpuTotal;
		int CpuRemained;
		 NodeInfo(string ipAddress) 
        {
			IpAddress = ipAddress;
			MemoryTotal = 100;
			MemoryRemained = 100;
			CpuTotal = 100;
			CpuRemained=100;
        }
		NodeInfo(){};
		
		//pid_t Pid;
};

#endif
