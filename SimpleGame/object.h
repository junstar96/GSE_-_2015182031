#pragma once
#include"stdafx.h"
#include"Renderer.h"
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"



struct vect  // 1�� y = ����, x = ������, 2�� y = �Ʒ���, x = ����
{
	int x;
	int y;
};

class object
{
protected:
	int type; 
	float x;
	float y;
	vect v;
	Renderer* image = NULL;

public:
	object();
	~object();
	
	void move_object();

	void draw();

	void get_object(int x, int y);

};