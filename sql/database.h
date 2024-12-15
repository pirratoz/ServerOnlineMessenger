#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>


const QString mainDataBase = "main";


class Database
{
public:
    Database();
    QSqlDatabase static getDatabaseByName(const QString name);
};


class QueryResult
{
public:
    QueryResult(QSqlQuery query, bool result);
    bool result;
    QSqlQuery query;
};

#endif // DATABASE_H
