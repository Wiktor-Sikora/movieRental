#include <iostream>
#include <string>
#include <ctime>
#include <format>

#include "db.h"
#include "movies.h"

Movie::Movie(
    const std::string& name, const std::string& description, 
    int released, float price, 
    int stock, int id
) : name(name), description(description),
    released(released), price(price),
    stock(stock), id(id)
{}

Movie::~Movie() {}

void Movie::saveToDb() const {
    SQLiteDb db_handler("database.db");

    // TODO
    // if (this->id != -1) {
    //     db_handler.execute(
    //         std::format("")
    //     );
    // } else {
    db_handler.execute(
        std::format("INSERT INTO movies (name, description, released, price, in_stock) VALUES('{}', '{}', {}, {}, {});", 
        this->name, 
        this->description,
        this->released,
        this->price,
        this->stock
    ));

    db_handler.close();
}
