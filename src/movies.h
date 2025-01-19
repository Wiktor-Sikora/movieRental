#ifndef MOVIES_H
#define MOVIES_H

#include <iostream>
#include <vector>
#include <string>
#include <ctime>

#include "db.h"
#include "users.h"
#include "utils.h"

class Movie: public BaseModel {
    public:
        std::string name;
        std::string description; 
        int released;
        float price;
        int stock;

        Movie(const std::string& name, const std::string& description, int released, float price=10.00, int stock=10, int id=-1): BaseModel("Movie", id),
        name(name), description(description), released(released), price(price), stock(stock) {};
        ~Movie();

        void saveToDb() override;
        void deleteFromDb() const override;
        bool rentMovie(int userId);
        bool unRentMovie(int userId);

        friend std::ostream& operator<<(std::ostream& out, const Movie& movie);
};

class MoviesQuerySet {
    private:
        std::string searchPhrase;
        int userId;

    public:
        std::vector<Movie> querySet;

        MoviesQuerySet(const std::string& searchPhrase, int userId = -1, bool onlyInRental = false);
        ~MoviesQuerySet();

        friend std::ostream& operator<<(std::ostream& out, const MoviesQuerySet& movies);
};


#endif
