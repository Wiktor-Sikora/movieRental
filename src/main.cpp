#include <iostream>
#include <vector>
#include <string>

#include "db.h"
#include "movies.h"
#include "menu.h"

int main() {
    // MoviesQuerySet movies("Ojciec chrzestny II");
    // std::cout << movies.querySet.size() << "\n";
    
    // std::cout << movies << "\n";

    Menu mainMenu(nullptr, 0);
    mainMenu.updateMenuOptions();
    mainMenu.navigation();
    
    return 0;
}