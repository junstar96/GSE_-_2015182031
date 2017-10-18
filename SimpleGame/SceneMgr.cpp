#include"stdafx.h"
#include"SceneMgr.h"


SceneMgr::SceneMgr()
{
	num = 0;
}

SceneMgr::SceneMgr(int get_num) : num(get_num)
{
	mainobject = new object*[max];
	for (int i = 0; i < num; ++i)
	{
		mainobject[i] = new object((float)(rand()%500 - 250), (float)(rand()%500 - 250));
		list[i] = true;
	}
}

SceneMgr::~SceneMgr()
{
	for (int i = 0; i < num; ++i)
	{
		if (list[i] == true)
		{
			delete mainobject[i];
		}
	}
}

void SceneMgr::draw()
{
	for (int i = 0; i < num; ++i)
	{
		if (list[i] == true)
		{
			mainobject[i]->draw();
		}
	}
}


void SceneMgr::get_object()
{
	if (num < max - 1)
	{
		num += 1;
		mainobject[num] = new object();
	}
}

void SceneMgr::del_object()
{
	if (num > 0)
	{
		delete mainobject[num];
		list[num] = false;
		num -= 1;
	}
}
