#ifndef USER_H
#define USER_H

#include "sql/database.h"

class User
{
public:
    User();
    QueryResult static createTable();
    QueryResult static insertRecord(const QString& login, const QString& password);
    QueryResult static getRecordByLogin(const QString& login);
};

#endif // USER_H
