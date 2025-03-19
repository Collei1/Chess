//
// Created by Collei on 25-3-7.
//

#ifndef CHESSSERVER_H
#define CHESSSERVER_H

#include "../User/user.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QJsonObject>
#include<QJsonDocument>



class ChessServer : public QTcpServer {
    Q_OBJECT
public:
    explicit ChessServer(QObject *parent = nullptr) : QTcpServer(parent) {
        // 监听所有IP地址的指定端口
        if (listen(QHostAddress::Any, 8080)) {
            qDebug() << "Server is running on port 8080";
        } else {
            qDebug() << "Server failed to start:" << errorString();
        }
        connect(this, &QTcpServer::newConnection, this, &ChessServer::onNewConnection);
    }
    void sendDataToClient(const StepData *stepData) {
        QJsonObject stepJson= stepData->dataToJson();
        QJsonObject jsonObject;
        jsonObject["type"] = STEPDATA;
        jsonObject["data"] = stepJson;
        QJsonDocument jsonDoc(jsonObject);
        QByteArray data = jsonDoc.toJson();
        if (clientSocket && clientSocket->state() == QTcpSocket::ConnectedState) {
            clientSocket->write(data);
            qDebug() <<"Send to Client Data";
        }else {
            qDebug() << "Fail to send data to client";
        }
    }

    void startChess() {
        QJsonObject jsonObject;
        jsonObject["type"] = START;
        QJsonDocument jsonDoc(jsonObject);
        QByteArray data = jsonDoc.toJson();
        if (clientSocket && clientSocket->state() == QTcpSocket::ConnectedState) {
            clientSocket->write(data);
        }
    }
    void restartChess() {
        QJsonObject jsonObject;
        jsonObject["type"] = RESTART;
        QJsonDocument jsonDoc(jsonObject);
        QByteArray data = jsonDoc.toJson();
        if (clientSocket && clientSocket->state() == QTcpSocket::ConnectedState) {
            clientSocket->write(data);
        }
    }
    void sendUserData(const QString& username) {
        QJsonObject userJson;
        userJson["username"] = username;
        QJsonObject jsonObject;
        jsonObject["type"] = USERDATA;
        jsonObject["data"] = userJson;
        QJsonDocument jsonDoc(jsonObject);
        QByteArray data = jsonDoc.toJson();
        if (clientSocket->state() == QTcpSocket::ConnectedState) {
            clientSocket->write(data);
            qDebug() <<"Send to Client User Data";
        }
    }
    void surrender() {
        QJsonObject jsonObject;
        jsonObject["type"] = SURRENDER;
        QJsonDocument jsonDoc(jsonObject);
        QByteArray data = jsonDoc.toJson();
        if (clientSocket && clientSocket->state() == QTcpSocket::ConnectedState) {
            clientSocket->write(data);
        }
    }
signals:
    void getStepData(const QJsonObject *receivedData);
    void getUserData(const QJsonObject *receivedData);
    void itSurrender();
public slots:
    void onNewConnection() {
        // 当有客户端连接时
        clientSocket = nextPendingConnection();
        qDebug() << "New client connected:" << clientSocket->peerAddress().toString();

        // 连接信号槽，处理客户端数据
        connect(clientSocket, &QTcpSocket::readyRead, this, &ChessServer::onReadyRead);
        connect(clientSocket, &QTcpSocket::disconnected, this, &ChessServer::onClientDisconnected);

    }

    void onReadyRead() {
        // 读取客户端发送的数据
        QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
        QByteArray data = clientSocket->readAll();
        qDebug() << "Received data from client:" << data;
        // 将 QByteArray 转换为 QJsonDocument
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
        // 检查是否解析成功
        if (jsonDoc.isNull()) {
            qDebug() << "Failed to parse JSON data!";
            return;
        }
        // 将 QJsonDocument 转换为 QJsonObject
        const QJsonObject receivedJson = jsonDoc.object();
        const QJsonObject receivedData = receivedJson["data"].toObject();
        switch (receivedJson["type"].toInt()) {
            case STEPDATA: {
                emit getStepData(&receivedData);
                break;
            }
            case USERDATA: {
                emit getUserData(&receivedData);//***更改
                break;
            }
            case SURRENDER: {
                emit itSurrender();
                break;
            }
            default:break;
        }
    }

    void onClientDisconnected() {
        // 当客户端断开连接时
        QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
        qDebug() << "Client disconnected:" << clientSocket->peerAddress().toString();

        // 从列表中移除客户端
        clientSocket->deleteLater();
    }
private:
    QTcpSocket *clientSocket{};

};


#endif //CHESSSERVER_H
