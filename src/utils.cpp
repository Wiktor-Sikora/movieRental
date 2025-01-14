#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <chrono>
#include <thread>


#include "utils.h"
#include "db.h"

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

void initilizeDbOnFirstRun() {
    std::ifstream configFile("config.txt");
    std::string fileContent{std::istreambuf_iterator<char>(configFile), std::istreambuf_iterator<char>()};

    if(std::stoi(std::string{fileContent[20]}) == 1) {
        configFile.close();
        return;
    }

    configFile.close();
    fileContent.erase();

    std::ifstream sqlFile("src/db/scheme.sql");
    std::string fileContent{std::istreambuf_iterator<char>(sqlFile), std::istreambuf_iterator<char>()};
    std::cout << fileContent;    

    std::chrono::seconds timespan(5);
    std::this_thread::sleep_for(timespan);
};
