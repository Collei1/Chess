#pragma once
#include"../MyLabel/myLabel.h"

class Chessman :public LabelButton {

	Q_OBJECT

public:
	Chessman(QWidget* parent, int color, int type);
	void promote(int type);
	bool choose = false;
	bool moved = false;
	int type;
	int color;
	int loc{};
};