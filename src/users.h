#ifndef USERS_H
#define USERS_H

#include <string>
#include <iostream>
#include <format>

#include "db.h"

class User {
    private:
        int id;
    public:
        std::string login;
        bool isAdmin = false;
        bool isAuthenticated = false;

        User(std::string login, bool isAdmin=false, bool isAuthenticated=false, int id=-1): 
            login(login), isAdmin(isAdmin), isAuthenticated(isAuthenticated), id(id) {};
        ~User();

        void saveToDb(std::string password);
        void deleteUser() const;
        int getId() const {return this->id;};
        bool authenticateUser(std::string password);
};
 
bool userExists(std::string login);

#endif
