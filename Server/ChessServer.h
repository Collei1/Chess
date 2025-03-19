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
        // ��������IP��ַ��ָ���˿�
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
        // ���пͻ�������ʱ
        clientSocket = nextPendingConnection();
        qDebug() << "New client connected:" << clientSocket->peerAddress().toString();

        // �����źŲۣ�����ͻ�������
        connect(clientSocket, &QTcpSocket::readyRead, this, &ChessServer::onReadyRead);
        connect(clientSocket, &QTcpSocket::disconnected, this, &ChessServer::onClientDisconnected);

    }

    void onReadyRead() {
        // ��ȡ�ͻ��˷��͵�����
        QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
        QByteArray data = clientSocket->readAll();
        qDebug() << "Received data from client:" << data;
        // �� QByteArray ת��Ϊ QJsonDocument
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
        // ����Ƿ�����ɹ�
        if (jsonDoc.isNull()) {
            qDebug() << "Failed to parse JSON data!";
            return;
        }
        // �� QJsonDocument ת��Ϊ QJsonObject
        const QJsonObject receivedJson = jsonDoc.object();
        const QJsonObject receivedData = receivedJson["data"].toObject();
        switch (receivedJson["type"].toInt()) {
            case STEPDATA: {
                emit getStepData(&receivedData);
                break;
            }
            case USERDATA: {
                emit getUserData(&receivedData);//***����
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
        // ���ͻ��˶Ͽ�����ʱ
        QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
        qDebug() << "Client disconnected:" << clientSocket->peerAddress().toString();

        // ���б����Ƴ��ͻ���
        clientSocket->deleteLater();
    }
private:
    QTcpSocket *clientSocket{};

};


#endif //CHESSSERVER_H
