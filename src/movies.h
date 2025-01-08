#ifndef MOVIES_H
#define MOVIES_H

#include <iostream>
#include <vector>
#include <string>
#include "db.h"

class Movie {
    private:
        int id;

    public:
        std::string name;
        std::string description; 
        int released;
        float price;
        int stock;

        Movie(const std::string& name, const std::string& description, int released, float price=10.00, int stock=10, int id=-1);
        ~Movie();

        void deleteMovie() const;
        void saveToDb() const;
};

class MoviesQuerySet {
    private:
        std::string searchPhrase;
        std::vector<Movie> QuerySet;
        int userId;

    public:
        MoviesQuerySet(std::string& searchPhrase, int userId = -1);
        ~MoviesQuerySet();

        
};
#endif