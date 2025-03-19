/********************************************************************************
** Form generated from reading UI file 'ChessWindow2.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHESSWINDOW2_H
#define UI_CHESSWINDOW2_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ChessWindow2
{
public:
    QPushButton *pushButton_return_room;
    QPushButton *pushButton_begin;
    QPushButton *pushButton_surrender;
    QLabel *label_w;
    QLabel *label_b;
    QPushButton *pushButton_create;
    QPushButton *pushButton_enter;
    QPushButton *pushButton_return_menu;
    QLabel *label_name;
    QFrame *frame_ipInput;
    QPushButton *pushButton_ipInput_close;
    QLineEdit *lineEdit_ipInput;
    QPushButton *pushButton_ipOk;
    QLabel *label_ipInput;
    QPushButton *pushButton_edit;
    QLabel *label_surrender_its;
    QLabel *label_surrender_my;
    QLabel *label_name_its;
    QLabel *label_name_my;
    QPushButton *pushButton_restart;
    QFrame *frame_msgInput;
    QPushButton *pushButton_msgInput_close;
    QLineEdit *lineEdit_msgInput;
    QPushButton *pushButton_msgInputOk;
    QLabel *label_nameInput;

    void setupUi(QFrame *ChessWindow2)
    {
        if (ChessWindow2->objectName().isEmpty())
            ChessWindow2->setObjectName("ChessWindow2");
        ChessWindow2->resize(1150, 850);
        ChessWindow2->setStyleSheet(QString::fromUtf8(""));
        pushButton_return_room = new QPushButton(ChessWindow2);
        pushButton_return_room->setObjectName("pushButton_return_room");
        pushButton_return_room->setGeometry(QRect(1010, 430, 91, 41));
        QFont font;
        font.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221")});
        pushButton_return_room->setFont(font);
        pushButton_return_room->setStyleSheet(QString::fromUtf8("background-color: rgb(187, 241, 169);"));
        pushButton_begin = new QPushButton(ChessWindow2);
        pushButton_begin->setObjectName("pushButton_begin");
        pushButton_begin->setGeometry(QRect(1010, 250, 91, 41));
        pushButton_begin->setFont(font);
        pushButton_begin->setStyleSheet(QString::fromUtf8("background-color: rgb(187, 241, 169);"));
        pushButton_surrender = new QPushButton(ChessWindow2);
        pushButton_surrender->setObjectName("pushButton_surrender");
        pushButton_surrender->setGeometry(QRect(1010, 340, 91, 41));
        pushButton_surrender->setFont(font);
        pushButton_surrender->setStyleSheet(QString::fromUtf8("background-color: rgb(187, 241, 169);"));
        label_w = new QLabel(ChessWindow2);
        label_w->setObjectName("label_w");
        label_w->setGeometry(QRect(810, 690, 31, 31));
        label_w->setStyleSheet(QString::fromUtf8("border-radius: 15px;\n"
"border: 1px solid gray;\n"
"background-color: rgb(255, 255, 255);"));
        label_b = new QLabel(ChessWindow2);
        label_b->setObjectName("label_b");
        label_b->setGeometry(QRect(810, 120, 30, 30));
        label_b->setStyleSheet(QString::fromUtf8("border-radius: 15px;\n"
"border: 1px solid gray;\n"
"background-color: rgb(0, 0, 0);"));
        pushButton_create = new QPushButton(ChessWindow2);
        pushButton_create->setObjectName("pushButton_create");
        pushButton_create->setGeometry(QRect(930, 280, 91, 41));
        pushButton_create->setFont(font);
        pushButton_create->setStyleSheet(QString::fromUtf8("background-color: rgb(187, 241, 169);"));
        pushButton_enter = new QPushButton(ChessWindow2);
        pushButton_enter->setObjectName("pushButton_enter");
        pushButton_enter->setGeometry(QRect(930, 370, 91, 41));
        pushButton_enter->setFont(font);
        pushButton_enter->setStyleSheet(QString::fromUtf8("background-color: rgb(187, 241, 169);"));
        pushButton_return_menu = new QPushButton(ChessWindow2);
        pushButton_return_menu->setObjectName("pushButton_return_menu");
        pushButton_return_menu->setGeometry(QRect(930, 460, 91, 41));
        pushButton_return_menu->setFont(font);
        pushButton_return_menu->setStyleSheet(QString::fromUtf8("background-color: rgb(187, 241, 169);"));
        label_name = new QLabel(ChessWindow2);
        label_name->setObjectName("label_name");
        label_name->setGeometry(QRect(950, 150, 71, 21));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221")});
        font1.setPointSize(11);
        label_name->setFont(font1);
        frame_ipInput = new QFrame(ChessWindow2);
        frame_ipInput->setObjectName("frame_ipInput");
        frame_ipInput->setGeometry(QRect(420, 360, 361, 81));
        frame_ipInput->setStyleSheet(QString::fromUtf8("QPushButton:hover{\n"
"	background-color: rgb(234, 234, 234);\n"
"}"));
        frame_ipInput->setFrameShape(QFrame::Shape::StyledPanel);
        frame_ipInput->setFrameShadow(QFrame::Shadow::Raised);
        pushButton_ipInput_close = new QPushButton(frame_ipInput);
        pushButton_ipInput_close->setObjectName("pushButton_ipInput_close");
        pushButton_ipInput_close->setGeometry(QRect(3, 3, 30, 30));
        QFont font2;
        font2.setBold(false);
        pushButton_ipInput_close->setFont(font2);
        pushButton_ipInput_close->setStyleSheet(QString::fromUtf8("QPushButton{border-radius: 15px;}\n"
"QPushButton:hover{\n"
"	background-color: rgb(234, 234, 234);\n"
"}"));
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::ApplicationExit));
        pushButton_ipInput_close->setIcon(icon);
        pushButton_ipInput_close->setIconSize(QSize(12, 12));
        lineEdit_ipInput = new QLineEdit(frame_ipInput);
        lineEdit_ipInput->setObjectName("lineEdit_ipInput");
        lineEdit_ipInput->setGeometry(QRect(40, 40, 251, 38));
        lineEdit_ipInput->setStyleSheet(QString::fromUtf8("padding: 5px;\n"
"border-top: 2px solid qlineargradient(y0:0,y1:1,stop: 0 #ececef, stop: 1 white);\n"
"border-left: 1px solid qlineargradient(x0:0, x1:1,stop: 0 #ececef, stop: 1 white);\n"
"border-bottom: 4px solid qlineargradient(y0:0,y1:1,stop: 0 white, stop: 1 #ececef);\n"
"border-right: 1px solid qlineargradient(x0:0, x1:1,stop: 0 white, stop: 1 #ececef);"));
        pushButton_ipOk = new QPushButton(frame_ipInput);
        pushButton_ipOk->setObjectName("pushButton_ipOk");
        pushButton_ipOk->setGeometry(QRect(300, 40, 51, 36));
        pushButton_ipOk->setFont(font1);
        pushButton_ipOk->setStyleSheet(QString::fromUtf8("background-color: rgb(187, 241, 169);"));
        label_ipInput = new QLabel(frame_ipInput);
        label_ipInput->setObjectName("label_ipInput");
        label_ipInput->setGeometry(QRect(10, 48, 21, 21));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221")});
        font3.setPointSize(12);
        label_ipInput->setFont(font3);
        pushButton_edit = new QPushButton(ChessWindow2);
        pushButton_edit->setObjectName("pushButton_edit");
        pushButton_edit->setGeometry(QRect(1020, 140, 71, 31));
        pushButton_edit->setFont(font);
        pushButton_edit->setStyleSheet(QString::fromUtf8("background-color: rgb(187, 241, 169);"));
        label_surrender_its = new QLabel(ChessWindow2);
        label_surrender_its->setObjectName("label_surrender_its");
        label_surrender_its->setGeometry(QRect(910, 90, 81, 31));
        label_surrender_its->setFont(font3);
        label_surrender_my = new QLabel(ChessWindow2);
        label_surrender_my->setObjectName("label_surrender_my");
        label_surrender_my->setGeometry(QRect(920, 660, 81, 31));
        label_surrender_my->setFont(font3);
        label_name_its = new QLabel(ChessWindow2);
        label_name_its->setObjectName("label_name_its");
        label_name_its->setGeometry(QRect(850, 123, 71, 21));
        label_name_its->setFont(font1);
        label_name_my = new QLabel(ChessWindow2);
        label_name_my->setObjectName("label_name_my");
        label_name_my->setGeometry(QRect(850, 695, 71, 21));
        label_name_my->setFont(font1);
        pushButton_restart = new QPushButton(ChessWindow2);
        pushButton_restart->setObjectName("pushButton_restart");
        pushButton_restart->setGeometry(QRect(1010, 210, 91, 41));
        QFont font4;
        font4.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221")});
        font4.setPointSize(9);
        pushButton_restart->setFont(font4);
        pushButton_restart->setStyleSheet(QString::fromUtf8("background-color: rgb(187, 241, 169);"));
        frame_msgInput = new QFrame(ChessWindow2);
        frame_msgInput->setObjectName("frame_msgInput");
        frame_msgInput->setGeometry(QRect(460, 300, 301, 91));
        frame_msgInput->setStyleSheet(QString::fromUtf8("QPushButton:hover{\n"
"	background-color: rgb(234, 234, 234);\n"
"}"));
        frame_msgInput->setFrameShape(QFrame::Shape::StyledPanel);
        frame_msgInput->setFrameShadow(QFrame::Shadow::Raised);
        pushButton_msgInput_close = new QPushButton(frame_msgInput);
        pushButton_msgInput_close->setObjectName("pushButton_msgInput_close");
        pushButton_msgInput_close->setGeometry(QRect(3, 3, 30, 30));
        pushButton_msgInput_close->setFont(font2);
        pushButton_msgInput_close->setStyleSheet(QString::fromUtf8("QPushButton{border-radius: 15px;}\n"
"QPushButton:hover{\n"
"	background-color: rgb(234, 234, 234);\n"
"}"));
        pushButton_msgInput_close->setIcon(icon);
        pushButton_msgInput_close->setIconSize(QSize(12, 12));
        lineEdit_msgInput = new QLineEdit(frame_msgInput);
        lineEdit_msgInput->setObjectName("lineEdit_msgInput");
        lineEdit_msgInput->setGeometry(QRect(60, 40, 161, 38));
        lineEdit_msgInput->setStyleSheet(QString::fromUtf8("padding: 5px;\n"
"border-top: 2px solid qlineargradient(y0:0,y1:1,stop: 0 #ececef, stop: 1 white);\n"
"border-left: 1px solid qlineargradient(x0:0, x1:1,stop: 0 #ececef, stop: 1 white);\n"
"border-bottom: 4px solid qlineargradient(y0:0,y1:1,stop: 0 white, stop: 1 #ececef);\n"
"border-right: 1px solid qlineargradient(x0:0, x1:1,stop: 0 white, stop: 1 #ececef);"));
        pushButton_msgInputOk = new QPushButton(frame_msgInput);
        pushButton_msgInputOk->setObjectName("pushButton_msgInputOk");
        pushButton_msgInputOk->setGeometry(QRect(230, 40, 61, 36));
        pushButton_msgInputOk->setFont(font1);
        pushButton_msgInputOk->setStyleSheet(QString::fromUtf8("background-color: rgb(187, 241, 169);"));
        label_nameInput = new QLabel(frame_msgInput);
        label_nameInput->setObjectName("label_nameInput");
        label_nameInput->setGeometry(QRect(10, 50, 41, 21));
        label_nameInput->setFont(font3);

        retranslateUi(ChessWindow2);

        QMetaObject::connectSlotsByName(ChessWindow2);
    } // setupUi

    void retranslateUi(QFrame *ChessWindow2)
    {
        ChessWindow2->setWindowTitle(QCoreApplication::translate("ChessWindow2", "ChessWindow2", nullptr));
        pushButton_return_room->setText(QCoreApplication::translate("ChessWindow2", "\350\277\224\345\233\236\346\210\277\351\227\264", nullptr));
        pushButton_begin->setText(QCoreApplication::translate("ChessWindow2", "\345\274\200\345\247\213\346\270\270\346\210\217", nullptr));
        pushButton_surrender->setText(QCoreApplication::translate("ChessWindow2", "\346\212\225\351\231\215\345\226\265", nullptr));
        label_w->setText(QString());
        label_b->setText(QString());
        pushButton_create->setText(QCoreApplication::translate("ChessWindow2", "\345\210\233\345\273\272\346\210\277\351\227\264", nullptr));
        pushButton_enter->setText(QCoreApplication::translate("ChessWindow2", "\345\212\240\345\205\245\346\210\277\351\227\264", nullptr));
        pushButton_return_menu->setText(QCoreApplication::translate("ChessWindow2", "\350\277\224\345\233\236\344\270\273\350\217\234\345\215\225", nullptr));
        label_name->setText(QCoreApplication::translate("ChessWindow2", " HuTao", nullptr));
        pushButton_ipInput_close->setText(QString());
        pushButton_ipOk->setText(QCoreApplication::translate("ChessWindow2", "\347\241\256\350\256\244", nullptr));
        label_ipInput->setText(QCoreApplication::translate("ChessWindow2", "IP:", nullptr));
        pushButton_edit->setText(QCoreApplication::translate("ChessWindow2", "\347\274\226\350\276\221\344\277\241\346\201\257", nullptr));
        label_surrender_its->setText(QCoreApplication::translate("ChessWindow2", "\346\212\225\351\231\215\344\272\206\345\226\265~", nullptr));
        label_surrender_my->setText(QCoreApplication::translate("ChessWindow2", "\346\212\225\351\231\215\344\272\206\345\226\265~", nullptr));
        label_name_its->setText(QCoreApplication::translate("ChessWindow2", " HuTao", nullptr));
        label_name_my->setText(QCoreApplication::translate("ChessWindow2", " HuTao", nullptr));
        pushButton_restart->setText(QCoreApplication::translate("ChessWindow2", "\351\207\215\346\226\260\345\274\200\345\247\213", nullptr));
        pushButton_msgInput_close->setText(QString());
        pushButton_msgInputOk->setText(QCoreApplication::translate("ChessWindow2", "\347\241\256\350\256\244", nullptr));
        label_nameInput->setText(QCoreApplication::translate("ChessWindow2", "\346\230\265\347\247\260\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChessWindow2: public Ui_ChessWindow2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHESSWINDOW2_H
