#include"stdafx.h"
#include"SceneMgr.h"
#include<Windows.h>
#include"Mmsystem.h"
#pragma comment(lib, "winmm.lib")

float start_time;

SceneMgr::SceneMgr()
{
	image = new Renderer(500, 500);
	num = 0;
}

SceneMgr::SceneMgr(int get_num) : num(get_num)
{
	image = new Renderer(500, 500);
	start_time = (float)timeGetTime()*0.001f;
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
			list[i] = false;
			
		}
	}
	printf("전부 삭제\n");
}

void SceneMgr::update()
{
	float time = timeGetTime()*0.001f;
	printf("%f\n", time-start_time);
	for (int i = 0; i <= num; ++i)
	{
		if (list[i] == true)
		{
			mainobject[i]->update(time-start_time);
			mainobject[i]->get_col(0);
		}
	}

	for (int i = 0; i <= num; ++i)
	{

		if (list[i] == true)
		{
			for (int j = i + 1; j <= num; ++j)
			{
				if (list[j] == true)
				{
					cul_object(i, j);
					
				}
				
				if (mainobject[i]->set_col() == 1)
				{
					break;
				}
			}
		}

		
	}


	for (int i = 0; i < num; ++i)
	{
		
		if (mainobject[i]->set_life() <= 0)
		{
			
			del_object(i);
		}
	}
}

void SceneMgr::draw()
{
	for (int i = 0; i <= num; ++i)
	{
		if (list[i] == true)
		{
			switch (mainobject[i]->set_col())
			{
			case 0:
				
					image->DrawSolidRect(mainobject[i]->set_x(), mainobject[i]->set_y(), 0, 8, 1.0f, 1.0f, 1.0f, 1);
				break;
			case 1:
				
					image->DrawSolidRect(mainobject[i]->set_x(), mainobject[i]->set_y(), 0, 8, 1.0f, 0.0f, 0.0f, 1);
				break;
			}
		}
	}
}


void SceneMgr::get_object(float x, float y)
{
	int tmp = 0;

	for (int i = 0; i < num; ++i)
	{
		if (!list[i])
		{
			mainobject[i] = new object(x, y);
			list[i] = true;
			break;
		}
	}

	if (tmp != num)
	{
		return;
	}

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

void SceneMgr::del_object(int i)
{
	if (list[i])
	{
		delete mainobject[i];
		list[i] = false;
	}
}

void SceneMgr::printf_point()
{
	for (int i = 0; i < num; ++i)
	{
		printf("%d째 점 : \n", i);
		mainobject[i]->printf_point();
	}
}

void SceneMgr::cul_object(int i, int j)
{
	
	double ix = mainobject[i]->set_x();
	double iy = mainobject[i]->set_y();
	double jx = mainobject[j]->set_x();
	double jy = mainobject[j]->set_y();

	if (-8 < ix - jx && ix - jx < 8)
	{
		if (-8 < iy - jy && iy - jy < 8)
		{
			mainobject[i]->get_col(1);
			mainobject[j]->get_col(1);
		}
	}
	
}

void SceneMgr::crash_object(int i, int j)
{
	int vxi = mainobject[i]->set_vec_x();
	int vxj = mainobject[j]->set_vec_x();
	int vyi = mainobject[i]->set_vec_y();
	int vyj = mainobject[j]->set_vec_y();

	double ix = mainobject[i]->set_x();
	double iy = mainobject[i]->set_y();
	double jx = mainobject[j]->set_x();
	double jy = mainobject[j]->set_y();

	switch (vxi)
	{
	case 1:
		if (vxj == 2)
		{
			if (ix <= jx - 2.0 && jx <= ix + 4.0)
			{
				if (jy - 4.0 <= iy && iy <= jy + 4.0)
				{
					mainobject[i]->get_vec_x(2);
					mainobject[j]->get_vec_x(1);

					printf("x 값 %d %d 충돌 \n", i, j);
				}
			}
		}
		break;
	case 2:
		if (vxj == 1)
		{
			if (jx <= ix - 2.0 && ix < jx + 4.0)
			{
				if (jy - 4.0 <= iy && iy <= jy + 4.0)
				{
					mainobject[i]->get_vec_x(1);
					mainobject[j]->get_vec_x(2);

					printf("x값 %d %d 충돌 \n", i, j);
				}
			}
		}
		break;
	}

	switch (vyi)
	{
	case 1:
		if (vyj == 2)
		{
			if (iy <= jy && jy <= iy + 10.0)
			{
				if (jx - 4.0 <= ix && ix <= jx + 4.0)
				{
					mainobject[i]->get_vec_y(2);
					mainobject[j]->get_vec_y(1);

					printf("y값 %d %d 충돌 \n", i, j);
				}
			}
		}
		break;
	case 2:
		if (vyj == 1)
		{
			if (jy <= iy && iy < jy + 10.0)
			{
				if (jx - 4.0 <= ix && ix <= jx + 4.0)
				{
					mainobject[i]->get_vec_y(1);
					mainobject[j]->get_vec_y(2);

					printf("y값 %d %d 충돌 \n", i, j);
				}
			}
		}
		break;
	}
}