#include <iostream>
#include <vector>
#include <string>

#include "db.h"
#include "movies.h"
#include "menu.h"
#include "utils.h"

int main() {
    initilizeDbOnFirstRun();

    // MoviesQuerySet movies("Ojciec ");
    // std::cout << movies.querySet.size() << "\n";
    // for (auto movie : movies.querySet) {
    //     std::cout << movie.description << "\n";
    // }

    Menu mainMenu(nullptr, 0);
    mainMenu.updateMenuOptions();
    mainMenu.navigation();
    
    return 0;
}