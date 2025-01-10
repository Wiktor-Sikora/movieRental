#include <iostream>
#include <vector>
#include <string>

#include "db.h"
#include "movies.h"

int main() {
    MoviesQuerySet movies("Ojciec chrzestny II");
    std::cout << movies.querySet.size() << "\n";
    
    std::cout << movies << "\n";
    
    return 0;
}