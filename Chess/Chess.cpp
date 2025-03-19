#include "Chess.h"
#include<QObject>

Chess::Chess(QFrame *parent, int color)
    : QFrame(parent), ui(new Ui::Chess)
{
    ui->setupUi(this);
    frame_promotion_b = new myFrame(this, 0, color);
    frame_promotion_w = new myFrame(this, 1, color);

    ui->label_chess->setVisible(false);
    ui->label_win->setVisible(false);
    setBlock(color);
    initSignal();
}
void Chess::initSignal() {
    connect(frame_promotion_b, &myFrame::sendPromote, this, getPromotion);
    connect(frame_promotion_w, &myFrame::sendPromote, this, getPromotion);
}

Chess::~Chess() {
    delete ui;
}

void Chess::getPromotion(int type) {
    if(numPawn != -1) {
        chessman[numPawn]->promote(type);
    }else {
        qDebug()<< "no promoted pawnNum";
    }
    checkPos();
    frame_promotion_b->Hide();
    frame_promotion_w->Hide();
    emit promoteFinished(type);
}
void Chess::onGetData(const QJsonObject *receivedData) {
    int itNUm = receivedData->value("myNum").toInt();
    int oldLoc = receivedData->value("oldLoc").toInt();
    int newLoc = receivedData->value("newLoc").toInt();
    int eatedNum = receivedData->value("eatedNum").toInt();
    bool isPromotion = receivedData->value("isPromotion").toBool();
    int promotedType = receivedData->value("promotedType").toInt();
    bool isCastling = receivedData->value("isCastling").toBool();
    qDebug()<< "getData";
    chosen = itNUm;
    this->isPromotion = isPromotion;
    this->isCastling = isCastling;
    if(eatedNum == -1) {
        bkLabel[newLoc]->target = true;
        qDebug()<< "move"<<itNUm<<"to"<<newLoc;
        moveToBk(newLoc, false, promotedType);
    }else {
        chessman[eatedNum]->target = true;
        qDebug()<< "move"<<itNUm<<"to"<<newLoc;
        moveToCm(eatedNum, false, promotedType);
    }
}

void Chess::setBlock(int color) {
            pos = std::vector<int>(64, -1);

            bgLabel = new QLabel(this);
            bgLabel->setObjectName("label_bg");
            bgLabel->setGeometry(QRect(115, 95, 650, 650));
            //bgLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(248, 251, 241);"));
            bgLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
            for (int i = 0; i < 8; i++) {
                edgeLabel[i] = new QLabel(this);
                edgeLabel[i]->setObjectName("label_edge");


                edgeLabel[i]->setText(QString::fromUtf8(std::to_string(i + 1)));
                edgeLabel[i]->setAlignment(Qt::AlignCenter);

                edgeLabel[i + 8] = new QLabel(this);
                edgeLabel[i + 8]->setObjectName("label_edge");

                edgeLabel[i + 8]->setText(QString::fromUtf8(std::string(1, char('a' + i))));
                edgeLabel[i + 8]->setAlignment(Qt::AlignCenter);

                if(color) {
                    edgeLabel[i]->setGeometry(QRect(85, 665 - i * 80, 30, 80));
                    edgeLabel[i + 8]->setGeometry(QRect(120 + i * 80, 745, 80, 30));
                }else {
                    edgeLabel[i]->setGeometry(QRect(85, 95 + i * 80, 30, 80));
                    edgeLabel[i + 8]->setGeometry(QRect(665 - i * 80, 745, 80, 30));
                }
                for (int j = 0; j < 8; j++) {
                    bkLabel[i * 8 + j] = new LabelButton(this);
                    std::string str_name = "label_bk_";
                    str_name += std::to_string(i * 8 + j);
                    bkLabel[i * 8 + j]->setObjectName(str_name);
                    if(color) {
                        bkLabel[i * 8 + j]->setGeometry(QRect(120 + j * 80, 100 + i * 80, 80, 80));
                    }else {
                        bkLabel[i * 8 + j]->setGeometry(QRect(680 - j * 80, 660 - i * 80, 80, 80));
                    }


                    std::string str_image = (i + j) % 2 == 0 ? "../image/white.png" : "../image/black.png";
                    bkLabel[i * 8 + j]->setPixmap(QPixmap::fromImage(QImage(QString::fromUtf8(str_image))));
                    bkLabel[i * 8 + j]->show();
                    bkLabel[i * 8 + j]->setScaledContents(true);
                    connect(this->bkLabel[i * 8 + j], &LabelButton::Clicked, this, [=]() {this->moveToBk(i * 8 + j, true, -1); });

                }
            }
        }
