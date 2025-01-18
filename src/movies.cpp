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

        Finance finance(this->price * (-1));
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
        std::format("INSERT INTO rental (movie_id, user_id, date) VALUES({}, {}, '{}');",
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
    std::string sql;

    if (userId == - 1) {
        sql = std::format("SELECT * FROM movies Where name LIKE '%{}%';", searchPhrase);
    } else {
        sql = std::format("SELECT * FROM movies INNER JOIN rental ON movies.id = rental.movie_id WHERE rental.user_id = {}", userId);
    }

    rows = DbHandler.query(sql); 
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
        out << movies.querySet.at(movies.querySet.size() - 1);
    }
    out << "]";
    return out;
}
