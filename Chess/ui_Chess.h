/********************************************************************************
** Form generated from reading UI file 'Chess.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHESS_H
#define UI_CHESS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_Chess
{
public:
    QLabel *label_chess;
    QLabel *label_win;

    void setupUi(QFrame *Chess)
    {
        if (Chess->objectName().isEmpty())
            Chess->setObjectName("Chess");
        Chess->resize(900, 850);
        label_chess = new QLabel(Chess);
        label_chess->setObjectName("label_chess");
        label_chess->setEnabled(false);
        label_chess->setGeometry(QRect(770, 20, 81, 31));
        QFont font;
        font.setPointSize(18);
        label_chess->setFont(font);
        label_chess->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));
        label_win = new QLabel(Chess);
        label_win->setObjectName("label_win");
        label_win->setGeometry(QRect(610, 800, 281, 31));
        label_win->setFont(font);
        label_win->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));

        retranslateUi(Chess);

        QMetaObject::connectSlotsByName(Chess);
    } // setupUi

    void retranslateUi(QFrame *Chess)
    {
        Chess->setWindowTitle(QCoreApplication::translate("Chess", "a", nullptr));
        label_chess->setText(QCoreApplication::translate("Chess", "Check!", nullptr));
        label_win->setText(QCoreApplication::translate("Chess", "Win!", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Chess: public Ui_Chess {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHESS_H
