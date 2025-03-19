//
// Created by Collei on 25-3-3.
//
#include"Chessman.h"
#include<QDebug>
#include<QImage>

Chessman::Chessman(QWidget* parent, int color, int type) : LabelButton(parent), type(type), color(color) {
    this->raise();
    std::string str_image;
    switch (type){
        case 0:
            str_image = "pawn"; break;
        case 1:
            str_image = "rook"; break;
        case 2:
            str_image = "knight"; break;
        case 3:
            str_image = "bishop"; break;
        case 4:
            str_image = "queen"; break;
        case 5:
            str_image = "king"; break;
        default:
            break;
    }
    if (color == 0) {
        str_image = "../image/"+ str_image;
        str_image += "_b.png";
    }
    else if (color == 1) {
        str_image = "../image/" + str_image;
        str_image += "_w.png";
    }
    //str_image = "D:/CLion Workshop/Chess/image/bishop_b.png";
    this->setPixmap(QPixmap::fromImage(convertImageWhiteColorAlpha(QImage(QString::fromUtf8(str_image)))));
    this->setScaledContents(true);
    this->show();
    //QObject::connect(this, &Chessman::Clicked, this, &Chessman::setBorder);
}

void Chessman::promote(int type) {
    this->type = type;
    std::string str_image;
    switch (type){
        case 1:
            str_image = "rook"; break;
        case 2:
            str_image = "knight"; break;
        case 3:
            str_image = "bishop"; break;
        case 4:
            str_image = "queen"; break;
        default:
            break;
    }
    if (color == 0) {
        str_image = "../image/"+ str_image;
        str_image += "_b.png";
    }
    else if (color == 1) {
        str_image = "../image/" + str_image;
        str_image += "_w.png";
    }
    this->setPixmap(QPixmap::fromImage(convertImageWhiteColorAlpha(QImage(QString::fromUtf8(str_image)))));
    this->setScaledContents(true);
    this->show();
}