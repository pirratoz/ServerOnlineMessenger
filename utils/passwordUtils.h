#ifndef PASSWORDUTILS_H
#define PASSWORDUTILS_H

#include <QString>

class PasswordUtils
{
public:
    PasswordUtils();
    QString static get_hash(const QString& password);
    bool static cmp_hash(const QString& password, const QString& hash);
};

#endif // PASSWORDUTILS_H
