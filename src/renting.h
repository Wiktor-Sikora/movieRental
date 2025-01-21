#ifndef RENTING_H
#define RENTING_H

#include <iostream>
#include <vector>
#include <string>

#include "movies.h"
#include "users.h"

class Renting{
    public:
    bool isDisplay = true;
    void displayRentedMovies(User &currentUser);
    void displayRentedMovieDetails(Movie& movie, User &currentUser);

    void displayRentalHistory(User &currentUser);
};

#endif