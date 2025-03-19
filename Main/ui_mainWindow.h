/********************************************************************************
** Form generated from reading UI file 'mainWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mainWindow
{
public:
    QGridLayout *gridLayout;
    QFrame *frame_total;
    QGridLayout *gridLayout_2;
    QFrame *frame_header;
    QPushButton *pushButton_close;
    QPushButton *pushButton_min;
    QPushButton *pushButton_min_2;
    QFrame *frame_main;

    void setupUi(QWidget *mainWindow)
    {
        if (mainWindow->objectName().isEmpty())
            mainWindow->setObjectName("mainWindow");
        mainWindow->resize(1150, 907);
        QIcon icon;
        icon.addFile(QString::fromUtf8("../image/icon.jpg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        mainWindow->setWindowIcon(icon);
        mainWindow->setStyleSheet(QString::fromUtf8("QFrame#frame_main{border-radius: 10px;border: none;background-color: rgb(255, 255, 255);}\n"
"QFrame#frame_header{border-radius: 10px;border: none;background-color: rgb(215, 232, 205);}\n"
"QFrame#frame_total{border-radius: 10px;background-color: rgb(215, 232, 205);}\n"
"\n"
"\n"
"\n"
"\n"
""));
        gridLayout = new QGridLayout(mainWindow);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(5, 5, 5, 5);
        frame_total = new QFrame(mainWindow);
        frame_total->setObjectName("frame_total");
        frame_total->setStyleSheet(QString::fromUtf8(""));
        frame_total->setFrameShape(QFrame::Shape::StyledPanel);
        frame_total->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_2 = new QGridLayout(frame_total);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        frame_header = new QFrame(frame_total);
        frame_header->setObjectName("frame_header");
        frame_header->setStyleSheet(QString::fromUtf8("QPushButton{border-radius: 15px;}\n"
"QPushButton:hover{\n"
"	background-color: rgb(234, 234, 234);\n"
"}"));
        frame_header->setFrameShape(QFrame::Shape::StyledPanel);
        frame_header->setFrameShadow(QFrame::Shadow::Raised);
        pushButton_close = new QPushButton(frame_header);
        pushButton_close->setObjectName("pushButton_close");
        pushButton_close->setGeometry(QRect(1090, 8, 30, 30));
        pushButton_close->setStyleSheet(QString::fromUtf8(""));
        QIcon icon1(QIcon::fromTheme(QIcon::ThemeIcon::ApplicationExit));
        pushButton_close->setIcon(icon1);
        pushButton_min = new QPushButton(frame_header);
        pushButton_min->setObjectName("pushButton_min");
        pushButton_min->setGeometry(QRect(1040, 8, 30, 30));
        pushButton_min->setStyleSheet(QString::fromUtf8(""));
        QIcon icon2(QIcon::fromTheme(QIcon::ThemeIcon::ListRemove));
        pushButton_min->setIcon(icon2);
        pushButton_min_2 = new QPushButton(frame_header);
        pushButton_min_2->setObjectName("pushButton_min_2");
        pushButton_min_2->setGeometry(QRect(990, 8, 30, 30));
        pushButton_min_2->setStyleSheet(QString::fromUtf8(""));
        QIcon icon3(QIcon::fromTheme(QIcon::ThemeIcon::DocumentProperties));
        pushButton_min_2->setIcon(icon3);

        gridLayout_2->addWidget(frame_header, 0, 0, 1, 1);

        frame_main = new QFrame(frame_total);
        frame_main->setObjectName("frame_main");
        frame_main->setStyleSheet(QString::fromUtf8("border-radius: 10px;"));
        frame_main->setFrameShape(QFrame::Shape::StyledPanel);
        frame_main->setFrameShadow(QFrame::Shadow::Raised);

        gridLayout_2->addWidget(frame_main, 1, 0, 1, 1);

        gridLayout_2->setRowStretch(0, 1);
        gridLayout_2->setRowStretch(1, 18);

        gridLayout->addWidget(frame_total, 0, 0, 1, 1);


        retranslateUi(mainWindow);

        QMetaObject::connectSlotsByName(mainWindow);
    } // setupUi

    void retranslateUi(QWidget *mainWindow)
    {
        mainWindow->setWindowTitle(QCoreApplication::translate("mainWindow", "Chess", nullptr));
        pushButton_close->setText(QString());
        pushButton_min->setText(QString());
        pushButton_min_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class mainWindow: public Ui_mainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
