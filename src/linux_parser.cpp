#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <unistd.h>

#include "linux_parser.h"

using std::stof;
using std::stol;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// [ML DONE]: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  
  string key;
  string line;
  bool found_Mem = 0;
  bool found_Free = 0;
  float Total_Mem; 
  float Free_Mem;
  float value;
 
  std::ifstream filestream(kProcDirectory + kMeminfoFilename); // Define the system path to read the Memory information

  if(filestream.is_open()){
     while(std::getline(filestream, line)){
       std::istringstream linestream(line);
       linestream >> key >> value;                            // parse the line.
          if(key == "MemTotal:"){
             Total_Mem = value;
             found_Mem = 1;                                   // mark total memory as found.
          }
             
          if(key == "MemFree:"){
             Free_Mem = value; 
             found_Free = 1;                                  // mark free memory as found.
          }

          if(found_Mem && found_Free)                         // Skip further searches when both values were found.
             return (Total_Mem - Free_Mem) / Total_Mem;          

     }      
  }

  return 0.0; // If filestream can not be opened or nothing can be found report 0.

}

// [ML DONE]: Read and return the system uptime
long LinuxParser::UpTime() { 
  
  string uptime;
  string line;

  std::ifstream stream(kProcDirectory + kUptimeFilename);

  if(stream.is_open()){
     std::getline(stream, line);
     std::istringstream linestream(line);
     linestream >> uptime;
     return std::stol(uptime);   
  }
 
  return 0; 

}

// [ML DONE]: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { 
  
  string line; 
  string key;
  long user_t, nice_t, system_t, idle_t, iowait_t, irq_t, sofirq_t, steal_t, guest_t, guest_nice_t;

  std::ifstream filestream(kProcDirectory + kStatFilename); // Define the system path to read the Memory information

  if(filestream.is_open()){
     while(std::getline(filestream, line)){
       std::istringstream linestream(line);
       linestream >> key;                            
       if(key == "cpu"){
         linestream >> user_t >> nice_t >> system_t >> idle_t >> iowait_t >> irq_t >> sofirq_t >> steal_t >> guest_t >> guest_nice_t; 
         return( user_t + nice_t + system_t + idle_t + iowait_t + irq_t + sofirq_t + steal_t + guest_t + guest_nice_t);
       }
     }
  }
    
  return 0; 
}

// [ML DONE]: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) { 
  
  string pid_s = std::to_string(pid);
  string line;
  string key; 
  long jiffies_active = 0;

  std::ifstream filestream(kProcDirectory + pid_s + kStatFilename); 

  if(filestream.is_open()){
     std::getline(filestream, line);
     std::istringstream linestream(line);

     for(int i=1; i<=17; i++){
        linestream >> key;
        if(i>=14 && i <=17){
          jiffies_active += std::stol(key);
        }

     }

     return jiffies_active;

  }
    
  return 0; 

}

// [ML DONE]: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { 
  
  string line; 
  string key;
  long user_t, nice_t, system_t, idle_t, iowait_t, irq_t, sofirq_t, steal_t, guest_t, guest_nice_t;

  std::ifstream filestream(kProcDirectory + kStatFilename); // Define the system path to read the Memory information

  if(filestream.is_open()){
     while(std::getline(filestream, line)){
       std::istringstream linestream(line);
       linestream >> key;                            
       if(key == "cpu"){
         linestream >> user_t >> nice_t >> system_t >> idle_t >> iowait_t >> irq_t >> sofirq_t >> steal_t >> guest_t >> guest_nice_t; 
         return( user_t + nice_t + system_t);
       }
     }
  }
    
  return 0; 
  
 }

// [ML DONE]: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { 
  
  string line; 
  string key;
  long user_t, nice_t, system_t, idle_t, iowait_t, irq_t, sofirq_t, steal_t, guest_t, guest_nice_t;

  std::ifstream filestream(kProcDirectory + kStatFilename); // Define the system path to read the Memory information

  if(filestream.is_open()){
     while(std::getline(filestream, line)){
       std::istringstream linestream(line);
       linestream >> key;                            
       if(key == "cpu"){
         linestream >> user_t >> nice_t >> system_t >> idle_t >> iowait_t >> irq_t >> sofirq_t >> steal_t >> guest_t >> guest_nice_t; 
         return(  idle_t );
       }
     }
  }
    
  return 0; 
}

