#ifndef FINANCE_H
#define FINANCE_H

#include <iostream>
#include <vector>
#include <string>
#include <ctime>

#include "db.h"
#include "users.h"
#include "movies.h"
#include "utils.h"

class Finance: public BaseModel {
    private:
        time_t date;

    public:
        int userId;
        double amount;

        Finance(double amount, int userId=-1, int id=-1): BaseModel("Finance", id), amount(amount), userId(userId) {};
        ~Finance() {};

        void saveToDb() override;
        void deleteFromDb() const override;
        std::string getDateHuman() const {return DateTime(this->date);};

        friend std::ostream& operator<<(std::ostream& out, const Finance& finance);
};

double getProfit();
double getExpenses();
double getBalance();

#endif