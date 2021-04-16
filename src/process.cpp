#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include <process.h>
#include <linux_parser.h>

using namespace LinuxParser;

using std::string;
using std::to_string;
using std::vector;
using std::stoi;


// Constructor for Process Class
Process::Process(int pid){
   
   pid_ = pid;                      // Attach pid to the created process.

  // cpu_utilization_ = LinuxParser::CpuUtilization(pid);
   command_ = LinuxParser::Command(pid);
   Ram_ = LinuxParser::Ram(pid);
   User_ = LinuxParser::User(pid);
   UpTime_ = LinuxParser::UpTime(pid);
   
}


// [ML DONE]: Return this process's ID
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
    
    float pid_utime = LinuxParser::UpTime(Pid());            // Time process running in seconds
    float totalTime = LinuxParser::ActiveJiffies(Pid());     // Time process was active
    
    cpu_utilization_ = (float) (totalTime / sysconf(_SC_CLK_TCK)) / pid_utime;
    
    return cpu_utilization_; 
    }  

// TODO: Return the command that generated this process
string Process::Command() { return command_; }

// TODO: Return this process's memory utilization
string Process::Ram() {  return Ram_; }

// TODO: Return the user (name) that generated this process
string Process::User() { return User_; }

// TODO: Return the age of this process (in seconds)
long Process::UpTime() { return  UpTime_; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { 
    
    return cpu_utilization_ > a.cpu_utilization_; //Overload Sort.  
    
}