// [ML DONE]: Read and return CPU utilization
float LinuxParser::CpuUtilization() { 
  
  static float ACTIVE_ = 0;
  static float TOTAL_ = 0;
  float active;
  float total;
  float utilization; 
   
  active = LinuxParser::ActiveJiffies();
  total = LinuxParser::Jiffies();

  if(total > 0 ){
     utilization = (active - ACTIVE_) / (total - TOTAL_);      
  } else {
    return 0;
  }

  ACTIVE_ = active;        // Safe the counts in global value to calculate DELTA ACTIVE / DELTA TOTAL
  TOTAL_ = total; 
      
  return utilization; // If division 0 would happen. 

  }

/*
float LinuxParser::CpuUtilization(int pid) { 
  
  static float ACTIVE_PID = 0;
  static float TOTAL_PID = 0;
  float active;
  float total;
  float utilization; 
   
  active = LinuxParser::ActiveJiffies(pid);
  total = LinuxParser::ActiveJiffies();

  if(total > 0 ){
     utilization = (active - ACTIVE_PID) / (total - TOTAL_PID);      
  } else {
    return 0;
  }

  ACTIVE_PID = active;        // Safe the counts in global value to calculate DELTA ACTIVE / DELTA TOTAL
  TOTAL_PID = total; 
      
  return utilization; // If division 0 would happen. 

  }
*/

// [ML DONE]: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  
  string line; 
  string key;
  int active_processes;

  std::ifstream filestream(kProcDirectory + kStatFilename);
  if(filestream.is_open()){
     while(std::getline(filestream, line)){
       std::istringstream linestream(line);
       linestream >> key;                            
       if(key == "processes"){
         linestream >> active_processes;
         return active_processes;
       }
     }
  }

  
  
  return 0; 
  
}

// [ML DONE]: Read and return the number of running processes
int LinuxParser::RunningProcesses() {   
  
  string line; 
  string key;
  int running_processes;

  std::ifstream filestream(kProcDirectory + kStatFilename);
  if(filestream.is_open()){
     while(std::getline(filestream, line)){
       std::istringstream linestream(line);
       linestream >> key;                            
       if(key == "procs_running"){
         linestream >> running_processes;
         return running_processes;
       }
     }
  }
 
  
  return 0; 
  
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) { 
  
  string pid_s = std::to_string(pid);
  string line;
  string key;
  
  std::ifstream filestream(kProcDirectory + pid_s + kCmdlineFilename); 
  
  if(filestream.is_open()){
     std::getline(filestream, line);
     std::istringstream linestream(line);
     linestream >> key;
     return key;
  }


  return {}; // Empty Stream. 
  
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  
  string pid_s = std::to_string(pid);
  string line;
  string key; 
  string VmSize;
  
  std::ifstream filestream(kProcDirectory + pid_s + kStatusFilename); 
  
  if(filestream.is_open()){
     while(std::getline(filestream, line)){
        std::istringstream linestream(line);
        linestream >> key; 
        if(key =="VmSize:"){
           linestream >> VmSize;
           return to_string(stol(VmSize)/1024);
        }     
     }
  }
  
  return {"none"}; 

}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
  
  string pid_s = std::to_string(pid);
  string line;
  string key; 
  string Uid_;
  
  std::ifstream filestream(kProcDirectory + pid_s + kStatusFilename); 
  
  if(filestream.is_open()){
     while(std::getline(filestream, line)){
        std::istringstream linestream(line);
        linestream >> key; 
        if(key == "Uid:"){
           linestream >> Uid_;
           return Uid_;
        }     
     }
  } 
  
  return {}; 
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
  
  string user_ID = LinuxParser::Uid(pid);

  string line;
  string username_; 

  std::ifstream filestream(kPasswordPath); 

  if(filestream.is_open()){
     while(std::getline(filestream, line)){
        if(line.find(user_ID)){
           std::replace(line.begin(), line.end(), ':', ' ');
           std::istringstream linestream(line);
           linestream >> username_; 
           return username_;
        }     
     }
  }
  
  return {}; 
  
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { 
  
  string pid_s = std::to_string(pid);
  string line;
  string key; 
  int i=0;
  long uptime_ = 0;

  std::ifstream filestream(kProcDirectory + pid_s + kStatFilename); 

  if(filestream.is_open()){
     while(std::getline(filestream, line)){
     std::stringstream linestream(line);

     while(linestream >> key){
       i++;
       if(i == 22 ){
          uptime_ = stol(key) ;
          return (LinuxParser::UpTime() - (long)((float)uptime_ / (float) sysconf(_SC_CLK_TCK)));
       }
          
     }
     }

     

  }
  
  return 0; 
  
}
