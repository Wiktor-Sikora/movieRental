#include <iostream>
#include <vector>
#include <string>
#include "db.cpp"


int main() {
    SQLiteDb db_handler("database.db");


    std::vector<std::vector<std::string>> rows = db_handler.query("SELECT * FROM movies Where released > 2000");

    for (std::vector var1: rows) {
        for (std::string var2: var1) {
            std::cout << var2  << " | ";
        }

        std::cout << "\n";
    }

    
    return 0;
}