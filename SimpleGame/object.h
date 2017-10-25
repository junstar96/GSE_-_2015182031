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
	int color_num;
	double x;
	double y;
	double speed;
	float time;
	float life;
	vect v;
	

public:
	object();
	object(float x, float y);
	~object();
	
	void move_object();

	void get_object(int x, int y);

	void update(float get_time);

	

	void printf_point();

	void const get_vec_x(int vec);
	void const get_vec_y(int vec);

	double set_x() const;
	double set_y() const;

	int set_vec_x() const;
	int set_vec_y() const;

	void const get_col(int col)
	{
		color_num = col;
	}

	int set_col() const
	{
		return color_num;
	}

	float set_time() const
	{
		return time;
	}

	float set_life() const
	{
		return life;
	}
};