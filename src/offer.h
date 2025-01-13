#ifndef OFFER_H
#define OFFER_H

#include <iostream>
#include <vector>
#include <string>

#include "db.h"
#include "movies.h"

class Offer{
    public:
    void displayMovies();
    void displayMovieDetails(const Movie& movie);
};

#endif