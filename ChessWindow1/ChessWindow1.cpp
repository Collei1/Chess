//
// Created by Collei on 25-3-8.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ChessWindow.h" resolved

#include "ChessWindow1.h"
#include "ui_ChessWindow1.h"


ChessWindow1::ChessWindow1(QFrame *parent) :
    QFrame(parent), ui(new Ui::ChessWindow1) {
    ui->setupUi(this);
    chess = new Chess(this);
    chess->setGeometry(0,0,900, 850);
    chess->show();
    initSignal();
}

ChessWindow1::~ChessWindow1() {
    delete ui;
}

void ChessWindow1::initSignal() {
    connect(ui->pushButton_begin,&QPushButton::clicked,this,start);
    connect(ui->pushButton_restart, &QPushButton::clicked,this,restart);
    connect(ui->pushButton_return, &QPushButton::clicked,this, returnMain);
}

void ChessWindow1::start() {
    chess->setChessmen(-1);
    ui->pushButton_begin->setDisabled(true);
}

void ChessWindow1::restart() {
    delete chess;
    chess = new Chess(this);
    chess->show();
    chess->setChessmen(-1);
}

void ChessWindow1::returnMain() {
    sendReturnMain();
    ui->pushButton_begin->setDisabled(false);
    delete chess;
    chess = new Chess(this);
    chess->show();
}


