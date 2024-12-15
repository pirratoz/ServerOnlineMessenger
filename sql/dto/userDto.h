#ifndef USERDTO_H
#define USERDTO_H

#include <QString>
#include <QSqlQuery>

class UserDto
{
public:
    UserDto(const qint32 id, const QString& login, const QString& password);
    UserDto(const QSqlQuery& query);
    qint32 id;
    QString login;
    QString password;
};

#endif // USERDTO_H
