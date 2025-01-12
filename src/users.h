#ifndef USERS_H
#define USERS_H

#include <string>
#include <iostream>
#include <format>
#include "movies.h"
#include "db.h"

class User {
    private:
        int id;

    public:
        std::string login;
        bool isAdmin;
        bool isBlocked;
        bool isAuthenticated;

        User(std::string login, bool isAdmin=false, bool isBlocked=false, int id=-1): 
            login(login), isAdmin(isAdmin), isBlocked(isBlocked), id(id) {};
        ~User();

        void saveToDb() const;
        void deleteMovie() const;
        int getId() const {return this->id;};
        bool authenticateUser(std::string password);
        bool registerUser(std::string login, std::string password);
        void rentMovie(int movieId);
        void 
};
 
bool userExists(std::string login) {
    SQLiteDb dbHandler("database.db");
    std::string sql = std::format("SELECT login FROM users WHERE login={}", login);
    if (dbHandler.execute(sql)) {
        return true;
    } else {
        return false;
    }
}


#endif
