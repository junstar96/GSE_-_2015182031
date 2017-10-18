#include"stdafx.h"
#include"battleship_basic.h"



battleship::battleship()
{
	battleship_point.x = 0;
	battleship_point.y = 0;
	stat.atk = 0;
	stat.dpp = 0;
	stat.hp = 0;
	stat.mp = 0;

	speed = 1.0;
	image = new Renderer(500, 500);
	if (!image->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}
}

battleship::battleship(float x, float y)
{
	battleship_point.x = x;
	battleship_point.y = y;
	stat.atk = 10;
	stat.dpp = 10;
	stat.hp = 10;
	stat.mp = 10;

	speed = 1.0;

	image = new Renderer(500, 500);
	if (!image->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}
}

battleship::~battleship()
{
	delete image;
}

void battleship::move(float x, float y)
{
	battleship_point.x += x * speed;
	battleship_point.y += y * speed;
}

void battleship::update()
{
	if (speed < 5.0)
	{
		speed += 0.01;
	}
}



void battleship::draw()
{
	// Renderer Test
	image->DrawSolidRect(battleship_point.x, battleship_point.y, 0, 8, 0.5, 0.5, 0.5, 1);
}

