#pragma once
#include"stdafx.h"
#include"Renderer.h"
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

struct point
{
	double x;
	double y;

};

struct status
{
	int hp;//체력을 나타냄
	int mp;//기술을 구현하거나 이걸로 업그레이드를 시킴
	int atk;//attack, 공격력을 나타냄
	int dpp;//방어력을 나타냄

};

class battleship
{
protected:
	point battleship_point;
	status stat;
	Renderer* image = NULL;
	float speed;

public:
	battleship();
	battleship(float x, float y);
	~battleship();


	virtual void move(float x, float y);
	virtual void draw();
	virtual void update();
};