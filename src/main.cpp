#include <iostream>
#include <vector>
#include <string>

#include "db.h"
#include "movies.h"

int main() {
    SQLiteDb db_handler("database.db");

    Movie movie(
        "Przełęcz ocalonych", 
        "Schyłek II wojny światowej. Podczas krwawej bitwy o Okinawę amerykański sanitariusz odmawia noszenia broni i zabijania z powodów moralnych.", 
        2016
    );
    movie.saveToDb();
    
    // std::vector<std::vector<std::string>> rows = db_handler.query("SELECT * FROM movies Where released > 2000");

    // for (std::vector var1: rows) {
    //     for (std::string var2: var1) {
    //         std::cout << var2  << " | ";
    //     }

    //     std::cout << "\n";
    // }
    
    db_handler.close();
    return 0;
}