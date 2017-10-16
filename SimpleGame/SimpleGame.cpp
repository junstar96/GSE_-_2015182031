/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include "Renderer.h"

#include "battleship_basic.h"
#include "battleship_enemy.h"
#include "object.h"

Renderer *g_Renderer = NULL;
battleship* prototype = NULL;
object* testobject = NULL;
enemy** testenemy = NULL;
int enemy_num;

void RenderScene(void)
{
	//// Renderer Test
	//g_Renderer->DrawSolidRect(0, 0, 0, 4, 1, 0, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);


	prototype->draw();
	testobject->draw();
	for (int i = 0; i < enemy_num; ++i)
	{
		testenemy[i]->draw();
		
	}



	glutSwapBuffers();

}

void Idle(void)
{
	RenderScene();

	prototype->update();
}

void MouseInput(int button, int state, int x, int y)
{
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_UP)
		{
			printf("%d %d \n", x, y);
			if (enemy_num < 10)
			{
				testenemy[enemy_num] = new enemy(-x + 250.0, -y + 250.0, 1, 1);
				enemy_num += 1;
			}
		}
		break;
	}
}

void KeyInput(unsigned char key, int x, int y)
{

	switch (key)
	{
	case 'a':
	case 'A':

		prototype->move(-5.0, 0);

		break;

	case 'd':
	case 'D':
		prototype->move(5.0, 0);
		break;

	case 'w':
	case 'W':
		prototype->move(0, 5.0);
		break;
	case 's':
	case 'S':
		prototype->move(0, -5.0);
	}
}

void SpecialKeyInput(int key, int x, int y)
{
}

void timer(int value)
{
	testobject->move_object();
	for (int i = 0; i < enemy_num; ++i)
	{
		testenemy[i]->update();
	}
	glutTimerFunc(30, timer, 1);
}

int main(int argc, char **argv)
{
	enemy_num = 0;

	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Game Software Engineering KPU");

	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}

	// Initialize Renderer
	g_Renderer = new Renderer(500, 500);
	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}
	prototype = new battleship(0, 0);

	testobject = new object();

	testenemy = new enemy*[10];

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);
	glutTimerFunc(30, timer, 1);

	glutMainLoop();

	delete g_Renderer;
	delete prototype;
	delete testobject;

	for (int i = 0; i < enemy_num; ++i)
	{
		delete testenemy[i];
	}
	delete testenemy;

	return 0;
}

