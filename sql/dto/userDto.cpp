#include "userDto.h"
#include <QVariant>

UserDto::UserDto(const qint32 id, const QString& login, const QString& password)
{
    this->id = id;
    this->login = login;
    this->password = password;
}

UserDto::UserDto(const QSqlQuery& query) :
    UserDto(
       query.value("id").toInt(),
       query.value("login").toString(),
       query.value("password").toString()
    )
{

}
