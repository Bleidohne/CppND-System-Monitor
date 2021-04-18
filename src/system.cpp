#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;
using std::sort;

using namespace LinuxParser;

// [ML DONE]: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// Based on https://www.cplusplus.com/reference/algorithm/sort/
bool System::compare(Process& process1, Process& process2) {return (process1 < process2);}

// TODO: Return a container composed of the system's processes
// Based on Feedback: https://knowledge.udacity.com/questions/278992
vector<Process>& System::Processes() {  
    
    processes_.clear();                                          // Clear the list as this is periodically done due to cann in display function.
    
    vector<int> pids = LinuxParser::Pids();

    for(int pid:pids){
       Process process(pid);
       processes_.push_back(process);
    }

    sort(processes_.begin(), processes_.end(), compare);         // Sorting the processes downward CPU load. 


    return processes_; 
}

// [ML DONE]: Return the system's kernel identifier (string)
std::string System::Kernel() { return LinuxParser::Kernel(); }

// [ML DONE]: Return the system's memory utilization
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

// [ML DONE]: Return the operating system name
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// [ML DONE]: Return the total number of processes on the system
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// [ML DONE]: Return the number of seconds since the system started running
long System::UpTime() { return LinuxParser::UpTime(); }

