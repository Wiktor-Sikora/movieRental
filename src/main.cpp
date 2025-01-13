#include <iostream>
#include <vector>
#include <string>

#include "db.h"
#include "movies.h"
#include "menu.h"

int main() {
    MoviesQuerySet movies("Ojciec chrzestny II");
    std::cout << movies.querySet.size() << "\n";
    
    std::cout << movies << "\n";

    std::string initialOptions[] = {"Offer", "Sign Up", "Sign In", "Exit"};
    Menu menu(initialOptions, 4);

    menu.updateMenuOptions(); 
    menu.navigation();
    
    return 0;
}