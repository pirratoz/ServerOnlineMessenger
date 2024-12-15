#include "logDto.h"
#include <QVariant>

LogDto::LogDto(const qint32 id, const qint32 user_id, const QString& date, const QString& ip, const QString& port, const QString& action)
{
    this->id = id;
    this->user_id = user_id;
    this->date = date;
    this->ip = ip;
    this->port = port;
    this->action = action;
}

LogDto::LogDto(const QSqlQuery& query) :
    LogDto(
       query.value("id").toInt(),
       query.value("user_id").toInt(),
       query.value("date").toString(),
       query.value("ip").toString(),
       query.value("port").toString(),
       query.value("action").toString()
    )
{

}
