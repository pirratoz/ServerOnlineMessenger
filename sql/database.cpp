#include "database.h"
#include <QSqlDatabase>
#include <QSqlQuery>

Database::Database()
{

}

QSqlDatabase Database::getDatabaseByName(const QString name)
{
    if (!QSqlDatabase::contains(name))
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", name);
        db.setDatabaseName(name + ".db");
    }
    return QSqlDatabase::database("main");
}

QueryResult::QueryResult(QSqlQuery query, bool result)
{
    this->result = result;
    this->query = query;
}
