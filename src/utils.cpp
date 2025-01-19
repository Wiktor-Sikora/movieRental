#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <time.h>
#include <iomanip>
#include <sstream>
#include <locale>

#include "utils.h"
#include "db.h"

extern "C" char* strptime(const char* s, const char* f, struct tm* tm) {
  std::istringstream input(s);
  input.imbue(std::locale(setlocale(LC_ALL, nullptr)));
  input >> std::get_time(tm, f);
  if (input.fail()) {
    return nullptr;
  }
  return (char*)(s + input.tellg());
}

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

int getTrueLength(std::string &str) {
    size_t length = 0;
    for (size_t i = 0; i < str.size(); ) {
        unsigned char c = static_cast<unsigned char>(str[i]);
        if ((c & 0x80) == 0) { // 1-byte character (ASCII)
            i += 1;
        } else if ((c & 0xE0) == 0xC0) { // 2-byte character
            i += 2;
        } else if ((c & 0xF0) == 0xE0) { // 3-byte character
            i += 3;
        } else if ((c & 0xF8) == 0xF0) { // 4-byte character
            i += 4;
        } else {
            throw std::runtime_error("Invalid UTF-8 sequence");
        }
        ++length; // Count each valid character
    }
    return length;
}