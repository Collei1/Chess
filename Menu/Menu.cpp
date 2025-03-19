//
// Created by Collei on 25-3-8.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Menu.h" resolved

#include "Menu.h"
#include "ui_Menu.h"


Menu::Menu(QFrame *parent) :
    QFrame(parent), ui(new Ui::Menu) {
    ui->setupUi(this);

}

Menu::~Menu() {
    delete ui;
}



