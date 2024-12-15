#include "server.h"

#include <QJsonDocument>
#include <QJsonObject>
#include "sql/database.h"
#include "sql/tables/user.h"
#include "sql/dto/userDto.h"
#include "utils/passwordUtils.h"


Server::Server()
{
    connect(this, &QTcpServer::newConnection, this, &Server::newConnection);
}

void Server::clientDisconnected(QTcpSocket* client)
{
    QString s = client->peerAddress().toString();
    QByteArray message = "[Event] client disconnected: ";
    this->sendMessage(message);
    client->deleteLater();
    clients.removeOne(client);
}

void Server::clientReceived(QTcpSocket* client)
{
    QByteArray jsonData = client->readAll();
    QJsonDocument jsonText = QJsonDocument::fromJson(jsonData);
    QJsonObject json = jsonText.object();
    QJsonObject data = json["data"].toObject();

    QJsonObject answerJson, answerDataJson;
    answerJson["type"] = "ignore";
    answerJson["data"] = answerDataJson;

    if (json["type"] == "auth_user")
    {
        answerJson["type"] = "auth_user_status";
        answerDataJson["status"] = true;
        answerDataJson["login"] = data["login"].toString();
        QueryResult result = User::getRecordByLogin(data["login"].toString());
        result.query.next();
        UserDto user = UserDto(result.query);
        if (user.login.isEmpty())
            answerDataJson["status"] = false;
        else if (!PasswordUtils::cmp_hash(data["password"].toString(), user.password))
            answerDataJson["status"] = false;
        answerJson["data"] = answerDataJson;
        QJsonDocument jsonText(answerJson);
        client->write(jsonText.toJson());
        return;
    } else if (json["type"] == "create_user") {
        answerJson["type"] = "create_user_status";
        answerDataJson["status"] = true;
        answerDataJson["login"] = data["login"].toString();
        QueryResult result = User::getRecordByLogin(data["login"].toString());
        result.query.next();
        UserDto user = UserDto(result.query);
        if (!user.login.isEmpty())
            answerDataJson["status"] = false;
        else
            QueryResult result = User::insertRecord(data["login"].toString(), PasswordUtils::get_hash(data["password"].toString()));
        if (!result.result)
            answerDataJson["status"] = false;
        answerJson["data"] = answerDataJson;
        QJsonDocument jsonText(answerJson);
        client->write(jsonText.toJson());
        return;
    } else if (json["type"] == "new_message")
    {
        answerJson["type"] = "new_message";
        answerDataJson["text"] = data["login"].toString() + ":" + data["text"].toString();
        answerJson["data"] = answerDataJson;
        QJsonDocument jsonText(answerJson);
        QByteArray message = jsonText.toJson();
        this->sendMessage(message);
    }
}

void Server::newConnection()
{
    QTcpSocket *clientSocket = this->nextPendingConnection();
    this->clients.append(clientSocket);

    connect(clientSocket, &QTcpSocket::readyRead,
            this, [this, clientSocket](){this->clientReceived(clientSocket);});
    connect(clientSocket, &QTcpSocket::disconnected,
            this, [this, clientSocket](){this->clientDisconnected(clientSocket);});

    QByteArray message = "[Event] client connected: \n";
    this->sendMessage(message);
}

void Server::sendMessage(QByteArray& message)
{
    for (auto &clientSocket : this->clients)
    {
        clientSocket->write(message);
        clientSocket->flush();
    }
}
