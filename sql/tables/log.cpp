#include "log.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "sql/database.h"


Log::Log()
{

}

QueryResult Log::createTable()
{
    // date = yyyy-MM-dd HH:mm:ss
    QSqlQuery query(Database::getDatabaseByName(mainDataBase));
    QString textQuery =
            "CREATE TABLE IF NOT EXISTS logs("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "user_id INTEGER NOT NULL,"
            "date TEXT NOT NULL,"
            "ip TEXT,"
            "port TEXT,"
            "action TEXT,"
            "FOREIGN KEY(user_id) REFERENCES users(id)"
            ");";
    query.prepare(textQuery);
    return QueryResult(query, query.exec());
}

QueryResult Log::insertRecord(qint32 user_id, const QString& date, const QString& ip, const QString& port, const QString& action)
{
    QSqlQuery query(Database::getDatabaseByName(mainDataBase));
    QString textQuery =
            "INSERT INTO logs "
            "(user_id, date, ip, port, action)"
            "VALUES"
            "(:user_id, :date, :ip, :port, :action)";
    query.prepare(textQuery);
    query.bindValue(":user_id", user_id);
    query.bindValue(":date", date);
    query.bindValue(":ip", ip);
    query.bindValue(":port", port);
    query.bindValue(":action", action);
    return QueryResult(query, query.exec());
}
