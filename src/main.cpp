#include <iostream>
#include <vector>
#include <string>

#include "db.h"
#include "movies.h"

int main() {
    MoviesQuerySet movies("oj");
    std::cout << movies.querySet.size() << "\n";
    
    std::cout << movies << "\n";
    
    return 0;
}