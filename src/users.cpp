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
            sql.insert(65, std::format(", '{}'", password));
        };

        DbHandler.execute(sql);
        // TODO: update id after insert with
        // sqlite3_last_insert_rowid() or some shit like that
    }

    DbHandler.close();
}

void User::deleteUser() const {
    SQLiteDb DbHandler("database.db");

    if (this->id != -1) {
        DbHandler.execute(std::format("DELETE FROM users WHERE id={};", this->id));
    }

    DbHandler.close();
}

bool User::authenticateUser(std::string password) {
    SQLiteDb DbHandler("database.db");

    std::vector<std::vector<std::string>> rows = DbHandler.query(std::format("SELECT id, is_admin FROM users WHERE login='{}' AND password='{}';", this->login, password));
    if (rows.size() > 0) {
        this->id = stoi(rows.at(0).at(0));
        this->isAdmin = stoi(rows.at(0).at(1));
        this->isAuthenticated = true;
        DbHandler.close();
        return true;
    } else {
        DbHandler.close();
        return false;
    };
}

void User::blockUser() {
    SQLiteDb dbHandler("database.db");
    std::string sql = std::format(
        "UPDATE users SET is_blocked={} WHERE login='{}'",
        (this->isBlocked? 1 : 0),
        this->login
    );

    dbHandler.execute(sql);

    dbHandler.close();
}

void User::unBlockUser() {
    SQLiteDb dbHandler("database.db");
    std::string sql = std::format(
        "UPDATE users SET is_blocked={} WHERE login='{}'",
        (this->isBlocked? 0 : 1),
        this->login
    );

    dbHandler.execute(sql);

    dbHandler.close();
}

bool userExists(std::string login) {
    SQLiteDb dbHandler("database.db");
    std::string sql = std::format("SELECT login FROM users WHERE login='{}'", login);

    auto result = dbHandler.query(sql);
    dbHandler.close();

    return !result.empty();
}