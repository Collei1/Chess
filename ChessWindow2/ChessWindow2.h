//
// Created by Collei on 25-3-9.
//

#ifndef CHESSWINDOW2_H
#define CHESSWINDOW2_H

#include "../Chess/Chess.h"
#include "../Client/ChessClient.h"
#include "../Server/ChessServer.h"
#include <QFrame>
#include <QSettings>


QT_BEGIN_NAMESPACE
namespace Ui { class ChessWindow2; }
QT_END_NAMESPACE

class ChessWindow2 : public QFrame {
Q_OBJECT

public:
    explicit ChessWindow2(QFrame *parent = nullptr);
    ~ChessWindow2() override;
    void initSignal();
    void initRoom(int color);

    signals:
    void sendReturnMain();

public slots:
    void createRoom();
    void enterRoom();
    void returnMenu();
    void start();
    void restart();
    void surrender();
    void returnRoom();
    void getIp();
    void changeMsg();
    void getMoved(const StepData *stepData);

private:
    Ui::ChessWindow2 *ui;

    Chess *chess{};
    ChessServer *server{};
    ChessClient *client{};
    int myColor = -2;
    bool isHost{};
    QWidget *overlay_total{};
    QWidget *overlay_surrender{};
    //LabelButton *labelbutton_avtarInput{};

    QString username;
    QSettings *settings;
};


#endif //CHESSWINDOW2_H
