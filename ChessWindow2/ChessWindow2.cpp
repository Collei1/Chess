//
// Created by Collei on 25-3-9.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ChessWindow2.h" resolved

#include "ChessWindow2.h"
#include "ui_ChessWindow2.h"
#include <QString>
#include <QFileDialog>

ChessWindow2::ChessWindow2(QFrame *parent) :
    QFrame(parent), ui(new Ui::ChessWindow2), settings(new QSettings("../msg.ini", QSettings::IniFormat, this)), overlay_surrender(new QWidget(this)) {
    ui->setupUi(this);
    overlay_surrender->setGeometry(120, 100, 640, 640);
    overlay_surrender->setStyleSheet("background-color: rgba(0, 0, 0, 20);");
    overlay_surrender->setAttribute(Qt::WA_TransparentForMouseEvents, false);  // 不允许鼠标事件穿透
    overlay_surrender->hide();
    ui->pushButton_begin->hide();
    ui->pushButton_restart->hide();
    ui->pushButton_surrender->hide();
    ui->pushButton_return_room->hide();
    ui->label_w->hide();
    ui->label_b->hide();
    /*ui->label_avatar_my->hide();
    ui->label_avatar_its->hide();*/
    ui->frame_ipInput->hide();
    ui->frame_msgInput->hide();
    ui->label_surrender_its->hide();
    ui->label_surrender_my->hide();
    ui->label_name_my->hide();
    ui->label_name_its->hide();
    if(!settings->value("username").isNull() && settings->value("username") != "") {
        username = settings->value("username").toString();
        ui->label_name->setText(username);
        ui->label_name_my->setText(username);
    }else {
        settings->setValue("username", "");
        username = "HuTao";
    }

    chess = new Chess(this);
    chess->setGeometry(0,0,900, 850);
    chess->show();
    initSignal();
}

ChessWindow2::~ChessWindow2() {
    delete ui;
}

void ChessWindow2::initSignal() {
    connect(ui->pushButton_create,&QPushButton::clicked,this,createRoom);
    connect(ui->pushButton_enter,&QPushButton::clicked,this,enterRoom);
    connect(ui->pushButton_return_menu, &QPushButton::clicked,this, returnMenu);
    connect(ui->pushButton_begin,&QPushButton::clicked,this,start);
    connect(ui->pushButton_restart,&QPushButton::clicked,this,restart);
    connect(ui->pushButton_surrender, &QPushButton::clicked,this,surrender);
    connect(ui->pushButton_return_room, &QPushButton::clicked,this, returnRoom);

    connect(ui->pushButton_ipInput_close, &QPushButton::clicked,this, [=] {
        ui->frame_ipInput->hide();
        if (overlay_total) {
            overlay_total->hide();
            delete overlay_total;  // 销毁遮罩窗口
            overlay_total = nullptr;
        }
    });
    connect(ui->pushButton_ipOk, &QPushButton::clicked,this, getIp);
    /*connect(labelbutton_avtarInput, &LabelButton::Clicked, this, [=]() {
        // 打开文件对话框，选择图片文件
        QString fileName = QFileDialog::getOpenFileName(nullptr, "Open Image", "", "Images (*.png *.jpg *.bmp)");
        if (!fileName.isEmpty()) {
            QImage image(fileName);
            if (!image.isNull()) {
                // 图片加载成功
                qDebug() << "Image loaded in"<<fileName;
                QString filePath = "../image/avatar/userAvatar.png";
                if (image.save(filePath)) {
                // 保存成功
                    qDebug() << "Image saved successfully to" << filePath;
                } else {
                    // 保存失败
                    qDebug() << "Failed to save image to" << filePath;
                }
                // 显示图片（可选）
                labelbutton_avtarInput->setPixmap(QPixmap::fromImage(image));
                ui->label_avatar->setPixmap(QPixmap::fromImage(image));
                ui->label_avatar_my->setPixmap(QPixmap::fromImage(image));
            } else {
                // 图片加载失败
                qDebug() << "Image loaded error";
            }
        }else {

        }
    });*/
    connect(ui->pushButton_msgInput_close, &QPushButton::clicked,this, [=] {
        ui->frame_msgInput->hide();
        if (overlay_total) {
            overlay_total->hide();
            delete overlay_total;  // 销毁遮罩窗口
            overlay_total = nullptr;
        }
    });
    connect(ui->pushButton_msgInputOk, &QPushButton::clicked,this, changeMsg);
    connect(ui->pushButton_edit, &QPushButton::clicked,this, [=]() {
        ui->frame_msgInput->show();
        ui->frame_msgInput->raise();
        // 创建遮罩窗口
        overlay_total = new QWidget(this);
        overlay_total->setGeometry(0, 0, width(), height());  // 设置遮罩大小与主窗口一致
        overlay_total->setStyleSheet("background-color: rgba(0, 0, 0, 150);");  // 黑色半透明
        overlay_total->setAttribute(Qt::WA_TransparentForMouseEvents, false);  // 不允许鼠标事件穿透
        overlay_total->show();
        overlay_total->stackUnder(ui->frame_msgInput);
        ui->frame_msgInput->setStyleSheet("background-color: rgb(255, 255, 255);");
    });
    //connect(chess, &Chess::sendMoved, this, getMoved);
    //connect(server, &ChessServer::sendReceivedData, chess, &Chess::getReceivedData);
}
void ChessWindow2::changeMsg() {
    ui->frame_msgInput->hide();
    if (overlay_total) {
        overlay_total->hide();
        delete overlay_total;  // 销毁遮罩窗口
        overlay_total = nullptr;
    }
    //处理更改用户数据
    username = ui->lineEdit_msgInput->text();
    settings->setValue("username", username);
    ui->label_name->setText(username);
    ui->label_name_my->setText(username);
}

