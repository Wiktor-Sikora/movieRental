#include <iostream>
#include <string>
#include <ctime>
#include <fstream>

#include "utils.h"
#include "db.h"

time_t parseDateTime(const char* datetimeString, const char* format) {
    struct tm tmStruct;
    strptime(datetimeString, format, &tmStruct);
    return mktime(&tmStruct);
}

std::string DateTime(time_t time, const char* format) {
    char buffer[100];
    struct tm* timeinfo = localtime(&time);
    std::strftime(buffer, sizeof(buffer), format, timeinfo);
    return buffer;
}

void initilizeDbOnFirstRun() {
    std::ifstream configFile1("config.txt");
    std::string fileContent{std::istreambuf_iterator<char>(configFile1), std::istreambuf_iterator<char>()};

    if(std::stoi(std::string{fileContent[20]}) == 1) {
        configFile1.close();
        return;
    }
    configFile1.close();

    std::ofstream configFile2("config.txt", std::ios::trunc);
    configFile2 << "was_db_initilized = 1";
    configFile2.close();

    std::ifstream sqlFile("src/db/scheme.sql");
    fileContent = std::string(std::istreambuf_iterator<char>(sqlFile), std::istreambuf_iterator<char>());

    SQLiteDb dbHandler("database.db");

    dbHandler.execute(fileContent);

    dbHandler.close();

    sqlFile.close();
};
