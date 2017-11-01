#pragma once
#include"stdafx.h"
#include"Renderer.h"
#include"object.h"
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
	Renderer* image = NULL;
public:
	SceneMgr();
	SceneMgr(int num);
	~SceneMgr();

	void get_object(float x, float y, int type);
	void del_object();
	void del_object(int i);

	void update();

	void draw();

	void printf_point();

	void crash_object(int i, int j);
	void cul_object(int i, int j);

};