void ChessWindow2::getMoved(const StepData *stepData) {
    if(isHost) {
        server->sendDataToClient(stepData);
    }else {
        client->sendDataToServer(stepData);
    }
}

void ChessWindow2::createRoom() {
    server = new ChessServer(this);
    isHost = true;
    myColor = 1;//加上选择颜色
    initRoom(myColor);
    connect(server, &ChessServer::getUserData, this, [=](const QJsonObject *receivedData) {
        ui->label_name_its->show();
        ui->label_name_its->setText(receivedData->value("username").toString());
        ui->pushButton_begin->setDisabled(false);
        ui->pushButton_surrender->setDisabled(false);
        server->sendUserData(username);
    });
    connect(chess, &Chess::sendMoved, this, getMoved);
    connect(server, &ChessServer::getStepData, chess, &Chess::onGetData);
    connect(server, &ChessServer::itSurrender, this, [=]() {
        ui->label_surrender_its->show();
        overlay_surrender->show();
        overlay_surrender->raise();
    });
}

void ChessWindow2::initRoom(int color) {
    ui->pushButton_begin->show();
    ui->pushButton_begin->move(ui->pushButton_create->x(), ui->pushButton_create->y());
    ui->pushButton_surrender->show();
    ui->pushButton_surrender->move(ui->pushButton_enter->x(), ui->pushButton_enter->y());
    ui->pushButton_begin->setDisabled(true);
    ui->pushButton_surrender->setDisabled(true);
    ui->pushButton_return_room->show();
    ui->pushButton_return_room->move(ui->pushButton_return_menu->x(), ui->pushButton_return_menu->y());
    ui->label_b->show();
    ui->label_w->show();
    /*ui->label_avatar_my->show();
    ui->label_avatar_its->show();*/
    ui->label_name_my->show();
    //ui->label_name_its->show();
    if(color) {
        ui->label_b->setGeometry(QRect(810, 120, 30, 30));
        ui->label_w->setGeometry(QRect(810, 690, 30, 30));
    }else {
        ui->label_w->setGeometry(QRect(810, 120, 30, 30));
        ui->label_b->setGeometry(QRect(810, 690, 30, 30));
    }
    ui->pushButton_create->hide();
    ui->pushButton_enter->hide();
    ui->pushButton_return_menu->hide();
    //ui->label_avatar->hide();
    ui->label_name->hide();
    ui->pushButton_edit->hide();
}
void ChessWindow2::enterRoom() {
    ui->frame_ipInput->show();
    ui->frame_ipInput->raise();
    // 创建遮罩窗口
    overlay_total = new QWidget(this);
    overlay_total->setGeometry(0, 0, width(), height());  // 设置遮罩大小与主窗口一致
    overlay_total->setStyleSheet("background-color: rgba(0, 0, 0, 150);");  // 黑色半透明
    overlay_total->setAttribute(Qt::WA_TransparentForMouseEvents, false);  // 不允许鼠标事件穿透
    overlay_total->show();
    overlay_total->stackUnder(ui->frame_ipInput);
    ui->frame_ipInput->setStyleSheet("background-color: rgb(255, 255, 255);");
}
void ChessWindow2::getIp() {
    QString ipStr = ui->lineEdit_ipInput->text();
    if(ipStr.isNull()) {//检查ip
       return;
    }
    ui->frame_ipInput->hide();
    if (overlay_total) {
        overlay_total->hide();
        delete overlay_total;  // 销毁遮罩窗口
        overlay_total = nullptr;
    }
    client = new ChessClient(ipStr, this);
    isHost = false;
    myColor = 0;//加上选择颜色
    delete chess;
    chess = new Chess(this, myColor);
    chess->show();
    initRoom(myColor);
    //chess->setChessmen(myColor);
    connect(chess, &Chess::sendMoved, this, getMoved);
    connect(client, &ChessClient::startChess, this,[=](int color) {
        chess->setChessmen(color);
        ui->pushButton_surrender->setDisabled(false);
    });
    connect(client, &ChessClient::restartChess, this, restart);
    connect(client, &ChessClient::getStepData, chess, &Chess::onGetData);
    connect(client, &ChessClient::ready, this, [=]() {
        client->sendUserData(username);
    });
    connect(client, &ChessClient::getUserData, this, [=](const QJsonObject *receivedData) {
        ui->label_name_its->show();
        ui->label_name_its->setText(receivedData->value("username").toString());
        /*QPixmap pixmap;
        pixmap.loadFromData(receivedData->value("avatar").toVariant().toByteArray());
        ui->label_avatar_its->setPixmap(pixmap);*/
        //
    });
    connect(client, &ChessClient::itSurrender, this, [=]() {
        ui->label_surrender_its->show();
        overlay_surrender->show();
        overlay_surrender->raise();
    });
    ui->pushButton_begin->setDisabled(true);
    ui->pushButton_surrender->setDisabled(true);
}

