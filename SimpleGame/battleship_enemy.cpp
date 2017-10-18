#include"stdafx.h"
#include"battleship_enemy.h"

enemy::enemy() : battleship()
{

}

enemy::enemy(float x, float y, int type, int item_type) : battleship(x, y), type(type), item_type(item_type)
{
	vect_x = rand() % 2 + 1;
	vect_y = rand() % 2 + 1;
}

void enemy::move(float x, float y)
{
	battleship_point.x += x * speed;
	battleship_point.y += y * speed;
}

void enemy::draw()
{
	image->DrawSolidRect(battleship_point.x, battleship_point.y, 0, 8, 0.5, 0.5, 0.5, 1);
}

void enemy::update()
{
	if (speed > 2)
	{
		speed += 0.002;
	}


	if (battleship_point.x >= 250.0)
	{
		vect_x = 2;
	}
	else if (battleship_point.x <= -250.0)
	{
		vect_x = 1;
	}

	if (battleship_point.y >= 250.0)
	{
		vect_y = 2;
	}
	else if (battleship_point.y <= -250.0)
	{
		vect_y = 1;
	}



	switch (vect_x)
	{
	case 1:
		battleship_point.x += 5.0*speed;
		break;
	case 2:
		battleship_point.x -= 5.0*speed;
		break;
	default:
		break;
	}



	switch (vect_y)
	{
	case 1:
		battleship_point.y += 5.0*speed;
		break;
	case 2:
		battleship_point.y -= 5.0*speed;
		break;
	default:
		break;
	}



}

