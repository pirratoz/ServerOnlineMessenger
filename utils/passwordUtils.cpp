#include "passwordUtils.h"
#include <QCryptographicHash>

PasswordUtils::PasswordUtils()
{

}

QString PasswordUtils::get_hash(const QString& password)
{
    QByteArray hashedPassword = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
    return hashedPassword.toHex();
}

bool PasswordUtils::cmp_hash(const QString& password, const QString& hash)
{
    return hash == PasswordUtils::get_hash(password);
}
