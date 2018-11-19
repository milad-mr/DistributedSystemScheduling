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
	string command = "mosctl rstatus " + oldInfo.IpAddress;
	cout << "command is " << command << endl;
		string str = exec( command.c_str() );
	vector<string> v{explode(str, ' ')};
	result.IpAddress = oldInfo.IpAddress;
	result.MemoryTotal = atoi(v.at(7).c_str());
	result.MemoryRemained = atoi(v.at(6).c_str());
	result.Load = atoi(v[1].c_str());
	return result;
	
}
