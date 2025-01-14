#ifndef TIME_MANIPULATION_H
#define TIME_MANIPULATION_H

#include <ctime>
#include <string>

// @brief function to convert string to time_t type, for example: 
// time_t moment = parseDateTime("2023-06-17 12:36:51", "%Y-%m-%d %H:%M:%S")
/// @param datetimeString string to parse. Example: "2023-06-17 12:36:51" 
/// @param format format to display in. Example: "%Y-%m-%d %H:%M:%S" 
/// @return time_t
time_t parseDateTime(const char* datetimeString, const char* format = "%Y-%m-%d %H:%M:%S");

// @brief function to convert time_t type to string, for example: 
// time_t momentString = DateTime(1627303429, "%Y-%m-%d %H:%M:%S")
/// @param datetimeString time_t object to parse. Example: 1627303429 
/// @param format format to display in. Example: "%Y-%m-%d %H:%M:%S" 
/// @return std::string
std::string DateTime(time_t time, const char* format = "%Y-%m-%d %H:%M:%S");

void initilizeDbOnFirstRun();
    
#endif