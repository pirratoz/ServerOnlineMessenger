#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>

class Server : public QTcpServer
{
public:
    Server();

private:
    QVector<QTcpSocket*> clients;

private:
    void clientDisconnected(QTcpSocket* client);
    void clientReceived(QTcpSocket* client);
    void newConnection();
    void sendMessage(QByteArray& message);
};

#endif // SERVER_H
