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

object::object(float x, float y, int type) : x(x), y(y)
{
	
	speed = 1.0;
	time = 0;
	v.x = cos((float)(rand() % 361 - 180)*0.01f);
	v.y = sin((float)(rand() % 361 - 180)*0.01f);
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
		life = 40;
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



	

	

}



void object::update(float get_time, int type)
{
	switch (type)
	{
	case 1:

		if (x >= 250.0)
		{
			v.x = v.x * (-1);
		}
		else if (x <= -250.0)
		{
			v.x = v.x * (-1);
		}

		if (y >= 250.0)
		{
			v.y = v.y *(-1);
		}
		else if (y <= -250.0)
		{
			v.y = v.y *(-1);
		}



		x = x  + speed * v.x;
		y = y + speed * v.y;

		time = get_time;
		speed = 1.0 * (1.0 + time);
		//life -= 1; , 이거 그 때 라이프타임
		break;
	case 2:
		break;
	case 3:
		
		if (x >= 250.0)
		{
			life = 0;
		}
		else if (x <= -250.0)
		{
			life = 0;
		}

		if (y >= 250.0)
		{
			life = 0;
		}
		else if (y <= -250.0)
		{
			life = 0;
		}



	

		x = x + speed * v.x;
		y = y + speed * v.y;

		speed = 20;
		break;
	case 4:
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