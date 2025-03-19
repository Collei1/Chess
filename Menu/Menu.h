//
// Created by Collei on 25-3-8.
//

#ifndef MENU_H
#define MENU_H

#include <QFrame>
#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class Menu; }
QT_END_NAMESPACE

class Menu : public QFrame {
Q_OBJECT

public:
    explicit Menu(QFrame *parent = nullptr);
    ~Menu() override;

    Ui::Menu *ui;
};


#endif //MENU_H
