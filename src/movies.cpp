#include <iostream>
#include <string>
#include <ctime>

class Movie {
private:
    int id;

public:
    std::string name;
    std::string description;
    // only year, soo date object is not necessary
    int released;
    float price;
    int stock;

    Movie(
        std::string name, 
        std::string description, 
        int released,
        float price = 10,
        int stock = 10,
        int id = NULL 
    ) {
        this->name = name;
        this->description = description;
        this->released = released;
        this->price = price;
        this->stock = stock;
        this->id = id;
    };
    
    bool saveToDb() {
        if (this->id) {
            
        }
        
    }

    ~Movie();
};






