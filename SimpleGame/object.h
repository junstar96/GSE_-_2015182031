#pragma once
#include"stdafx.h"
#include"Renderer.h"
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"
#define py 3.14159265

#define team_nt 1
#define team_ws 2



struct vect  // 1�� y = ����, x = ������, 2�� y = �Ʒ���, x = ����
{
	float x;
	float y;
};

class object
{
protected:
	int color_num;
	double x;
	double y;
	double speed;
	float time;
	int life;
	int Iteam;//���� �����ϱ� ���� ����
	vect v;
	int object_type;

public:
	object();
	object(double x, double y, int type, int get_team);
	~object();
	

	void get_object(int x, int y);

	void update(float get_time, int type);

	

	void printf_point();

	void const get_vec_x(float vec);
	void const get_vec_y(float vec);

	double set_x() const;
	double set_y() const;

	float set_vec_x() const;
	float set_vec_y() const;

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

	int set_life() const
	{
		return life;
	}

	void minus_life(const int a_life)
	{
		life -= a_life;
	}

	int set_Iteam() const
	{
		return Iteam;
	}

	float set_speed_x() const
	{
		return v.x * speed;
	}

	float set_speed_y() const
	{
		return v.y * speed;
	}

	void get_object_type(const int type)
	{
		object_type = type;
	}

	int set_object_type() const
	{
		return object_type;
	}

};