#ifndef LOG_H
#define LOG_H

#include <QString>
#include "sql/database.h"

class Log
{
public:
    Log();
    QueryResult static createTable();
    QueryResult static insertRecord(qint32 user_id, const QString& date, const QString& ip, const QString& port, const QString& action);
};

#endif // LOG_H
