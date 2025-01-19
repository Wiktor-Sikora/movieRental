#include <iostream>
#include <string>
#include <ctime>
#include <format>

#include "db.h"
#include "movies.h"
#include "finance.h"
#include "users.h"


Movie::~Movie() {}

void Movie::saveToDb() {
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

        Finance finance(this->price * (-1) * this->stock);
        finance.saveToDb();
        // TODO: update id after insert with
        // sqlite3_last_insert_rowid() or some shit like that
    }

    DbHandler.close();
}

void Movie::deleteFromDb() const {
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
        std::format("INSERT INTO rental (movie_id, user_id, returned, date) VALUES({}, {}, 0, '{}');",
        this->id,
        userId,
        DateTime(std::time(0))
    ));

    this->stock -= 1;
    this->saveToDb();
    
    DbHandler.close();

    Finance finance(this->price, userId);
    finance.saveToDb();

    return true;
}

bool Movie::unRentMovie(int userId) {
    SQLiteDb DbHandler("database.db");

    if (userId == -1) {
        return false;
    }

    DbHandler.execute(
        std::format("UPDATE rental SET returned=1 WHERE movie_id={} and user_id={};",
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
MoviesQuerySet::MoviesQuerySet(const std::string& searchPhrase, int userId, bool searchByRental, bool onlyNotReturned) {
    SQLiteDb DbHandler("database.db");
    std::vector<std::vector<std::string>> rows;
    std::string sql;

    if (!searchByRental) { // searches for movies by searchPhrase
        sql = std::format(
            "SELECT name, description, released, price, in_stock, id FROM movies Where name LIKE '%{}%';", 
            searchPhrase
        );
    } else if (searchByRental && userId != -1 && onlyNotReturned) { // searches for movies rented by specific user that are not returned
        sql = std::format("SELECT movies.name, movies.description, movies.released, movies.price, movies.in_stock, movies.id,\
            rental.returned, rental.date, users.login, users.id\
            FROM movies JOIN rental ON movies.id = rental.movie_id JOIN users ON users.id = rental.user_id WHERE rental.user_id = {} AND rental.returned = 0", 
            userId
        );
    } else if (searchByRental && userId != -1) { // searches for movies rented by specific user
        sql = std::format("SELECT movies.name, movies.description, movies.released, movies.price, movies.in_stock, movies.id,\
            rental.returned, rental.date, users.login, users.id\
            FROM movies JOIN rental ON movies.id = rental.movie_id JOIN users ON users.id = rental.user_id WHERE rental.user_id = {}", userId);
    } else { // // searches for all movies that were rented
        sql = "SELECT movies.name, movies.description, movies.released, movies.price, movies.in_stock, movies.id,\
            rental.returned, rental.date, users.login, users.id\
            FROM movies JOIN rental ON movies.id = rental.movie_id JOIN users ON users.id = rental.user_id";
    }

    rows = DbHandler.query(sql); 
    for (std::vector row : rows) {
        this->querySet.push_back(Movie(
            row.at(0),
            row.at(1),
            std::stoi(row.at(2)),
            std::stof(row.at(3)),
            std::stoi(row.at(4)),
            std::stoi(row.at(5))
        ));

        if (!searchByRental) {continue;};
        
        this->querySet.back().isInRenting = std::stoi(row.at(6));
        this->querySet.back().date = parseDateTime(row.at(7).c_str());
        this->querySet.back().rentedByLogin = row.at(8);
        this->querySet.back().rentedById = std::stoi(row.at(9));
    }

    DbHandler.close();
}

std::ostream& operator<<(std::ostream& out, const Movie& movie) {
    return out << std::format("{}({})", movie.modelName, movie.name);
}

MoviesQuerySet::~MoviesQuerySet() {}

std::ostream& operator<<(std::ostream& out, const MoviesQuerySet& movies) {
    out << "[";
    if (movies.querySet.size() > 0) {
        for (int i = 0; i < movies.querySet.size() - 1; i++) {
            out << movies.querySet.at(i) << ", ";
        }
        out << movies.querySet.back();
    }
    out << "]";
    return out;
}
