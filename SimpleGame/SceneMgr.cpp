#include"stdafx.h"
#include"SceneMgr.h"


SceneMgr::SceneMgr()
{
	num = 0;
}

SceneMgr::SceneMgr(int get_num) : num(get_num)
{
	for (int i = 0; i < num; ++i)
	{
		mainobject[i] = new object((float)(rand()%500 - 250), (float)(rand()%500 - 250));
		list[i] = true;
	}
}

SceneMgr::~SceneMgr()
{
	for (int i = 0; i <= num; ++i)
	{
		if (list[i] == true)
		{
			delete mainobject[i];
		}
	}
}

void SceneMgr::update()
{
	for (int i = 0; i <= num; ++i)
	{
		if (list[i] == true)
		{
			mainobject[i]->update();
		}
	}

	for (int i = 0; i <= num; ++i)
	{
		if (list[i] == true)
		{
			for (int j = i; j <= num; ++j)
			{
				if (list[j] == true)
				{
					mainobject[i]->crash_object(mainobject[j]);
				}
			}
		}
	}
}

void SceneMgr::draw()
{
	for (int i = 0; i <= num; ++i)
	{
		if (list[i] == true)
		{
			mainobject[i]->draw();
		}
	}
}


void SceneMgr::get_object(float x, float y)
{
	if (num < max - 1)
	{
		num += 1;
		mainobject[num] = new object(x, y);
		list[num] = true;
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

void SceneMgr::printf_point()
{
	for (int i = 0; i < num; ++i)
	{
		printf("%dÂ° Á¡ : \n", i);
		mainobject[i]->printf_point();
	}
}