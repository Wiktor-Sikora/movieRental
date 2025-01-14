#include <iostream>
#include <string>
#include <ctime>
#include <format>

#include "db.h"
#include "movies.h"
#include "users.h"

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
    SQLiteDb DbHandler("database.db");

    if (this->id != -1) {
        DbHandler.execute(
            std::format("UPDATE movies SET\
                name='{}', description='{}',\
                released={}, price={}, in_stock={}\
                WHERE id={};",
            this->name,
            this->description,
            this->released,
            this->price,
            this->stock,
            this->id
        ));
    } else {
        DbHandler.execute(
            std::format("INSERT INTO movies\
                (name, description, released, price, in_stock)\
                VALUES('{}', '{}', {}, {}, {});", 
            this->name, 
            this->description,
            this->released,
            this->price,
            this->stock
        ));
        // TODO: update id after insert with
        // sqlite3_last_insert_rowid() or some shit like that
    }

    DbHandler.close();
}

void Movie::deleteMovie() const {
    SQLiteDb DbHandler("database.db");

    if (this->id != -1) {
        DbHandler.execute(std::format("DELETE FROM movies WHERE id={};", this->id));
    }

    DbHandler.close();
}

bool Movie::rentMovie(int userId) {
    SQLiteDb DbHandler("database.db");

    if (userId == -1 || this->stock < 1) {
        return false;
    }

    DbHandler.execute(
        std::format("INSERT INTO rental (movie_id, user_id, date) VALUES({}, {}, '{}');",
        this->id,
        userId,
        DateTime(std::time(0))
    ));

    this->stock -= 1;
    this->saveToDb();
    
    DbHandler.close();

    return true;
}

bool Movie::unRentMovie(int userId) {
    SQLiteDb DbHandler("database.db");

    if (userId == -1) {
        return false;
    }

    DbHandler.execute(
        std::format("DELETE FROM rental WHERE movie_id={} and user_id={};",
        this->id,
        userId
    ));

    this->stock += 1;

    this->saveToDb();

    DbHandler.close();
    return true;
};


/**
 * Fills the class with Movie objects
 * 
 * @param searchPhrase gets movies with similiar name
 * @param userId gets movies that are rented by a user
*/
MoviesQuerySet::MoviesQuerySet(const std::string& searchPhrase, int userId) {
    SQLiteDb DbHandler("database.db");
    std::vector<std::vector<std::string>> rows;

    if (userId == - 1) {
        std::string sqlQuery = std::format("SELECT * FROM movies Where name LIKE '%{}%';", searchPhrase);        
        rows = DbHandler.query(sqlQuery); 
    } else {
        // TODO: 
    }

    for (std::vector row : rows) {
        this->querySet.push_back(Movie(
            row.at(1),
            row.at(2),
            std::stoi(row.at(3)),
            std::stof(row.at(4)),
            std::stoi(row.at(5)),
            std::stoi(row.at(0))
        ));
    }

    DbHandler.close();
}

MoviesQuerySet::~MoviesQuerySet() {}

std::ostream& operator<<(std::ostream& out, const MoviesQuerySet& movies) {
    out << "[";
    if (movies.querySet.size() > 0) {
        for (int i = 0; i < movies.querySet.size() - 1; i++) {
            out << "Movie(" << movies.querySet.at(i).name << "), ";
        }
        out << "Movie(" << movies.querySet.at(movies.querySet.size() - 1).name <<  ")";
    }
    out << "]";
    return out;
}
