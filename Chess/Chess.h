#pragma once

#include <QJsonObject>
#include <QtWidgets/QMainWindow>
#include <unordered_set>
#include "../Chessman/Chessman.h"
#include "../MyLabel//myLabel.h"
#include "../MyFrame/myFrame.h"
#include "ui_Chess.h"
#include "../User/User.h"
class Chess : public QFrame
{
    Q_OBJECT

public:
    explicit Chess(QFrame *parent = nullptr, int color = 1);
    ~Chess() override;

    void setBlock(int color);
    bool isCheckPos(int sign);
    void setRoute(int i);
    void checkPre(int i);
    void clearTargetBk();
    void clearTargetCm();
    void showPromote(int x, int y);
    void initSignal();
    void setRouteColor();

signals:
    void promoteFinished(int type);
    void sendMoved(const StepData *stepData);

public slots:
    void setChessmen(int color);
    void moveToBk(int i, bool isHost, int promoteType);
    void moveToCm(int i, bool isHost, int promoteType);
    void checkPos();
    void setBorder(int i);
    static QImage convertImageWhiteColorAlpha(QImage val);
    void getPromotion(int type);

    void onGetData(const QJsonObject *receivedData);

private:
    Ui::Chess *ui{};

    QLabel* bgLabel{};
    LabelButton* bkLabel[64]{};
    QLabel* edgeLabel[16]{};

    Chessman* chessman[32]{};
    myFrame *frame_promotion_b{};
    myFrame *frame_promotion_w{};
    std::vector<int> pos;
    std::vector<int> targetCm;
    std::vector<int> targetBk;
    std::vector<int> aliveNums_w{};
    std::vector<int> aliveNums_b{};
    int chosen = -1;
    int numNew = -1;
    int numOld = -1;
    int nowColor = 1;
    bool isChecked = false;//����
    bool isCastling = false;//������λ
    bool isPromotion = false;//��������
    int numPawn = -1;//���������б���num

};
