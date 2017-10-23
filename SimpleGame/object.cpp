#include"stdafx.h"
#include"object.h"

object::object()
{
	image = new Renderer(500, 500);
	x = 400;
	y = 300;
	v.x = 1;
	v.y = 1;
	color_num = 0;
	if (!image->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}
}

object::object(float x, float y) : x(x), y(y)
{
	image = new Renderer(500, 500);
	v.x = rand() % 2 + 1;
	v.y = rand() % 2 + 1;
	color_num = 0;
}


object::~object()
{
	delete image;
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

void object::draw()
{

	// Renderer Test
	switch (color_num)
	{
	case 0:
		image->DrawSolidRect(x, y, 0.0, 8, 1.0, 1.0, 1.0, 1);
		break;
	case 1:
		image->DrawSolidRect(x, y, 0.0, 8, 1.0, 0.0, 0.0, 1);
		break;
	}
	
}

void object::update()
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