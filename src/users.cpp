#include <string>
#include <iostream>
#include <string>
#include <format>
#include <ctime>

#include "users.h"
#include "db.h"

User::~User() {}

void User::saveToDb(std::string password) {
    SQLiteDb DbHandler("database.db");

    if (this->id != -1) {
        std::string sql = std::format(
            "UPDATE users SET login='{}', is_admin={}, is_blocked={} WHERE id={};",
            this->login,
            (this->isAdmin ? 1 : 0),
            (this->isBlocked ? 1 : 0),
            this->id
        );
        DbHandler.execute(sql);
    } else {
        std::string sql = std::format("INSERT INTO users (login, is_admin) VALUES('{}', {});",
            this->login,
            (this->isAdmin ? 1 : 0)
        );
        if (password != "") {
            sql.insert(34, ", password");
            sql.insert(58 + this->login.length(), std::format(", '{}'", password));
        };

        DbHandler.execute(sql);
        // TODO: update id after insert with
        // sqlite3_last_insert_rowid() or some shit like that
    }

    DbHandler.close();
}

void User::deleteFromDb() const {
    SQLiteDb DbHandler("database.db");

    if (this->id != -1) {
        DbHandler.execute(std::format("DELETE FROM users WHERE id={};", this->id));
    }

    DbHandler.close();
}

bool User::authenticateUser(std::string password) {
    SQLiteDb DbHandler("database.db");

    std::vector<std::vector<std::string>> rows = DbHandler.query(std::format("SELECT id, is_admin FROM users WHERE login='{}' AND password='{}';", this->login, password));
    DbHandler.close();

    if (rows.size() == 0) {
        return false;
    }
    
    this->id = stoi(rows.at(0).at(0));
    this->isAdmin = stoi(rows.at(0).at(1));
    this->isAuthenticated = true;
    
    return true;
}

std::ostream& operator<<(std::ostream& out, const User& user) {
    return out << std::format("{}({})", user.modelName, user.login);
}

bool userExists(std::string login) {
    SQLiteDb dbHandler("database.db");
    std::string sql = std::format("SELECT login FROM users WHERE login='{}'", login);

    auto result = dbHandler.query(sql);
    dbHandler.close();

    return !result.empty();
}

bool isBlocked(std::string login) {
    SQLiteDb DbHandler("database.db");
    std::vector<std::vector<std::string>> rows = DbHandler.query(std::format("SELECT is_blocked FROM users WHERE login='{}';", login));
    DbHandler.close();
    
    if (rows.size() == 0 || stoi(rows.at(0).at(0)) == 1) {
        return true;
    }
    return false;
}

User getUser(std::string login) {
    SQLiteDb DbHandler("database.db");
    std::vector<std::vector<std::string>> rows = DbHandler.query(std::format("SELECT id, is_admin FROM users WHERE login='{}';", login));
    DbHandler.close();
    
    User user(login, std::stoi(rows.at(0).at(1)), false, std::stoi(rows.at(0).at(0)));
    return user;
}

