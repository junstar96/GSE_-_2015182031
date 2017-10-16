#pragma once

#include"battleship_basic.h"

class enemy : public battleship
{
protected:
	int type;
	int item_type;//0 : 아무것도 가지지 않았다, 
	int vect_x;
	int vect_y;
public:
	enemy();
	enemy(float x, float y, int type, int item_type);


	virtual void move(float x, float y);
	virtual void draw();
	virtual void update();
};