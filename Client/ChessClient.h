//
// Created by Collei on 25-3-7.
//

#ifndef CHESSCLIENT_H
#define CHESSCLIENT_H

#include "../User/User.h"
#include <QTcpSocket>
#include <QDebug>
#include <QJsonObject>
#include<QJsonDocument>

class ChessClient : public QObject {
    Q_OBJECT
public:
    explicit ChessClient(const QString &serverAddress, QObject *parent = nullptr) : QObject(parent) {
        socket = new QTcpSocket(this);

        // 连接信号槽
        connect(socket, &QTcpSocket::connected, this, &ChessClient::onConnected);
        connect(socket, &QTcpSocket::readyRead, this, &ChessClient::onReadyRead);
        connect(socket, &QTcpSocket::disconnected, this, &ChessClient::onDisconnected);

        // 连接到主机的IP地址和端口
        socket->connectToHost(serverAddress, 8080);
    }

    void sendDataToServer(const StepData *stepData) {
        QJsonObject stepJson = stepData->dataToJson();
        QJsonObject jsonObject;
        jsonObject["type"] = STEPDATA;
        jsonObject["data"] = stepJson;
        QJsonDocument jsonDoc(jsonObject);
        QByteArray data = jsonDoc.toJson();
        if (socket->state() == QTcpSocket::ConnectedState) {
            socket->write(data);
            qDebug() <<"Send to Server Data";
        }else {
            qDebug() << "Fail to send data to server";
        }
    }
    void sendUserData(const QString &username) {
        QJsonObject userJson;
        userJson["username"] = username;
        QJsonObject jsonObject;
        jsonObject["type"] = USERDATA;
        jsonObject["data"] = userJson;
        QJsonDocument jsonDoc(jsonObject);
        QByteArray data = jsonDoc.toJson();
        if (socket->state() == QTcpSocket::ConnectedState) {
            socket->write(data);
            qDebug() <<"Send to Server User Data";
        }
    }
    void surrender() {
        QJsonObject jsonObject;
        jsonObject["type"] = SURRENDER;
        QJsonDocument jsonDoc(jsonObject);
        QByteArray data = jsonDoc.toJson();
        if (socket->state() == QTcpSocket::ConnectedState) {
            socket->write(data);
        }
    }
    signals:
    void getStepData(const QJsonObject *receivedData);
    void startChess(int color);
    void restartChess();
    void ready();
    void getUserData(const QJsonObject *receivedData);
    void itSurrender();

private slots:
    void onConnected() {
        qDebug() << "Connected to server";
        emit ready();
    }

    void onReadyRead() {
        // 读取服务器发送的数据
        QByteArray data = socket->readAll();
        qDebug() << "Received data from server:" << data;
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
            case START: {
                emit startChess(0);//***更改
                break;
            }
            case RESTART: {
                emit restartChess();//***更改
                break;
            }
            case USERDATA: {
                emit getUserData(&receivedData);
                break;
            }
            case SURRENDER: {
                emit itSurrender();
                break;
            }
            default:break;
        }

    }

    void onDisconnected() {
        qDebug() << "Disconnected from server";
    }

private:
    QTcpSocket *socket;
};

#endif //CHESSCLIENT_H
