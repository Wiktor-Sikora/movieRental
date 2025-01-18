#ifndef USERS_H
#define USERS_H

#include <string>
#include <iostream>
#include <format>

#include "db.h"

class User: public BaseModel {
    public:
        std::string login;
        bool isAdmin = false;
        bool isAuthenticated = false;
        bool isBlocked = false;

        User(std::string login, bool isAdmin=false, bool isAuthenticated=false, int id=-1): BaseModel("User", id),
            login(login), isAdmin(isAdmin), isAuthenticated(isAuthenticated) {};
        ~User();

        void saveToDb(std::string password) const;
        void deleteFromDb() const override;
        bool authenticateUser(std::string password);

        friend std::ostream& operator<<(std::ostream& out, const User& user);
};
 
bool userExists(std::string login);
bool isBlocked(std::string login);

#endif
