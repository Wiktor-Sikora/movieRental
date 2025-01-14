#ifndef OFFER_H
#define OFFER_H

#include <iostream>
#include <vector>
#include <string>

#include "db.h"
#include "movies.h"
#include "users.h"

class Offer{
    User* currentUser;
    public:
    void displayMovies(User &currentUser);
    void displayMovieDetails(Movie& movie, User &currentUser);
};

#endif