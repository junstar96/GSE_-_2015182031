#pragma once
#include"stdafx.h"
#include"Renderer.h"
#include"object.h"
#include"Sound.h"
#include"timer.h"
#include<Windows.h>
#define max 100
#define object_character 1
#define object_building 2
#define object_bullet 3 
#define object_arrow 4

class SceneMgr //이 안에 오브젝트들을 집어넣고 
{
private:
	bool list[100];
	int type[100];//1 : character, 2 : building, 3 : bullet, 4 : arrow
	int num;
	object* mainobject[max];
	Renderer* Cimage = NULL;
	timer* object_time = NULL;

	GLuint m_Block_ID[2];
	GLuint background;
	GLuint sprite, bullet_image;
	GLuint fly_monster;
	GLuint soundBG;
	GLuint bullet_crash;
	GLuint snow;

	Sound* m_sound;


public:
	SceneMgr();
	~SceneMgr();

	void get_object(float x, float y, int type, int Iteam);
	void del_object();
	void del_object(int i);

	void update();

	void draw();

	void printf_point();

	void get_object_character(float x, float y, int lteam, int object_type);
	
	void cul_object(int i, int j);


};
