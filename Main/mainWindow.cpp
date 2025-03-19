//
// Created by Collei on 25-3-6.
//

// You may need to build the project (run Qt uic code generator) to get "ui_mainWindow.h" resolved

#include "mainWindow.h"
#include "ui_mainWindow.h"
#include "../ChessWindow1/ChessWindow1.h"
#include "../Menu/ui_Menu.h"
#include <QGraphicsDropShadowEffect>
#include <QColor>
#include<QMovie>

mainWindow::mainWindow(QWidget *parent) :
    QWidget(parent), ui(new Ui::mainWindow) {
    ui->setupUi(this);
    menu = new Menu(ui->frame_main);
    chess1 = new ChessWindow1(ui->frame_main);
    chess2 = new ChessWindow2(ui->frame_main);
    menu->show();
    chess1->hide();
    chess2->hide();

    //设置具体阴影
    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setOffset(0, 0);
    //阴影颜色
    shadow_effect->setColor(QColor(150, 150, 150, 150));
    //阴影半径
    shadow_effect->setBlurRadius(30);
    ui->frame_total->setGraphicsEffect(shadow_effect);

    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags( Qt::FramelessWindowHint);
    initSignal();
}

mainWindow::~mainWindow() {
    delete ui;
}

void mainWindow::initSignal() {
    connect(ui->pushButton_close, &QPushButton::clicked, this, close);
    connect(ui->pushButton_min, &QPushButton::clicked, this, showMinimized);
    connect(menu->ui->pushButton_one, &QPushButton::clicked, this, showChess1);
    connect(menu->ui->pushButton_two, &QPushButton::clicked, this, showChess2);
    connect(chess1, &ChessWindow1::sendReturnMain, this, returnMain);
    connect(chess2, &ChessWindow2::sendReturnMain, this, returnMain);
}

void mainWindow::showChess1() {
    menu->hide();
    chess2->hide();
    chess1->show();
}

void mainWindow::showChess2() {
    menu->hide();
    chess1->hide();
    chess2->show();
}


void mainWindow::returnMain() {
    chess1->hide();
    chess2->hide();
    menu->show();
}


// ??д???????????????????
void mainWindow::mousePressEvent( QMouseEvent *event){
    // ?ж??????????? frame_header ????
    if (ui->frame_header->geometry().contains(event->pos()) && event->button() == Qt::LeftButton) {
        isDragging = true;
        dragStartPosition = event->globalPosition().toPoint() - this->frameGeometry().topLeft();
        event->accept();
    }
}

void mainWindow::mouseMoveEvent(QMouseEvent *event){
    // ???????????????????????????
    if (isDragging && (event->buttons() & Qt::LeftButton)) {
        move(event->globalPosition().toPoint() - dragStartPosition);
        event->accept();
    }
}

void mainWindow::mouseReleaseEvent(QMouseEvent *event){
    // ??????????????
    if (event->button() == Qt::LeftButton) {
        isDragging = false;
    }
}
