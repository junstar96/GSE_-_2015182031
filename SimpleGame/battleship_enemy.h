#pragma once

#include"battleship_basic.h"

class enemy : public battleship
{
protected:
	int type;
	int item_type;//0 : �ƹ��͵� ������ �ʾҴ�, 
public:
	enemy();
	enemy(float x, float y, int type, int item_type);


	virtual void move(float x, float y);
	virtual void draw();

};