#ifndef DB_H
#define DB_H
#include "sqlite3.h"
#include <vector>
#include <string>

class SQLiteDb {
    sqlite3* db;
    std::string dbName;

    public:
        SQLiteDb(const std::string& databaseName);
        ~SQLiteDb();

        bool open();
        void close();
        bool execute(const std::string& sql);
        std::vector<std::vector<std::string>> query(const std::string& sql);
};

class BaseModel {
    protected:
        int id;
        std::string modelName;

    public:
        BaseModel(std::string modelName, int id=-1): modelName(modelName), id(id) {};
        ~BaseModel() {};

        virtual void saveToDb() const {};
        virtual void deleteFromDb() const {};
        int getId() const {return this->id;};

        friend std::ostream& operator<<(std::ostream& out, const BaseModel& model);
};

#endif