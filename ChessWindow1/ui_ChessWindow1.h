/********************************************************************************
** Form generated from reading UI file 'ChessWindow1.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHESSWINDOW1_H
#define UI_CHESSWINDOW1_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ChessWindow1
{
public:
    QPushButton *pushButton_begin;
    QPushButton *pushButton_restart;
    QPushButton *pushButton_return;

    void setupUi(QFrame *ChessWindow1)
    {
        if (ChessWindow1->objectName().isEmpty())
            ChessWindow1->setObjectName("ChessWindow1");
        ChessWindow1->resize(1150, 850);
        pushButton_begin = new QPushButton(ChessWindow1);
        pushButton_begin->setObjectName("pushButton_begin");
        pushButton_begin->setGeometry(QRect(970, 180, 91, 41));
        QFont font;
        font.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221")});
        pushButton_begin->setFont(font);
        pushButton_begin->setStyleSheet(QString::fromUtf8("background-color: rgb(187, 241, 169);"));
        pushButton_restart = new QPushButton(ChessWindow1);
        pushButton_restart->setObjectName("pushButton_restart");
        pushButton_restart->setGeometry(QRect(970, 280, 91, 41));
        pushButton_restart->setFont(font);
        pushButton_restart->setStyleSheet(QString::fromUtf8("background-color: rgb(187, 241, 169);"));
        pushButton_return = new QPushButton(ChessWindow1);
        pushButton_return->setObjectName("pushButton_return");
        pushButton_return->setGeometry(QRect(970, 380, 91, 41));
        pushButton_return->setFont(font);
        pushButton_return->setStyleSheet(QString::fromUtf8("background-color: rgb(187, 241, 169);"));

        retranslateUi(ChessWindow1);

        QMetaObject::connectSlotsByName(ChessWindow1);
    } // setupUi

    void retranslateUi(QFrame *ChessWindow1)
    {
        ChessWindow1->setWindowTitle(QCoreApplication::translate("ChessWindow1", "a", nullptr));
        pushButton_begin->setText(QCoreApplication::translate("ChessWindow1", "\345\274\200\345\247\213\346\270\270\346\210\217", nullptr));
        pushButton_restart->setText(QCoreApplication::translate("ChessWindow1", "\351\207\215\346\226\260\345\274\200\345\247\213", nullptr));
        pushButton_return->setText(QCoreApplication::translate("ChessWindow1", "\350\277\224\345\233\236\344\270\273\347\225\214\351\235\242", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChessWindow1: public Ui_ChessWindow1 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHESSWINDOW1_H
