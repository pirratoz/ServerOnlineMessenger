#ifndef LOGDTO_H
#define LOGDTO_H

#include <QString>
#include <QSqlQuery>

class LogDto
{
public:
    LogDto(const qint32 id, const qint32 user_id, const QString& date, const QString& ip, const QString& port, const QString& action);
    LogDto(const QSqlQuery& query);
    qint32 id;
    qint32 user_id;
    QString date;
    QString ip;
    QString port;
    QString action;
};

#endif // LOGDTO_H
