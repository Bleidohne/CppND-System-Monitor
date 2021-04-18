#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  int Pid();                               // DONE: See src/process.cpp
  std::string User();                      // DONE: See src/process.cpp
  std::string Command();                   // DONE: See src/process.cpp
  float CpuUtilization();                  // DONE: See src/process.cpp
  std::string Ram();                       // DONE: See src/process.cpp
  long UpTime();                           // DONE: See src/process.cpp
  bool operator<(Process const& a) const;  // DONE: See src/process.cpp

  Process(int pid);                        // Constructor for Process class. 

  // DONE: Declare any necessary private members
 private:
   int pid_;                      // Process ID. 
   float cpu_utilization_;
   std::string command_;
   std::string Ram_;
   std::string User_;
   long UpTime_;

};

#endif