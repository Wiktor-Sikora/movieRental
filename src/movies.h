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
    private:

    public:
        std::string name;
        std::string description; 
        int released;
        float price;
        int stock;

        time_t date;
        bool isInRenting = false;
        std::string rentedByLogin; // User login
        int rentedById; // User id

        Movie(const std::string& name, const std::string& description, int released, float price=10.00, int stock=10, int id=-1): BaseModel("Movie", id),
        name(name), description(description), released(released), price(price), stock(stock) {};
        ~Movie();

        void saveToDb() override;
        void deleteFromDb() const override;
        bool rentMovie(int userId);
        bool unRentMovie(int userId);

        std::string getRentedDateHuman() {return DateTime(this->date);};

        friend std::ostream& operator<<(std::ostream& out, const Movie& movie);
};

class MoviesQuerySet {
    private:
        std::string searchPhrase;
        int userId;

    public:
        std::vector<Movie> querySet;

        MoviesQuerySet(const std::string& searchPhrase, int userId = -1, bool searchByRental = false, bool onlyNotReturned = false);
        ~MoviesQuerySet();

        friend std::ostream& operator<<(std::ostream& out, const MoviesQuerySet& movies);
};

// class RentedMovie: public BaseModel {
//     private:
//         time_t date; // the day that movie was rented

//     public:
//         bool returned;
//         User user;
//         Movie movie;

//         RentedMovie(Movie movie, User user, bool returned, time_t date, int id=-1): BaseModel("RentedMovie", id),
//         movie(movie), user(user), returned(returned) {}
            
//         std::string getHumanDate() {};
//         std::string getTime_tDate() {};
// };

#endif
