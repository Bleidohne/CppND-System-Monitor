#include "processor.h"
#include "linux_parser.h"

using namespace LinuxParser;

// [ML DONE]: Return the aggregate CPU utilization
float Processor::Utilization() { return LinuxParser::CpuUtilization(); }