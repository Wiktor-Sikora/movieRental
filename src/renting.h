#ifndef RENTING_H
#define RENTING_H

#include <iostream>
#include <vector>
#include <string>

#include "movies.h"
#include "users.h"

class Renting{
    User* currentUser;
    public:
    bool isDisplay = true;
    void displayRentedMovies(User &currentUser);
    void displayRentedMovieDetails(Movie& movie, User &currentUser);

};

#endif