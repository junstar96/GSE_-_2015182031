#include"stdafx.h"
#include"object.h"

object::object()
{
	time = 0;
	life = 100.0;
	x = 400;
	y = 300;
	v.x = cos((float)(rand()%361 - 180)*0.01f);
	v.y = sin((float)(rand()%361 - 180)*0.01f);
	speed = 1;
	color_num = 0;
	
}

object::object(double x, double y, int type, int get_team) : x(x), y(y), Iteam(get_team)
{
	
	speed = 1.0;
	time = 0;
	v.x = cos((float)(rand())*0.01f);
	v.y = sin((float)(rand())*0.01f);
	color_num = 0;
	switch (type)
	{
	case 1:
		life = 100;
		break;
	case 2:
		life = 500;
		break;
	case 3:
		life = 20;
		break;
	case 4:
		life = 10;
		break;
	}

	
}


object::~object()
{
	printf("삭제당함\n");
}

void object::get_object(int x, int y)
{

}


void object::update(float get_time, int type)
{
	switch (type)
	{
	case 1:

		if (x >= x_size/2)
		{
			v.x = v.x * (-1);
		}
		else if (x <= -(x_size)/2)
		{
			v.x = v.x * (-1);
		}

		if (y >= y_size/2)
		{
			v.y = v.y *(-1);
		}
		else if (y <= -(y_size/2))
		{
			v.y = v.y *(-1);
		}



		x = x  + speed * v.x;
		y = y + speed * v.y;

		time = get_time;
		speed = 5;
		break;
	case 2:
		break;
	case 3:
		
		if (x >= x_size/2)
		{
			life = 0;
		}
		else if (x <= -(x_size/2))
		{
			life = 0;
		}

		if (y >= y_size/2)
		{
			life = 0;
		}
		else if (y <= -(y_size/2))
		{
			life = 0;
		}



	

		x = x + speed * v.x;
		y = y + speed * v.y;

		speed = 10;
		break;
	case 4:

		if (x >= x_size / 2)
		{
			life = 0;
		}
		else if (x <= -(x_size / 2))
		{
			life = 0;
		}

		if (y >= y_size / 2)
		{
			life = 0;
		}
		else if (y <= -(y_size / 2))
		{
			life = 0;
		}

		





		x = x + speed * v.x;
		y = y + speed * v.y;

		speed = 10;
		break;
	}
}

void object::printf_point()
{
	
}

void const object::get_vec_x(float vec)
{
	v.x = vec;
}

void const object::get_vec_y(float vec)
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

float object::set_vec_x() const
{
	return v.x;
}

float object::set_vec_y() const
{
	return v.y;
}