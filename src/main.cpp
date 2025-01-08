#include <iostream>
#include <vector>
#include <string>

#include "db.h"
#include "movies.h"

int main() {
    MoviesQuerySet movies("p"); 
    std::cout << movies << "\n";
    
    return 0;
}