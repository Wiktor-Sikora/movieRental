#include <iostream>
#include <string>
#include <ctime>

#include "db.h"
#include "movies.h"

Movie::Movie(
    std::string name, std::string description, 
    int released, float price=10, 
    int stock=10, int id=10
) : name(name), description(description),
    released(released), price(price),
    stock(stock), id(id)
{}

Movie::~Movie() {}

void Movie::saveToDb() {
    if (this->id) {
        
    }
    
}








