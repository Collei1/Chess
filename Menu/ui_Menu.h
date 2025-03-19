/********************************************************************************
** Form generated from reading UI file 'Menu.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENU_H
#define UI_MENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Menu
{
public:
    QLabel *label_logo;
    QPushButton *pushButton_one;
    QPushButton *pushButton_two;
    QPushButton *pushButton_wait;

    void setupUi(QFrame *Menu)
    {
        if (Menu->objectName().isEmpty())
            Menu->setObjectName("Menu");
        Menu->resize(1150, 850);
        label_logo = new QLabel(Menu);
        label_logo->setObjectName("label_logo");
        label_logo->setGeometry(QRect(170, 110, 461, 331));
        QFont font;
        font.setFamilies({QString::fromUtf8("Segoe Script")});
        font.setPointSize(80);
        font.setItalic(false);
        font.setStyleStrategy(QFont::PreferAntialias);
        label_logo->setFont(font);
        pushButton_one = new QPushButton(Menu);
        pushButton_one->setObjectName("pushButton_one");
        pushButton_one->setGeometry(QRect(900, 200, 121, 41));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221")});
        font1.setPointSize(10);
        pushButton_one->setFont(font1);
        pushButton_one->setStyleSheet(QString::fromUtf8("background-color: rgb(187, 241, 169);"));
        pushButton_two = new QPushButton(Menu);
        pushButton_two->setObjectName("pushButton_two");
        pushButton_two->setGeometry(QRect(900, 310, 121, 41));
        pushButton_two->setFont(font1);
        pushButton_two->setStyleSheet(QString::fromUtf8("background-color: rgb(187, 241, 169);"));
        pushButton_wait = new QPushButton(Menu);
        pushButton_wait->setObjectName("pushButton_wait");
        pushButton_wait->setGeometry(QRect(900, 420, 121, 41));
        pushButton_wait->setFont(font1);
        pushButton_wait->setStyleSheet(QString::fromUtf8("background-color: rgb(187, 241, 169);"));

        retranslateUi(Menu);

        QMetaObject::connectSlotsByName(Menu);
    } // setupUi

    void retranslateUi(QFrame *Menu)
    {
        Menu->setWindowTitle(QCoreApplication::translate("Menu", "a", nullptr));
        label_logo->setText(QCoreApplication::translate("Menu", "Chess", nullptr));
        pushButton_one->setText(QCoreApplication::translate("Menu", "\347\203\255\345\272\247\346\250\241\345\274\217", nullptr));
        pushButton_two->setText(QCoreApplication::translate("Menu", "\345\261\200\345\237\237\347\275\221\346\250\241\345\274\217", nullptr));
        pushButton_wait->setText(QCoreApplication::translate("Menu", "\346\225\254\350\257\267\346\234\237\345\276\205", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Menu: public Ui_Menu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENU_H
