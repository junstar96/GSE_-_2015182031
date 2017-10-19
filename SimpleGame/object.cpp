#include"stdafx.h"
#include"object.h"

object::object()
{
	image = new Renderer(500, 500);
	x = 400;
	y = 300;
	v.x = 1;
	v.y = 1;
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
		x += 5.0;
		break;
	case 2:
		x -= 5.0;
		break;
	default:
		break;
	}

	

	switch (v.y)
	{
	case 1:
		y += 5.0;
		break;
	case 2:
		y -= 5.0;
		break;
	default:
		break;
	}

	

}

void object::draw()
{

	// Renderer Test
	image->DrawSolidRect(x, y, 0.0, 8, 1.0, 1.0, 1.0, 1);
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
		x += 5.0;
		break;
	case 2:
		x -= 5.0;
		break;
	default:
		break;
	}



	switch (v.y)
	{
	case 1:
		y += 5.0;
		break;
	case 2:
		y -= 5.0;
		break;
	default:
		break;
	}


}

void object::crash_object(object* there)
{
	switch (there->v.x)
	{
	case 1:
		if (v.x == 2)
		{
			int temp = sqrt((x - there->x)*(x - there->x) + (y - there->y)*(y - there->y));

			if (temp < 2)
			{
				there->v.x = 2;
				v.x = 1;
			}
		}
		break;
	case 2:
		if (v.x == 1)
		{
			int temp = sqrt((x - there->x)*(x - there->x) + (y - there->y)*(y - there->y));

			if (temp < 2)
			{
				there->v.x = 1;
				v.x = 2;
			}
		}
		break;
	}


	switch (there->v.y)
	{
	case 1:
		if (v.y == 2 && there->x - 2 < x && x < there->x + 2)
		{
			there->v.y = 2;
			v.y = 1;
		}
		break;
	case 2:
		if (v.y == 1 && there->x - 2 < x && x < there->x + 2)
		{
			there->v.y =  1;
			v.y = 2;
		}
		break;
	}
}

void object::printf_point()
{
	printf("%lf %lf, vec = %d %d\n", x, y, v.x, v.y);
	
}