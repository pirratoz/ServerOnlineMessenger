#include <QCoreApplication>

#include "server/server.h"

int main(int argc, char *argv[])
{
    QCoreApplication application(argc, argv);
    Server server;
    server.listen(QHostAddress::Any, 8000);
    return application.exec();
}
