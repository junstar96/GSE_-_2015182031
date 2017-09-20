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
	battleship_point.x += x;
	battleship_point.y += y;
}



void battleship::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	// Renderer Test
	image->DrawSolidRect(battleship_point.x, battleship_point.y, 0, 8, 0.5, 0.5, 0.5, 1);

	glutSwapBuffers();
}

