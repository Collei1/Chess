//
// Created by Collei on 25-3-11.
//

#ifndef USER_H
#define USER_H
#include <QImage>
#include <QJsonObject>
#include <QString>
#include <utility>
#include<QBuffer>
#include<QJsonDocument>

#define STEPDATA 0
#define START 1
#define RESTART 2
#define RETURNROOM 3
#define READY 4
#define USERDATA 5
#define SURRENDER 6

/*
struct User {
    User(QString username, QImage avatar): username(std::move(username)), avatar(std::move(avatar)){}
    [[nodiscard]] QJsonObject dataToJson() const {
        QJsonObject jsonObj;
        jsonObj["username"] = username;
        //jsonObj["avatar"] = avatar.to;
        /*QByteArray byteArray;
        QBuffer buffer(&byteArray);
        buffer.open(QIODevice::WriteOnly);
        avatar.save(&buffer, "PNG"); // 保存为 PNG 格式
        jsonObj["avatar"] = QJsonValue::fromVariant(byteArray.toBase64());//*********there#1#
        return jsonObj;
    }
    QString username;
    QImage avatar;
};
*/

struct StepData {
    StepData(int myNum,  int oldLoc, int newLoc, int eatedNum, bool isPromotion, int promotedType, bool isCastling):
    myNum(myNum), oldLoc(oldLoc),newLoc(newLoc),eatedNum(eatedNum),isPromotion(isPromotion),promotedType(promotedType),isCastling(isCastling){}
    [[nodiscard]] QJsonObject dataToJson() const {
        QJsonObject jsonObj;
        jsonObj["myNum"] = myNum;
        jsonObj["oldLoc"] = oldLoc;
        jsonObj["newLoc"] = newLoc;
        jsonObj["eatedNum"] = eatedNum;
        jsonObj["isPromotion"] = isPromotion;
        jsonObj["promotedType"] = promotedType;
        jsonObj["isCastling"] = isCastling;
        return jsonObj;
    }
    int myNum;
    int oldLoc;
    int newLoc;
    int eatedNum;
    bool isPromotion;
    int promotedType;
    bool isCastling;
};

#endif //USER_H
