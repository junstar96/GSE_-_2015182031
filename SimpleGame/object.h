#pragma once
#include"stdafx.h"
#include"Renderer.h"
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"



struct vect  // 1은 y = 위쪽, x = 오른쪽, 2는 y = 아래쪽, x = 왼쪽
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