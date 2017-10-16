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
	int hp;//ü���� ��Ÿ��
	int mp;//����� �����ϰų� �̰ɷ� ���׷��̵带 ��Ŵ
	int atk;//attack, ���ݷ��� ��Ÿ��
	int dpp;//������ ��Ÿ��

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