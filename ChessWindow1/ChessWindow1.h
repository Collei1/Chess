//
// Created by Collei on 25-3-8.
//

#ifndef CHESSWINDOW_H
#define CHESSWINDOW_H
#include "../Chess/Chess.h"
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class ChessWindow1; }
QT_END_NAMESPACE

class ChessWindow1 : public QFrame {
Q_OBJECT

public:
    explicit ChessWindow1(QFrame *parent = nullptr);
    ~ChessWindow1() override;

    void initSignal();
    void start();
    void restart();
    void returnMain();
    signals:
    void sendReturnMain();
private:
    Ui::ChessWindow1 *ui;

    Chess *chess;


};


#endif //CHESSWINDOW_H
