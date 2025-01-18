#include <iostream>
#include <string>
#include <ctime>
#include <format>

#include "db.h"
#include "users.h"
#include "finance.h"
#include "utils.h"

void Finance::saveToDb() {
    SQLiteDb DbHandler("database.db");

    if (this->id != -1) {
        DbHandler.execute(
            std::format("UPDATE finances SET\
                amount={}, user_id={}, date='{}'\
                WHERE id={};",
            this->amount,
            this->userId,
            DateTime(this->date),
            this->id
        ));
    } else {
        date = std::time(0);

        DbHandler.execute(
            std::format("INSERT INTO finances\
                (amount, user_id, date)\
                VALUES({}, {}, '{}');", 
            this->amount, 
            this->userId,
            DateTime(this->date)
        ));
        // TODO: update id after insert with
        // sqlite3_last_insert_rowid() or some shit like that
    }

    DbHandler.close();
}

void Finance::deleteFromDb() const {
    SQLiteDb DbHandler("database.db");

    if (this->id != -1) {
        DbHandler.execute(std::format("DELETE FROM finance WHERE id={};", this->id));
    }

    DbHandler.close();
}

std::ostream& operator<<(std::ostream& out, const Finance& finance) {
    return out << std::format("{}({})", finance.modelName, finance.amount);
};

double getProfit() {
    SQLiteDb DbHandler("database.db");

    std::vector<std::vector<std::string>> rows = DbHandler.query("SELECT SUM(amount) FROM finances WHERE amount > 0"); 

    DbHandler.close();

    return std::stod(rows.at(0).at(0));
}

double getExpenses() {
    SQLiteDb DbHandler("database.db");

    std::vector<std::vector<std::string>> rows = DbHandler.query("SELECT SUM(amount) FROM finances WHERE amount < 0"); 

    DbHandler.close();

    return std::stod(rows.at(0).at(0));
}

double getBalance() {
    SQLiteDb DbHandler("database.db");

    std::vector<std::vector<std::string>> rows = DbHandler.query("SELECT SUM(amount) FROM finances"); 

    DbHandler.close();

    return std::stod(rows.at(0).at(0));
}