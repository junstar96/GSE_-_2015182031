#include"stdafx.h"
#include"battleship_basic.h"



battleship::battleship()
{
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

	image = new Renderer(1000, 1000);
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
	battleship_point.x += x;
	battleship_point.y += y;
}



void battleship::draw()
{
	

	// Renderer Test
	image->DrawSolidRect(battleship_point.x, battleship_point.y, 0, 8, 0.5, 0.5, 0.5, 1);


}

