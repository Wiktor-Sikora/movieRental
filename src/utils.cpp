#include <iostream>
#include <string>
#include <ctime>

#include "utils.h"

time_t parseDateTime(const char* datetimeString, const char* format) {
    struct tm tmStruct;
    //strptime(datetimeString, format, &tmStruct);
    return mktime(&tmStruct);
}

std::string DateTime(time_t time, const char* format) {
    char buffer[90];
    struct tm* timeinfo = localtime(&time);
    strftime(buffer, sizeof(buffer), format, timeinfo);
    return buffer;
}