void ChessWindow2::returnMenu() {
    ui->pushButton_begin->setDisabled(false);
    delete chess;
    chess = new Chess(this);
    chess->show();
    sendReturnMain();
}
void ChessWindow2::start() {
    chess->setChessmen(myColor);
    ui->pushButton_begin->setDisabled(true);
    server->startChess();
}
void ChessWindow2::restart() {
    delete chess;
    chess = new Chess(this, myColor);
    chess->show();
    chess->setChessmen(myColor);
    connect(chess, &Chess::sendMoved, this, getMoved);
    overlay_surrender->hide();
    ui->label_surrender_my->hide();
    ui->label_surrender_its->hide();
    if(isHost) {
        server->restartChess();
        connect(server, &ChessServer::getStepData, chess, &Chess::onGetData);
        ui->pushButton_restart->hide();
        ui->pushButton_begin->show();
        ui->pushButton_begin->setDisabled(true);
    }else {
        connect(client, &ChessClient::getStepData, chess, &Chess::onGetData);
    }
}

void ChessWindow2::surrender() {
    ui->label_surrender_my->show();
    overlay_surrender->show();
    overlay_surrender->raise();
    //overlay_surrender->stackUnder(ui->frame_ipInput);
    if(isHost) {
        ui->pushButton_begin->hide();
        ui->pushButton_restart->move(ui->pushButton_create->x(), ui->pushButton_create->y());
        ui->pushButton_restart->show();
        server->surrender();
    }else {
        client->surrender();
    }
}
void ChessWindow2::returnRoom() {
    delete server;
    delete client;
    delete chess;
    chess = new Chess(this);
    chess->show();
    ui->pushButton_begin->hide();
    ui->pushButton_create->show();
    ui->pushButton_surrender->hide();
    ui->pushButton_enter->show();
    ui->pushButton_return_room->hide();
    ui->pushButton_return_menu->show();
    ui->label_w->hide();
    ui->label_b->hide();
    ui->label_name->show();
    ui->pushButton_edit->show();
    ui->label_name_my->hide();
    ui->label_name_its->hide();
    ui->label_surrender_my->hide();
    ui->label_surrender_its->hide();
    ui->pushButton_restart->hide();
    overlay_surrender->hide();
}

