#include <iostream>
#include <string>
#include "sqlite3.h"
#include <format>
#include <vector>

#include "db.h"

SQLiteDb::SQLiteDb(const std::string& databaseName) : db(nullptr), dbName(databaseName) {
    this->open();
}

SQLiteDb::~SQLiteDb() {
    this->close();
}

bool SQLiteDb::open() {
    int result = sqlite3_open(dbName.c_str(), &db);
    if (result != SQLITE_OK) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    return true;
}

void SQLiteDb::close() {
    if (this->db) {
        sqlite3_close(this->db);
        this->db = nullptr;
    }
}

bool SQLiteDb::execute(const std::string& sql) {
    char* errorMessage = nullptr;
    int result = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errorMessage);

    if (result != SQLITE_OK) {
        std::cout << "SQL error: " << errorMessage << "\n";
        sqlite3_free(errorMessage);
        return false;
    } 
    
    return true;
}
    
std::vector<std::vector<std::string>> SQLiteDb::query(const std::string& sql) {
    char* errorMessage = nullptr;
    sqlite3_stmt* stmt;
    std::vector<std::vector<std::string>> result;
    // int result = sqlite3_prepare_v2(this->db, sql.c_str(), -1, &stmt, nullptr);

    if (sqlite3_prepare_v2(this->db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cout << "Failed to execute statement: " << sqlite3_errmsg(this->db) << "\n";
        return result;
    }

    int columnCount = sqlite3_column_count(stmt);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        std::vector<std::string> row;
        for (int i = 0; i < columnCount; ++i) {
            const char* columnText = reinterpret_cast<const char*>(sqlite3_column_text(stmt, i));
            row.push_back(columnText ? columnText : ""); // Handle NULL values
        }
        result.push_back(row);
    }

    if (sqlite3_finalize(stmt) != SQLITE_OK) {
        std::cout << "Failed to finalize statement: " << sqlite3_errmsg(this->db) << "\n";
    }

    return result;
}

std::ostream& operator<<(std::ostream& out, const BaseModel& model) {
    return out << std::format("{}", model.modelName);
}

