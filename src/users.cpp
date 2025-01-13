#include <string>
#include <iostream>
#include <string>
#include <format>
#include <ctime>

#include "users.h"
#include "db.h"

void User::saveToDb(std::string password) const {
    SQLiteDb DbHandler("database.db");

    if (this->id != -1) {
        std::string sql = std::format(
            "UPDATE movies SET login='{}', is_admin={}",
            this->login,
            (this->isAdmin ? 1 : 0)
        );
        if (password != "") {
            sql += std::format(", password='{}'", password);
        };
        sql += ";";
        DbHandler.execute(sql);
    } else {
        std::string sql = std::format("INSERT INTO users (login, is_admin) VALUES('{}', {});",
            this->login,
            (this->isAdmin ? 1 : 0)
        );
        if (password != "") {
            sql.insert(34, ", password");
            sql.insert(61, std::format(", '{}'", password));
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

    std::vector<std::vector<std::string>> rows = DbHandler.query(std::format("SELECT id FROM users WHERE login='{}' AND password='{}';", this->login, password));
    if (rows.size() > 0) {
        this->id = stoi(rows.at(0).at(0));
        DbHandler.close();
        return true;
    } else {
        DbHandler.close();
        return false;
    };
}

bool userExists(std::string login) {
    SQLiteDb dbHandler("database.db");
    std::string sql = std::format("SELECT login FROM users WHERE login={}", login);
    if (dbHandler.execute(sql)) {
        dbHandler.close();
        return true;
    } else {
        dbHandler.close();
        return false;
    }
}