/*void Chess::setChessmen(int color) {
            chessman[0] = new Chessman(this, 0, 5);
            chessman[0]->setGeometry(QRect(320, 80, 58, 58));
            chessman[0]->loc = 4;
            pos[4] = 0;

            chessman[1] = new Chessman(this, 1, 5);
            chessman[1]->setGeometry(QRect(320, 500, 58, 58));
            chessman[1]->loc = 60;
            pos[60] = 1;

            chessman[2] = new Chessman(this, 0, 4);
            chessman[2]->setGeometry(QRect(260, 80, 58, 58));
            chessman[2]->loc = 3;
            pos[3] = 2;

            chessman[3] = new Chessman(this, 1, 4);
            chessman[3]->setGeometry(QRect(260, 500, 58, 58));
            chessman[3]->loc = 59;
            pos[59] = 3;

            for (int i = 0; i < 8; i++) {
                chessman[i + 16] = new Chessman(this, 0, 0);
                chessman[i + 16]->setGeometry(QRect(80 + i * 60, 140, 58, 58));
                chessman[i + 16]->loc = 8 + i;
                pos[8 + i] = i + 16;

                chessman[i + 24] = new Chessman(this, 1, 0);
                chessman[i + 24]->setGeometry(QRect(80 + i * 60, 440, 58, 58));
                chessman[i + 24]->loc = 48 + i;
                pos[48 + i] = i + 24;
            }
            for (int i = 0; i < 2; i++) {
                chessman[i + 4] = new Chessman(this, 0, 1);
                chessman[i + 4]->setGeometry(QRect(80 + i * 420, 80, 58, 58));
                chessman[i + 4]->loc = 0 + 7 * i;
                pos[0 + 7 * i] = i + 4;

                chessman[i + 6] = new Chessman(this, 1, 1);
                chessman[i + 6]->setGeometry(QRect(80 + i * 420, 500, 58, 58));
                chessman[i + 6]->loc = 56 + 7 * i;
                pos[56 + 7 * i] = i + 6;

                chessman[i + 8] = new Chessman(this, 0, 2);
                chessman[i + 8]->setGeometry(QRect(140 + i * 300, 80, 58, 58));
                chessman[i + 8]->loc = 1 + 5 * i;
                pos[1 + 5 * i] = i + 8;

                chessman[i + 10] = new Chessman(this, 1, 2);
                chessman[i + 10]->setGeometry(QRect(140 + i * 300, 500, 58, 58));
                chessman[i + 10]->loc = 57 + 5 * i;
                pos[57 + 5 * i] = i + 10;

                chessman[i + 12] = new Chessman(this, 0, 3);
                chessman[i + 12]->setGeometry(QRect(200 + i * 180, 80, 58, 58));
                chessman[i + 12]->loc = 2 + 3 * i;
                pos[2 + 3 * i] = i + 12;

                chessman[i + 14] = new Chessman(this, 1, 3);
                chessman[i + 14]->setGeometry(QRect(200 + i * 180, 500, 58, 58));
                chessman[i + 14]->loc = 58 + 3 * i;
                pos[58 + 3 * i] = i + 14;
            }

            aliveNums_b = std::vector<int>{4, 8, 12, 2, 0, 13, 9, 5, 16, 17, 18, 19, 20, 21, 22, 23};
            aliveNums_w = std::vector<int>{6, 10, 14, 3, 1, 15, 11, 7, 24, 25, 26, 27, 28, 29, 30, 31};

            if(color == -1) {
                for (int i = 0; i < 32; i++) {
                    connect(this->chessman[i], &Chessman::Clicked, this, [=]() {this->setBorder(i); });
                    connect(this->chessman[i], &Chessman::Clicked, this, [=]() {this->moveToCm(i, true, -1); });
                }
            }else if(color == 1) {
                for(auto i : aliveNums_w) {
                    connect(this->chessman[i], &Chessman::Clicked, this, [=]() {this->setBorder(i); });
                }
                for(auto i : aliveNums_b) {
                    connect(this->chessman[i], &Chessman::Clicked, this, [=]() {this->moveToCm(i, true, -1); });
                }
            }else if(color == 0) {
                for(auto i : aliveNums_b) {
                    connect(this->chessman[i], &Chessman::Clicked, this, [=]() {this->setBorder(i); });
                }
                for(auto i : aliveNums_w) {
                    connect(this->chessman[i], &Chessman::Clicked, this, [=]() {this->moveToCm(i, true, -1); });
                }
            }
            //ui->pushButton_begin->setDisabled(true);
        }*/
        void Chess::setChessmen(int color) {
            chessman[0] = new Chessman(this, 0, 5);
            chessman[0]->setGeometry(bkLabel[4]->geometry());
            chessman[0]->loc = 4;
            pos[4] = 0;

            chessman[1] = new Chessman(this, 1, 5);
            chessman[1]->setGeometry(bkLabel[60]->geometry());
            chessman[1]->loc = 60;
            pos[60] = 1;

            chessman[2] = new Chessman(this, 0, 4);
            chessman[2]->setGeometry(bkLabel[3]->geometry());
            chessman[2]->loc = 3;
            pos[3] = 2;

            chessman[3] = new Chessman(this, 1, 4);
            chessman[3]->setGeometry(bkLabel[59]->geometry());
            chessman[3]->loc = 59;
            pos[59] = 3;

            for (int i = 0; i < 8; i++) {
                chessman[i + 16] = new Chessman(this, 0, 0);
                chessman[i + 16]->setGeometry(bkLabel[8 + i]->geometry());
                chessman[i + 16]->loc = 8 + i;
                pos[8 + i] = i + 16;

                chessman[i + 24] = new Chessman(this, 1, 0);
                chessman[i + 24]->setGeometry(bkLabel[48 + i]->geometry());
                chessman[i + 24]->loc = 48 + i;
                pos[48 + i] = i + 24;
            }
            for (int i = 0; i < 2; i++) {
                chessman[i + 4] = new Chessman(this, 0, 1);
                chessman[i + 4]->setGeometry(bkLabel[i * 7]->geometry());
                chessman[i + 4]->loc = 0 + 7 * i;
                pos[0 + 7 * i] = i + 4;

                chessman[i + 6] = new Chessman(this, 1, 1);
                chessman[i + 6]->setGeometry(bkLabel[56 + i * 7]->geometry());
                chessman[i + 6]->loc = 56 + 7 * i;
                pos[56 + 7 * i] = i + 6;

                chessman[i + 8] = new Chessman(this, 0, 2);
                chessman[i + 8]->setGeometry(bkLabel[1 + i * 5]->geometry());
                chessman[i + 8]->loc = 1 + 5 * i;
                pos[1 + 5 * i] = i + 8;

                chessman[i + 10] = new Chessman(this, 1, 2);
                chessman[i + 10]->setGeometry(bkLabel[57 + i * 5]->geometry());
                chessman[i + 10]->loc = 57 + 5 * i;
                pos[57 + 5 * i] = i + 10;

                chessman[i + 12] = new Chessman(this, 0, 3);
                chessman[i + 12]->setGeometry(bkLabel[2 + i * 3]->geometry());
                chessman[i + 12]->loc = 2 + 3 * i;
                pos[2 + 3 * i] = i + 12;

                chessman[i + 14] = new Chessman(this, 1, 3);
                chessman[i + 14]->setGeometry(bkLabel[58 + i * 3]->geometry());
                chessman[i + 14]->loc = 58 + 3 * i;
                pos[58 + 3 * i] = i + 14;
            }

            aliveNums_b = std::vector<int>{4, 8, 12, 2, 0, 13, 9, 5, 16, 17, 18, 19, 20, 21, 22, 23};
            aliveNums_w = std::vector<int>{6, 10, 14, 3, 1, 15, 11, 7, 24, 25, 26, 27, 28, 29, 30, 31};

            if(color == -1) {
                for (int i = 0; i < 32; i++) {
                    connect(this->chessman[i], &Chessman::Clicked, this, [=]() {this->setBorder(i); });
                    connect(this->chessman[i], &Chessman::Clicked, this, [=]() {this->moveToCm(i, true, -1); });
                }
            }else if(color == 1) {
                for(auto i : aliveNums_w) {
                    connect(this->chessman[i], &Chessman::Clicked, this, [=]() {this->setBorder(i); });
                }
                for(auto i : aliveNums_b) {
                    connect(this->chessman[i], &Chessman::Clicked, this, [=]() {this->moveToCm(i, true, -1); });
                }
            }else if(color == 0) {
                for(auto i : aliveNums_b) {
                    connect(this->chessman[i], &Chessman::Clicked, this, [=]() {this->setBorder(i); });
                }
                for(auto i : aliveNums_w) {
                    connect(this->chessman[i], &Chessman::Clicked, this, [=]() {this->moveToCm(i, true, -1); });
                }
            }
            //ui->pushButton_begin->setDisabled(true);
        }


        void Chess::moveToBk(int i, bool isHost, int promoteType) {//???????????   i?Bk?????¦Ë???
            if (chosen != -1 && bkLabel[i]->target) {
                if (numNew != -1) {
                    chessman[numNew]->setStyleSheet("QLabel{border:0px;}");
                }
                if (numOld != -1) {
                    bkLabel[numOld]->setStyleSheet("QLabel{border:0px;}");
                }
                /*isCastling = false;
                isPromotion = false;*/

                numOld = chessman[chosen]->loc;
                pos[chessman[chosen]->loc] = -1;
                pos[i] = chosen;
                chessman[chosen]->setGeometry(bkLabel[i]->geometry());
                chessman[chosen]->loc = i;
                chessman[chosen]->moved = true;
                chessman[chosen]->choose = false;
                numNew = chosen;
                int promoteTypeHost = -1;
                if(isPromotion) {
                    //????
                    if(isHost) {
                        QEventLoop loop;
                        connect(this, &Chess::promoteFinished, &loop, [&loop, &promoteTypeHost](int type) {
                            promoteTypeHost = type;
                            loop.quit(); // ?????????
                        });
                        showPromote(bkLabel[i]->x(), bkLabel[i]->y());
                        numPawn = chosen;
                        qDebug() << "Starting promote...";
                        loop.exec(); // ??? finished ???
                        qDebug() << "Promote finished, continuing...";
                    }else {
                        chessman[chosen]->promote(promoteType);
                        checkPos();
                    }
                }
                if(isHost) {
                    StepData stepData(chosen, numOld, i, -1, isPromotion, promoteTypeHost, isCastling);
                    emit sendMoved(&stepData);
                }
                clearTargetBk();
                clearTargetCm();
                chessman[numNew]->setStyleSheet("QLabel{border:0.5px solid rgb(255, 0, 0);}");
                bkLabel[numOld]->setStyleSheet("QLabel{border:0.5px solid rgb(255, 0, 0);}");

                if(isCastling) {// (bkNum, rookNum, newLoction) , kingNum = chosen
                    std::unordered_map<int, std::pair<int, int>> nums = {{2, {4,3}}, {6, {5,5}},{62, {7,61}}, {58,{6, 59}}};
                    if(i == 2 || i == 6 ||i == 58 || i == 62) {
                        int rookNum = nums[i].first;
                        int newLoction = nums[i].second;
                        pos[chessman[rookNum]->loc] = -1;
                        pos[newLoction] = rookNum;
                        chessman[rookNum]->setGeometry(bkLabel[newLoction]->geometry());
                        chessman[rookNum]->loc = newLoction;
                        chessman[rookNum]->moved = true;
                    }
                }
                isPromotion = false;
                isCastling = false;
                nowColor = 1 - nowColor;
                checkPos();
            }
        }

        void Chess::moveToCm(int i, bool isHost, int promoteType) {//??????????   i????????????
            if (chosen != -1 && chessman[i]->target) {
                if (numNew != -1) {
                    chessman[numNew]->setStyleSheet("QLabel{border:0px;}");
                }
                if (numOld != -1) {
                    bkLabel[numOld]->setStyleSheet("QLabel{border:0px;}");
                }

                numOld = chessman[chosen]->loc;
                pos[chessman[chosen]->loc] = -1;
                pos[chessman[i]->loc] = chosen;
                chessman[chosen]->setGeometry(chessman[i]->geometry());
                chessman[chosen]->loc = chessman[i]->loc;
                chessman[chosen]->moved = true;
                chessman[chosen]->choose = false;
                chessman[i]->close();
                if(nowColor) {
                    aliveNums_b.erase(std::remove(aliveNums_b.begin(), aliveNums_b.end(), i), aliveNums_b.end());
                }else {
                    aliveNums_w.erase(std::remove(aliveNums_w.begin(), aliveNums_w.end(), i), aliveNums_w.end());
                }
                numNew = chosen;
                int promoteTypeHost = -1;
                if(isPromotion) {
                    //????
                    if(isHost) {
                        QEventLoop loop;
                        connect(this, &Chess::promoteFinished, &loop, [&loop, &promoteTypeHost](int type) {
                            promoteTypeHost = type;
                            loop.quit(); // ?????????
                        });
                        showPromote(chessman[i]->x(), chessman[i]->y());
                        numPawn = chosen;
                        qDebug() << "Starting promote...";
                        loop.exec(); // ??? finished ???
                        qDebug() << "Promote finished, continuing...";
                    }else {
                        chessman[chosen]->promote(promoteType);
                        checkPos();
                    }
                }
                if(isHost) {
                    StepData stepData(chosen, numOld, chessman[chosen]->loc, i, isPromotion, promoteTypeHost, isCastling);
                    emit sendMoved(&stepData);
                }
                clearTargetBk();
                clearTargetCm();
                chessman[numNew]->setStyleSheet("QLabel{border:0.5px solid rgb(255, 0, 0);}");
                bkLabel[numOld]->setStyleSheet("QLabel{border:0.5px solid rgb(255, 0, 0);}");

                isPromotion = false;
                isCastling = false;
                nowColor = 1 - nowColor;
                checkPos();
            }
        }

        void Chess::checkPos() {
            if (isCheckPos(-1)) {
                ui->label_chess->setVisible(true);
                isChecked = true;

                //????????
                bool isEnd = true;
                for(auto i : nowColor ? aliveNums_w : aliveNums_b) {
                    setRoute(i);
                    if(!targetBk.empty() || !targetCm.empty()) {
                        isEnd = false;
                        break;
                    }
                    targetBk.clear();
                    targetCm.clear();
                }
                if(isEnd) {
                    ui->label_win->setText(nowColor ? "The Black Win!" : "The White Win!");
                    ui->label_win->setVisible(true);
                    ui->label_chess->setVisible(false);
                }

            }else {
                ui->label_chess->setVisible(false);
                isChecked = false;
            }
        }
        bool Chess::isCheckPos(int sign) {      //sign?????-1?????????¡¤??¦Ë??
            int loction = -1;
            if (sign == -1) {//?????????ï…??÷‚????
                loction = chessman[nowColor]->loc;
            }
            else {//????????vector<>??ï…????????????
                loction = sign;
                pos[chessman[nowColor]->loc] = -1;
            }
            int num = loction;
            while (num > 7) {//??????????
                num -= 8;
                if (pos[num] == -1) {
                    continue;
                }
                if(sign !=- 1 && num + 8 == loction) {//???????***???????2
                    if(pos[num] == 1 - nowColor) {
                        return true;
                    }
                }
                if (chessman[pos[num]]->color != nowColor && (chessman[pos[num]]->type == 1 || chessman[pos[num]]->type == 4)) {//???????????
                    return true;
                }
                break;//???
            }
            num = loction;
            while (num < 56) {//??????????
                num += 8;
                if (pos[num] == -1) {
                    continue;
                }
                if(sign !=- 1 && num - 8 == loction) {//???????***???????2
                    if(pos[num] == 1 - nowColor) {
                        return true;
                    }
                }
                if(num - 8 == loction) {//???????
                    if(pos[num] == 1 - nowColor) {
                        return true;
                    }
                }
                if (chessman[pos[num]]->color != nowColor && (chessman[pos[num]]->type == 1 || chessman[pos[num]]->type == 4)) {//???????????
                    return true;
                }
                break;//???
            }
            num = loction;
            while (num % 8 != 0) {//??????????
                num -= 1;
                if (pos[num] == -1) {
                    continue;
                }
                if(sign !=- 1 && num + 1 == loction) {//???????***???????2
                    if(pos[num] == 1 - nowColor) {
                        return true;
                    }
                }
                if (chessman[pos[num]]->color != nowColor && (chessman[pos[num]]->type == 1 || chessman[pos[num]]->type == 4)) {//???????????
                    return true;
                }
                break;//???
            }
            num = loction;
            while (num % 8 != 7) {//??????????
                num += 1;
                if (pos[num] == -1) {
                    continue;
                }
                if(sign !=- 1 && num - 1 == loction) {//???????***???????2
                    if(pos[num] == 1 - nowColor) {
                        return true;
                    }
                }
                if (chessman[pos[num]]->color != nowColor && (chessman[pos[num]]->type == 1 || chessman[pos[num]]->type == 4)) {//???????????
                    return true;
                }
                break;//???
            }
            num = loction;
            while (num > 7 && num % 8 != 0) {//????????????
                num -= 9;
                if (pos[num] == -1) {
                    continue;
                }
                if(sign !=- 1 && num - 9 == loction) {//???????***???????2
                    if(pos[num] == 1 - nowColor) {
                        return true;
                    }
                }
                if (chessman[pos[num]]->color != nowColor && (chessman[pos[num]]->type == 3 || chessman[pos[num]]->type == 4)) {//????????
                    return true;
                }
                break;//???
            }
            num = loction;
            while (num < 56 && num % 8 != 0) {//????????????
                num += 7;
                if (pos[num] == -1) {
                    continue;
                }
                if(sign !=- 1 && num - 7 == loction) {//???????***???????2
                    if(pos[num] == 1 - nowColor) {
                        return true;
                    }
                }
                if (chessman[pos[num]]->color != nowColor && (chessman[pos[num]]->type == 3 || chessman[pos[num]]->type == 4)) {//????????
                    return true;
                }
                break;//???
            }
            num = loction;
            while (num > 7 && num % 8 != 7) {//????????????
                num -= 7;
                if (pos[num] == -1) {
                    continue;
                }
                if(sign !=- 1 && num + 7 == loction) {//???????***???????2
                    if(pos[num] == 1 - nowColor) {
                        return true;
                    }
                }
                if (chessman[pos[num]]->color != nowColor && (chessman[pos[num]]->type == 3 || chessman[pos[num]]->type == 4)) {//????????
                    return true;
                }
                break;//???
            }
            num = loction;
            while (num < 56 && num % 8 != 7) {//????????????
                num += 9;
                if (pos[num] == -1) {
                    continue;
                }
                if(sign !=- 1 && num - 9 == loction) {//???????***???????2
                    if(pos[num] == 1 - nowColor) {
                        return true;
                    }
                }
                if (chessman[pos[num]]->color != nowColor && (chessman[pos[num]]->type == 3 || chessman[pos[num]]->type == 4)) {//????????
                    return true;
                }
                break;//???
            }//????
            if (nowColor) {//????
                num = loction;
                if (num > 7 && num % 8 != 0) {//????????????1
                    num -= 9;
                    if (pos[num] != -1) {
                        if (chessman[pos[num]]->color != nowColor && chessman[pos[num]]->type == 0) {//?????????
                            return true;
                        }
                    }
                }
                num = loction;
                if (num > 7 && num % 8 != 7) {//????????????1
                    num -= 7;
                    if (pos[num] != -1) {
                        if (chessman[pos[num]]->color != nowColor && chessman[pos[num]]->type == 0) {//?????????
                            return true;
                        }
                    }
                }
            }
            else {
                num = loction;
                if (num < 56 && num % 8 != 0) {//????????????1
                    num += 7;
                    if (pos[num] != -1) {
                        if (chessman[pos[num]]->color != nowColor && chessman[pos[num]]->type == 0) {//?????????
                            return true;
                        }
                    }

                }
                num = loction;
                if (num < 56 && num % 8 != 7) {//????????????1
                    num += 9;
                    if (pos[num] != -1) {
                        if (chessman[pos[num]]->color != nowColor && chessman[pos[num]]->type == 0) {//?????????
                            return true;
                        }
                    }

                }
            }
            num = loction;//?????
            if (num > 15 && num % 8 > 0) {//????
                if (pos[num - 17] != -1) {
                    if (chessman[pos[num - 17]]->color != chessman[nowColor]->color && chessman[pos[num - 17]]->type == 2) {//?????????
                        return true;
                    }
                }

            }
            if (num > 15 && num % 8 < 7) {//????
                if (pos[num - 15] != -1) {
                    if (chessman[pos[num - 15]]->color != chessman[nowColor]->color && chessman[pos[num - 15]]->type == 2) {
                        return true;
                    }
                }

            }
            if (num > 7 && num % 8 > 1) {//????
                if (pos[num - 10] != -1) {
                    if (chessman[pos[num - 10]]->color != chessman[nowColor]->color && chessman[pos[num - 10]]->type == 2) {
                        return true;
                    }
                }

            }
            if (num > 7 && num % 8 < 6) {//????
                if (pos[num - 6] != -1) {
                    if (pos[num] != -1 && chessman[pos[num - 6]]->color != chessman[nowColor]->color && chessman[pos[num - 6]]->type == 2) {
                        return true;
                    }
                }

            }
            if (num < 48 && num % 8 > 0) {//????
                if (pos[num + 15] != -1) {
                    if (chessman[pos[num + 15]]->color != chessman[nowColor]->color && chessman[pos[num + 15]]->type == 2) {
                        return true;
                    }
                }

            }
            if (num < 48 && num % 8 < 7) {//????
                if (pos[num + 17] != -1) {
                    if (chessman[pos[num + 17]]->color != chessman[nowColor]->color && chessman[pos[num + 17]]->type == 2) {
                        return true;
                    }
                }

            }
            if (num < 56 && num % 8 > 1) {//????
                if (pos[num + 6] != -1) {
                    if (chessman[pos[num + 6]]->color != chessman[nowColor]->color && chessman[pos[num + 6]]->type == 2) {
                        return true;
                    }
                }

            }
            if (num < 56 && num % 8 < 6) {//????
                if (pos[num + 10] != -1) {
                    if (chessman[pos[num + 10]]->color != chessman[nowColor]->color && chessman[pos[num + 10]]->type == 2) {
                        return true;
                    }
                }
            }
            return false;
        }
        void Chess::checkPre(int i) {//??????
            if (i == 0 || i == 1) {//??????????¡¤?????
                for (int j = 0; j < targetBk.size(); j++) {//////pos[Chessman[nowColor]->loc] = -1;
                    if (isCheckPos(targetBk[j])) {
                        /*bkLabel[targetBk[j]]->setStyleSheet("QLabel{border:0px;}");
                        bkLabel[targetBk[j]]->target = false;*/
                        targetBk.erase(targetBk.begin() + j);
                        j--;
                    }
                    pos[chessman[nowColor]->loc] = nowColor;
                }
                for (int j = 0; j < targetCm.size(); j++) {
                    if (isCheckPos(chessman[targetCm[j]]->loc)) {
                        /*chessman[targetCm[j]]->setStyleSheet("QLabel{border:0px;}");
                        chessman[targetCm[j]]->target = false;*/
                        targetCm.erase(targetCm.begin() + j);
                        j--;
                    }
                    pos[chessman[nowColor]->loc] = nowColor;
                }
            }
            else {//???????????¡¤?????
                for (int j = 0; j < targetBk.size(); j++) {
                    pos[chessman[i]->loc] = -1;
                    int numTargetBk = targetBk[j];
                    pos[numTargetBk] = i;
                    if (isCheckPos(-1)) {
                        /*bkLabel[targetBk[j]]->setStyleSheet("QLabel{border:0px;}");
                        bkLabel[targetBk[j]]->target = false;*/
                        targetBk.erase(targetBk.begin() + j);
                        j--;
                    }
                    pos[numTargetBk] = -1;
                    pos[chessman[i]->loc] = i;
                }
                for (int j = 0; j < targetCm.size(); j++) {
                    pos[chessman[i]->loc] = -1;
                    int numTargetCm = targetCm[j];
                    pos[chessman[numTargetCm]->loc] = i;
                    if (isCheckPos(-1)) {
                        chessman[targetCm[j]]->setStyleSheet("QLabel{border:0px;}");
                        chessman[targetCm[j]]->target = false;
                        targetCm.erase(targetCm.begin() + j);
                        j--;
                    }
                    pos[chessman[i]->loc] = i;
                    pos[chessman[numTargetCm]->loc] = numTargetCm;
                }
            }
        }

        void Chess::setBorder(int i) {//?????????????   i???????
            if (chessman[i]->target) {
                return;
            }

            if (nowColor != chessman[i]->color) {//??
                return;
            }

            if (numNew != -1) {
                chessman[numNew]->setStyleSheet("QLabel{border:0px;}");
            }
            if (numOld != -1) {
                bkLabel[numOld]->setStyleSheet("QLabel{border:0px;}");
            }
            isCastling = false;
            isPromotion = false;
            clearTargetBk();
            clearTargetCm();
            if (!chessman[i]->choose) {//????????
                chosen = i;
                chessman[i]->setStyleSheet("QLabel{border:2px solid rgb(0, 0, 255);}");
                chessman[i]->choose = true;
                setRoute(i);
                setRouteColor();
            }
            else {//??????????
                chosen = -1;
                chessman[i]->setStyleSheet("QLabel{border:0px;}");
                chessman[i]->choose = false;
            }
        }
        void Chess::setRoute(int i) {//??????????????(????????????????)
            int num = -1;
            switch (chessman[i]->type) {
            case 0:          //??
            {
                num = chessman[i]->loc;
                if (chessman[i]->color) { //???
                    if (num > 7) {//?§Ø??????????
                        if (pos[num - 8] == -1) {//?1??
                            //bkLabel[num - 8]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                            //bkLabel[num - 8]->target = true;
                            targetBk.push_back(num - 8);

                            if (!chessman[i]->moved && pos[num - 16] == -1) {//????????2??
                                //bkLabel[num - 16]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                               // bkLabel[num - 16]->target = true;
                                targetBk.push_back(num - 16);
                            }
                        }
                        if (num % 8 != 0) {//?§Ø??????????
                            if (pos[num - 9] != -1 && !chessman[pos[num - 9]]->color) {//?????????
                                //chessman[pos[num - 9]]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                               // chessman[pos[num - 9]]->target = true;
                                targetCm.push_back(pos[num - 9]);
                            }
                        }
                        if (num % 8 != 7) {//?§Ø??????????
                            if (pos[num - 7] != -1 && !chessman[pos[num - 7]]->color) {//?????????
                                //chessman[pos[num - 7]]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                                //chessman[pos[num - 7]]->target = true;
                                targetCm.push_back(pos[num - 7]);
                            }
                        }
                        if(num - 8 <= 7) {//????
                            isPromotion = true;
                        }
                    }
                }
                else {//???
                    if (num < 56) {
                        if (pos[num + 8] == -1) {
                            //bkLabel[num + 8]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                            //bkLabel[num + 8]->target = true;
                            targetBk.push_back(num + 8);
                            if (!chessman[i]->moved && pos[num + 16] == -1) {
                               // bkLabel[num + 16]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                                //bkLabel[num + 16]->target = true;
                                targetBk.push_back(num + 16);
                            }
                        }
                        if (num % 8 != 0) {
                            if (pos[num + 7] != -1 && chessman[pos[num + 7]]->color) {
                               // chessman[pos[num + 7]]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                                //chessman[pos[num + 7]]->target = true;
                                targetCm.push_back(pos[num + 7]);
                            }
                        }
                        if (num % 8 != 7) {
                            if (pos[num + 9] != -1 && chessman[pos[num + 9]]->color) {
                              //  chessman[pos[num + 9]]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                               // chessman[pos[num + 9]]->target = true;
                                targetCm.push_back(pos[num + 9]);
                            }
                        }
                        if(num + 8 >= 56) {//????
                            isPromotion = true;
                        }
                    }
                }
                break;
            }

            case 1:     //??
            {
                num = chessman[i]->loc;
                while (num > 7) {//??????????
                    num -= 8;
                    if (pos[num] == -1) {//????
                       // bkLabel[num]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                       // bkLabel[num]->target = true;
                        targetBk.push_back(num);
                    }
                    else if (chessman[pos[num]]->color != chessman[i]->color) {//???????
                        //chessman[pos[num]]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                       // chessman[pos[num]]->target = true;
                        targetCm.push_back(pos[num]);
                        break;
                    }
                    else {
                        break;
                    }
                }
                num = chessman[i]->loc;
                while (num < 56) {//??????????
                    num += 8;
                    if (pos[num] == -1) {//????
                        //bkLabel[num]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                        //bkLabel[num]->target = true;
                        targetBk.push_back(num);
                    }
                    else if (chessman[pos[num]]->color != chessman[i]->color) {//???????
                       // chessman[pos[num]]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                       // chessman[pos[num]]->target = true;
                        targetCm.push_back(pos[num]);
                        break;
                    }
                    else {
                        break;
                    }
                }
                num = chessman[i]->loc;
                while (num % 8 != 0) {//??????????
                    num -= 1;
                    if (pos[num] == -1) {//????
                       // bkLabel[num]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                        //bkLabel[num]->target = true;
                        targetBk.push_back(num);
                    }
                    else if (chessman[pos[num]]->color != chessman[i]->color) {//???????
                       // chessman[pos[num]]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                        //chessman[pos[num]]->target = true;
                        targetCm.push_back(pos[num]);
                        break;
                    }
                    else {
                        break;
                    }
                }
                num = chessman[i]->loc;
                while (num % 8 != 7) {//??????????
                    num += 1;
                    if (pos[num] == -1) {//????
                        //bkLabel[num]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                        //bkLabel[num]->target = true;
                        targetBk.push_back(num);
                    }
                    else if (chessman[pos[num]]->color != chessman[i]->color) {//???????
                       // chessman[pos[num]]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                        //chessman[pos[num]]->target = true;
                        targetCm.push_back(pos[num]);
                        break;
                    }
                    else {
                        break;
                    }
                }
                break;
            }

            case 2: {   //??
                num = chessman[i]->loc;
                if (num > 15 && num % 8 > 0) {//????
                    if (pos[num - 17] == -1) {//????
                        //bkLabel[num - 17]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                        //bkLabel[num - 17]->target = true;
                        targetBk.push_back(num - 17);
                    }
                    else if (chessman[pos[num - 17]]->color != chessman[i]->color) {//???????
                        //chessman[pos[num - 17]]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                        //chessman[pos[num - 17]]->target = true;
                        targetCm.push_back(pos[num - 17]);
                    }
                }
                if (num > 15 && num % 8 < 7) {//????
                    if (pos[num - 15] == -1) {//????
                        //bkLabel[num - 15]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                        //bkLabel[num - 15]->target = true;
                        targetBk.push_back(num - 15);
                    }
                    else if (chessman[pos[num - 15]]->color != chessman[i]->color) {//???????
                        //chessman[pos[num - 15]]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                        //chessman[pos[num - 15]]->target = true;
                        targetCm.push_back(pos[num - 15]);
                    }
                }
                if (num > 7 && num % 8 > 1) {//????
                    if (pos[num - 10] == -1) {//????
                       // bkLabel[num - 10]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                       // bkLabel[num - 10]->target = true;
                        targetBk.push_back(num - 10);
                    }
                    else if (chessman[pos[num - 10]]->color != chessman[i]->color) {//???????
                        //chessman[pos[num - 10]]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                        //chessman[pos[num - 10]]->target = true;
                        targetCm.push_back(pos[num - 10]);
                    }
                }
                if (num > 7 && num % 8 < 6) {//????
                    if (pos[num - 6] == -1) {//????
                       // bkLabel[num - 6]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                        //bkLabel[num - 6]->target = true;
                        targetBk.push_back(num - 6);
                    }
                    else if (chessman[pos[num - 6]]->color != chessman[i]->color) {//???????
                        //chessman[pos[num - 6]]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                       // chessman[pos[num - 6]]->target = true;
                        targetCm.push_back(pos[num - 6]);
                    }
                }
                if (num < 48 && num % 8 > 0) {//????
                    if (pos[num + 15] == -1) {//????
                       // bkLabel[num + 15]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                        //bkLabel[num + 15]->target = true;
                        targetBk.push_back(num + 15);
                    }
                    else if (chessman[pos[num + 15]]->color != chessman[i]->color) {//???????
                       // chessman[pos[num + 15]]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                        //chessman[pos[num + 15]]->target = true;
                        targetCm.push_back(pos[num + 15]);
                    }
                }
                if (num < 48 && num % 8 < 7) {//????
                    if (pos[num + 17] == -1) {//????
                       // bkLabel[num + 17]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                        //bkLabel[num + 17]->target = true;
                        targetBk.push_back(num + 17);
                    }
                    else if (chessman[pos[num + 17]]->color != chessman[i]->color) {//???????
                       // chessman[pos[num + 17]]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                       // chessman[pos[num + 17]]->target = true;
                        targetCm.push_back(pos[num + 17]);
                    }
                }
                if (num < 56 && num % 8 > 1) {//????
                    if (pos[num + 6] == -1) {//????
                        //bkLabel[num + 6]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                        //bkLabel[num + 6]->target = true;
                        targetBk.push_back(num + 6);
                    }
                    else if (chessman[pos[num + 6]]->color != chessman[i]->color) {//???????
                       // chessman[pos[num + 6]]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                       // chessman[pos[num + 6]]->target = true;
                        targetCm.push_back(pos[num + 6]);
                    }
                }
                if (num < 56 && num % 8 < 6) {//????
                    if (pos[num + 10] == -1) {//????
                       // bkLabel[num + 10]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                        //bkLabel[num + 10]->target = true;
                        targetBk.push_back(num + 10);
                    }
                    else if (chessman[pos[num + 10]]->color != chessman[i]->color) {//???????
                       // chessman[pos[num + 10]]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                        //chessman[pos[num + 10]]->target = true;
                        targetCm.push_back(pos[num + 10]);
                    }
                }
                break;
            }

            case 3:     //??
            {
                num = chessman[i]->loc;
                while (num > 7 && num % 8 != 0) {//????????????
                    num -= 9;
                    if (pos[num] == -1) {//????
                       // bkLabel[num]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                       // bkLabel[num]->target = true;
                        targetBk.push_back(num);
                    }
                    else if (chessman[pos[num]]->color != chessman[i]->color) {//???????
                      //  chessman[pos[num]]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                        //chessman[pos[num]]->target = true;
                        targetCm.push_back(pos[num]);
                        break;
                    }
                    else {
                        break;
                    }
                }
                num = chessman[i]->loc;
                while (num < 56 && num % 8 != 0) {//????????????
                    num += 7;
                    if (pos[num] == -1) {//????
                       // bkLabel[num]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                        //bkLabel[num]->target = true;
                        targetBk.push_back(num);
                    }
                    else if (chessman[pos[num]]->color != chessman[i]->color) {//???????
                        //chessman[pos[num]]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                        //chessman[pos[num]]->target = true;
                        targetCm.push_back(pos[num]);
                        break;
                    }
                    else {
                        break;
                    }
                }
                num = chessman[i]->loc;
                while (num > 7 && num % 8 != 7) {//????????????
                    num -= 7;
                    if (pos[num] == -1) {//????
                        //bkLabel[num]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                        //bkLabel[num]->target = true;
                        targetBk.push_back(num);
                    }
                    else if (chessman[pos[num]]->color != chessman[i]->color) {//???????
                        //chessman[pos[num]]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                       // chessman[pos[num]]->target = true;
                        targetCm.push_back(pos[num]);
                        break;
                    }
                    else {
                        break;
                    }
                }
                num = chessman[i]->loc;
                while (num < 56 && num % 8 != 7) {//????????????
                    num += 9;
                    if (pos[num] == -1) {//????
                        //bkLabel[num]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                        //bkLabel[num]->target = true;
                        targetBk.push_back(num);
                    }
                    else if (chessman[pos[num]]->color != chessman[i]->color) {//???????
                        //chessman[pos[num]]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                        //chessman[pos[num]]->target = true;
                        targetCm.push_back(pos[num]);
                        break;
                    }
                    else {
                        break;
                    }
                }
                break;
            }
            break;
            case 4: {//??
                num = chessman[i]->loc;
                while (num > 7) {//??????????
                    num -= 8;
                    if (pos[num] == -1) {//????
                        //bkLabel[num]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                       // bkLabel[num]->target = true;
                        targetBk.push_back(num);
                    }
                    else if (chessman[pos[num]]->color != chessman[i]->color) {//???????
                        //chessman[pos[num]]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                        //chessman[pos[num]]->target = true;
                        targetCm.push_back(pos[num]);
                        break;
                    }
                    else {
                        break;
                    }
                }
                num = chessman[i]->loc;
                while (num < 56) {//??????????
                    num += 8;
                    if (pos[num] == -1) {//????
                        //bkLabel[num]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                       // bkLabel[num]->target = true;
                        targetBk.push_back(num);
                    }
                    else if (chessman[pos[num]]->color != chessman[i]->color) {//???????
                        //chessman[pos[num]]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                        //chessman[pos[num]]->target = true;
                        targetCm.push_back(pos[num]);
                        break;
                    }
                    else {
                        break;
                    }
                }
                num = chessman[i]->loc;
                while (num % 8 != 0) {//??????????
                    num -= 1;
                    if (pos[num] == -1) {//????
                        /*bkLabel[num]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                        bkLabel[num]->target = true;*/
                        targetBk.push_back(num);
                    }
                    else if (chessman[pos[num]]->color != chessman[i]->color) {//???????
                        /*chessman[pos[num]]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                        chessman[pos[num]]->target = true;*/
                        targetCm.push_back(pos[num]);
                        break;
                    }
                    else {
                        break;
                    }
                }
                num = chessman[i]->loc;
                while (num % 8 != 7) {//??????????
                    num += 1;
                    if (pos[num] == -1) {//????
                        /*bkLabel[num]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                        bkLabel[num]->target = true;*/
                        targetBk.push_back(num);
                    }
                    else if (chessman[pos[num]]->color != chessman[i]->color) {//???????
                        /*chessman[pos[num]]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                        chessman[pos[num]]->target = true;*/
                        targetCm.push_back(pos[num]);
                        break;
                    }
                    else {
                        break;
                    }
                }
                num = chessman[i]->loc;
                while (num > 7 && num % 8 != 0) {//????????????
                    num -= 9;
                    if (pos[num] == -1) {//????
                        /*bkLabel[num]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                        bkLabel[num]->target = true;*/
                        targetBk.push_back(num);
                    }
                    else if (chessman[pos[num]]->color != chessman[i]->color) {//???????
                        /*chessman[pos[num]]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                        chessman[pos[num]]->target = true;*/
                        targetCm.push_back(pos[num]);
                        break;
                    }
                    else {
                        break;
                    }
                }
                num = chessman[i]->loc;
                while (num < 56 && num % 8 != 0) {//????????????
                    num += 7;
                    if (pos[num] == -1) {//????
                        /*bkLabel[num]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                        bkLabel[num]->target = true;*/
                        targetBk.push_back(num);
                    }
                    else if (chessman[pos[num]]->color != chessman[i]->color) {//???????
                        /*chessman[pos[num]]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                        chessman[pos[num]]->target = true;*/
                        targetCm.push_back(pos[num]);
                        break;
                    }
                    else {
                        break;
                    }
                }
                num = chessman[i]->loc;
                while (num > 7 && num % 8 != 7) {//????????????
                    num -= 7;
                    if (pos[num] == -1) {//????
                        /*bkLabel[num]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                        bkLabel[num]->target = true;*/
                        targetBk.push_back(num);
                    }
                    else if (chessman[pos[num]]->color != chessman[i]->color) {//???????
                        /*chessman[pos[num]]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                        chessman[pos[num]]->target = true;*/
                        targetCm.push_back(pos[num]);
                        break;
                    }
                    else {
                        break;
                    }
                }
                num = chessman[i]->loc;
                while (num < 56 && num % 8 != 7) {//????????????
                    num += 9;
                    if (pos[num] == -1) {//????
                        /*bkLabel[num]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                        bkLabel[num]->target = true;*/
                        targetBk.push_back(num);
                    }
                    else if (chessman[pos[num]]->color != chessman[i]->color) {//???????
                        /*chessman[pos[num]]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                        chessman[pos[num]]->target = true;*/
                        targetCm.push_back(pos[num]);
                        break;
                    }
                    else {
                        break;
                    }
                }
                break;
            }
                  break;
            case 5: {//??
                num = chessman[i]->loc;
                if (num > 7) {//??????????
                    num -= 8;
                    if (pos[num] == -1) {//????
                        /*bkLabel[num]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                        bkLabel[num]->target = true;*/
                        targetBk.push_back(num);
                    }

                    else if (chessman[pos[num]]->color != chessman[i]->color) {//???????
                        /*chessman[pos[num]]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                        chessman[pos[num]]->target = true;*/
                        targetCm.push_back(pos[num]);
                    }
                }
                num = chessman[i]->loc;
                if (num < 56) {//??????????
                    num += 8;
                    if (pos[num] == -1) {//????
                        /*bkLabel[num]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                        bkLabel[num]->target = true;*/
                        targetBk.push_back(num);
                    }
                    else if (chessman[pos[num]]->color != chessman[i]->color) {//???????
                        /*chessman[pos[num]]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                        chessman[pos[num]]->target = true;*/
                        targetCm.push_back(pos[num]);
                    }
                }
                num = chessman[i]->loc;
                if (num % 8 != 0) {//??????????
                    num -= 1;
                    if (pos[num] == -1) {//????
                        /*bkLabel[num]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                        bkLabel[num]->target = true;*/
                        targetBk.push_back(num);
                    }
                    else if (chessman[pos[num]]->color != chessman[i]->color) {//???????
                        /*chessman[pos[num]]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                        chessman[pos[num]]->target = true;*/
                        targetCm.push_back(pos[num]);
                    }
                }
                num = chessman[i]->loc;
                if (num % 8 != 7) {//??????????
                    num += 1;
                    if (pos[num] == -1) {//????
                        /*bkLabel[num]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                        bkLabel[num]->target = true;*/
                        targetBk.push_back(num);
                    }
                    else if (chessman[pos[num]]->color != chessman[i]->color) {//???????
                        /*chessman[pos[num]]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                        chessman[pos[num]]->target = true;*/
                        targetCm.push_back(pos[num]);
                    }
                }
                num = chessman[i]->loc;
                if (num > 7 && num % 8 != 0) {//????????????
                    num -= 9;
                    if (pos[num] == -1) {//????
                        /*bkLabel[num]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                        bkLabel[num]->target = true;*/
                        targetBk.push_back(num);
                    }
                    else if (chessman[pos[num]]->color != chessman[i]->color) {//???????
                        /*chessman[pos[num]]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                        chessman[pos[num]]->target = true;*/
                        targetCm.push_back(pos[num]);
                    }
                }
                num = chessman[i]->loc;
                if (num < 56 && num % 8 != 0) {//????????????
                    num += 7;
                    if (pos[num] == -1) {//????
                        /*bkLabel[num]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                        bkLabel[num]->target = true;*/
                        targetBk.push_back(num);
                    }
                    else if (chessman[pos[num]]->color != chessman[i]->color) {//???????
                        /*chessman[pos[num]]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                        chessman[pos[num]]->target = true;*/
                        targetCm.push_back(pos[num]);
                    }
                }
                num = chessman[i]->loc;
                if (num > 7 && num % 8 != 7) {//????????????
                    num -= 7;
                    if (pos[num] == -1) {//????
                        /*bkLabel[num]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                        bkLabel[num]->target = true;*/
                        targetBk.push_back(num);
                    }
                    else if (chessman[pos[num]]->color != chessman[i]->color) {//???????
                        /*chessman[pos[num]]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                        chessman[pos[num]]->target = true;*/
                        targetCm.push_back(pos[num]);
                    }
                }
                num = chessman[i]->loc;
                if (num < 56 && num % 8 != 7) {//????????????
                    num += 9;
                    if (pos[num] == -1) {//????
                        /*bkLabel[num]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                        bkLabel[num]->target = true;*/
                        targetBk.push_back(num);
                    }
                    else if (chessman[pos[num]]->color != chessman[i]->color) {//???????
                        /*chessman[pos[num]]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                        chessman[pos[num]]->target = true;*/
                        targetCm.push_back(pos[num]);
                    }
                }
                num = chessman[i]->loc;//??????¦Ë
                if(!chessman[i]->moved && !isChecked && !chessman[4 + i * 2]->moved) {//???
                    if(pos[1 + i * 56] == -1 && pos[2 + i * 56] == -1 && pos[3 + i * 56] == -1) {
                        /*bkLabel[2 + i * 56]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                        bkLabel[2 + i * 56]->target = true;*/
                        targetBk.push_back(2 + i * 56);
                        isCastling = true;
                    }
                }
                if(!chessman[i]->moved && !isChecked && !chessman[5 + i * 2]->moved) {//???
                    if(pos[5 + i * 56] == -1 && pos[6 + i * 56] == -1) {
                        /*bkLabel[6 + i * 56]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                        bkLabel[6 + i * 56]->target = true;*/
                        targetBk.push_back(6 + i * 56);
                        isCastling = true;
                    }
                }
                break;
            }
            default:
                break;
            }
            checkPre(i);//??targetCm??targetBk?????
        }
        void Chess::setRouteColor() {
             for (int j : targetBk) {
                bkLabel[j]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                bkLabel[j]->target = true;
            }
            for (int j : targetCm) {
                chessman[j]->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 255);}");
                chessman[j]->target = true;
            }
        }

        void Chess::clearTargetBk() {
            for (int j : targetBk) {
                bkLabel[j]->setStyleSheet("QLabel{border:0px;}");
                bkLabel[j]->target = false;
            }
            if (!targetBk.empty()) {
                targetBk.clear();

            }
        }
        void Chess::clearTargetCm() {
            for (int j : targetCm) {
                chessman[j]->setStyleSheet("QLabel{border:0px;}");
                chessman[j]->target = false;
            }
            if (!targetCm.empty()) {
                targetCm.clear();
            }
            if (chosen != -1) {
                chessman[chosen]->setStyleSheet("QLabel{border:0px;}");
                chessman[chosen]->target = false;
                chosen = -1;
            }

        }
        void Chess::showPromote(int x, int y) {
            if(nowColor) {
                frame_promotion_w->setPoint(x, y);
            }else {
                frame_promotion_b->setPoint(x, y);
            }
        }

        QImage Chess::convertImageWhiteColorAlpha(QImage val) {
            QImage imageAlpha = val.convertToFormat(QImage::Format_RGBA8888_Premultiplied, Qt::NoFormatConversion);
            int nWidth = imageAlpha.width();
            int nHeight = imageAlpha.height();
            for (int nCol = 0; nCol < nWidth; ++nCol) {
                for (int nRow = 0; nRow < nHeight; ++nRow) {
                    QColor pixelColor = imageAlpha.pixelColor(nCol, nRow);
                    // ???????????????????????240????????????????????
                    if (pixelColor.red() > 240 && pixelColor.green() > 240 && pixelColor.blue() > 240) {
                        pixelColor.setAlpha(0);
                        imageAlpha.setPixelColor(nCol, nRow, pixelColor);
                    }
                }
            }
            return imageAlpha;
        }


