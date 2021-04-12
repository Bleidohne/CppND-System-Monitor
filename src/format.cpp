#include <string>

#include "format.h"

using std::string;
using std::to_string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds /*[[maybe_unused]]*/) { 
    
   long hours;
   long minutes;

   hours = seconds / 3600;                      // Extract hours
   seconds = seconds - hours * 3600; 

   minutes = seconds / 60;                      // Extract minutes
   seconds = seconds - minutes * 60; 
 
   return to_string(hours) + ":" + to_string(minutes) + ":" + to_string(seconds);  // Build output string
    
}