#ifndef MOVIES_H
#define MOVIES_H

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

        Movie(std::string name, std::string description, int released, float price, int stock, int id);
        ~Movie();

        void deleteMovie();
        void saveToDb();
};

#endif