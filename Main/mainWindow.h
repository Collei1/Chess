//
// Created by Collei on 25-3-6.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../ChessWindow1/ChessWindow1.h"
#include "../ChessWindow2/ChessWindow2.h"
#include "../Menu/Menu.h"
#include <QWidget>
#include<QEvent>
#include<QMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class mainWindow; }
QT_END_NAMESPACE

class mainWindow : public QWidget {
Q_OBJECT

public:
    explicit mainWindow(QWidget *parent = nullptr);
    ~mainWindow() override;
    void initSignal();

public slots:
    void showChess1();
    void showChess2();
    void returnMain();

private:
    Ui::mainWindow *ui;
    Menu *menu;
    ChessWindow1 *chess1;
    ChessWindow2 *chess2;

protected:
    bool isDragging = false;
    QPoint dragStartPosition;
    void mousePressEvent( QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
};


#endif //MAINWINDOW_H
