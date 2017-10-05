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
#include "object.h"

Renderer *g_Renderer = NULL;
battleship* prototype = NULL;
object* testobject = NULL;

void RenderScene(void)
{
	//// Renderer Test
	//g_Renderer->DrawSolidRect(0, 0, 0, 4, 1, 0, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);


	prototype->draw();
	testobject->draw();


	glutSwapBuffers();
	
}

void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{

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

	glutTimerFunc(30, timer, 1);
}

int main(int argc, char **argv)
{
	

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

	return 0;
}

