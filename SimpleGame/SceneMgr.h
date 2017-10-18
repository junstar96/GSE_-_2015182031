#pragma once
#include"stdafx.h"
#include"object.h"
#define max 100


class SceneMgr //이 안에 오브젝트들을 집어넣고 
{
private:
	bool list[100];
	int num;
	object** mainobject = NULL;
public:
	SceneMgr();
	SceneMgr(int num);
	~SceneMgr();

	void get_object();
	void del_object();

	void draw();

};