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
	double x;
	double y;
	double speed;
	vect v;
	Renderer* image = NULL;

public:
	object();
	object(float x, float y);
	~object();
	
	void move_object();

	void draw();

	void get_object(int x, int y);

	void update();

	

	void printf_point();

	void const get_vec_x(int vec);
	void const get_vec_y(int vec);

	double set_x() const;
	double set_y() const;

	int set_vec_x() const;
	int set_vec_y() const;
};