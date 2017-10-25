#include"stdafx.h"
#include"object.h"

object::object()
{
	time = 0;
	life = 100.0;
	x = 400;
	y = 300;
	v.x = 1;
	v.y = 1;
	speed = 1;
	color_num = 0;
	
}

object::object(float x, float y) : x(x), y(y)
{
	
	speed = 1.0;
	time = 0;
	life = 100.0;
	v.x = rand() % 2 + 1;
	v.y = rand() % 2 + 1;
	color_num = 0;
}


object::~object()
{
	printf("삭제당함\n");
}

void object::get_object(int x, int y)
{

}

void object::move_object()
{
	
	if (x >= 500.0)
	{
		v.x = 2;
	}
	else if (x <= -500.0)
	{
		v.x = 1;
	}

	if (y >= 500.0)
	{
		v.y = 2;
	}
	else if (y <= -500.0)
	{
		v.y = 1;
	}



	switch (v.x)
	{
	case 1:
		x += 1.0;
		break;
	case 2:
		x -= 1.0;
		break;
	default:
		break;
	}

	

	switch (v.y)
	{
	case 1:
		y += 1.0;
		break;
	case 2:
		y -= 1.0;
		break;
	default:
		break;
	}

	

}



void object::update(float get_time)
{
		if (x >= 250.0)
		{
			v.x = 2;
		}
		else if (x <= -250.0)
		{
			v.x = 1;
		}

		if (y >= 250.0)
		{
			v.y = 2;
		}
		else if (y <= -250.0)
		{
			v.y = 1;
		}



		switch (v.x)
		{
		case 1:
			x += 1.0*speed;
			break;
		case 2:
			x -= 1.0*speed;
			break;
		default:
			break;
		}



		switch (v.y)
		{
		case 1:
			y += 1.0*speed;
			break;
		case 2:
			y -= 1.0*speed;
			break;
		default:
			break;
		}

		time = get_time;
		speed = 1.0 * (1.0+time);
		life -= 1;
}

void object::printf_point()
{
	printf("%lf %lf, vec = %d %d\n", x, y, v.x, v.y);
	
}

void const object::get_vec_x(int vec)
{
	v.x = vec;
}

void const object::get_vec_y(int vec)
{
	v.y = vec;
}

double object::set_x() const
{
	return x;
}

double object::set_y() const
{
	return y;
}

int object::set_vec_x() const
{
	return v.x;
}

int object::set_vec_y() const
{
	return v.y;
}