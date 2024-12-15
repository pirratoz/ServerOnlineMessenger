#include "user.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "sql/database.h"

User::User()
{

}


QueryResult User::createTable()
{
    QSqlQuery query(Database::getDatabaseByName(mainDataBase));
    QString textQuery =
            "CREATE TABLE IF NOT EXISTS users("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "login TEXT NOT NULL,"
            "password TEXT NOT NULL,"
            "UNIQUE(login)"
            ");";
    query.prepare(textQuery);
    return QueryResult(query, query.exec());
}

QueryResult User::insertRecord(const QString& login, const QString& password)
{
    QSqlQuery query(Database::getDatabaseByName(mainDataBase));
    QString textQuery =
            "INSERT INTO users"
            "(login, password)"
            "VALUES"
            "(:login, :password);";
    query.prepare(textQuery);
    query.bindValue(":login", login);
    query.bindValue(":password", password);
    return QueryResult(query, query.exec());
}

QueryResult User::getRecordByLogin(const QString &login)
{
    QSqlQuery query(Database::getDatabaseByName(mainDataBase));
    QString textQuery =
            "SELECT * FROM users "
            "WHERE login = :login;";
    query.prepare(textQuery);
    query.bindValue(":login", login);
    return QueryResult(query, query.exec());
}
