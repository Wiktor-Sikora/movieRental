#include <string>
#include <iostream>
#include <string>
#include <format>

#include "users.h"
#include "db.h"

void User::saveToDb(std::string password) const {
    SQLiteDb db_handler("database.db");

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
        db_handler.execute(sql);
    } else {
        std::string sql = std::format("INSERT INTO users (login, is_admin) VALUES('{}', {});",
            this->login,
            (this->isAdmin ? 1 : 0)
        );
        if (password != "") {
            sql.insert(34, ", password");
            sql.insert(61, std::format(", '{}'", password));
        };
        
        db_handler.execute(sql);
        // TODO: update id after insert with
        // sqlite3_last_insert_rowid() or some shit like that
    }

    db_handler.close();
}