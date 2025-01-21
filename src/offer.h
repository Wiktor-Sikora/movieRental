#ifndef OFFER_H
#define OFFER_H

#include <iostream>
#include <vector>
#include <string>

#include "movies.h"
#include "users.h"

class Offer{
    public:
    bool isDisplay = true;
    void displayMovies(User &currentUser);
    void displayMovieDetails(Movie& movie, User &currentUser);

    void addMovie();
    void displayForDeletion(Movie& movie, User &currentUser);
};

#endif