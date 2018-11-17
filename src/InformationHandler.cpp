#include "InformationHandler.h"


vector<string> explode(const string& s, const char& c)
{
	string buff{""};
	vector<string> v;
	
	for(auto n:s)
	{
		if(n != c) buff+=n; else
		if(n == c && buff != "") { v.push_back(buff); buff = ""; }
	}
	if(buff != "") v.push_back(buff);
	
	return v;
}

string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
            result += buffer.data();
    }
    return result;
}


NodeInfo InformationHandler::getNodeState(NodeInfo oldInfo){
	
	NodeInfo result;
	
		string str = exec("mosctl rstatus" + oldInfo.IpAddress);
 
	vector<string> v{explode(str, ' ')};
	result.IpAddress = oldInfo.IpAddress;
	result.MemoryTotal = atoi(v[7]);
	result.MemoryRemained = atoi(v[6]);
	int load = atoi(v[1]);
	
	return result;
	
}
