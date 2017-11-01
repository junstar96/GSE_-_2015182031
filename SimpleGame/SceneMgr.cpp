#include"stdafx.h"
#include"SceneMgr.h"
#include<Windows.h>
#include"Mmsystem.h"
#pragma comment(lib, "winmm.lib")

float start_time;

SceneMgr::SceneMgr()
{
	image = new Renderer(500, 500);
	start_time = (float)timeGetTime()*0.001f;

	type[0] = object_building;
	mainobject[0] = new object(0, 0, type[0]);
	list[0] = true;
	num = 1;
}

SceneMgr::SceneMgr(int get_num) : num(get_num)
{
	image = new Renderer(500, 500);
	start_time = (float)timeGetTime()*0.001f;
	type[0] = object_building;
	mainobject[0] = new object(0, 0, type[0]);
	
	for (int i = 1; i < num; ++i)
	{
		type[i] = object_character;
		mainobject[i] = new object((float)(rand()%500 - 250), (float)(rand()%500 - 250), type[i]);
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
			list[i] = false;
			
		}
	}
	printf("���� ����\n");
}

void SceneMgr::update()
{
	float time = timeGetTime()*0.001f;
	float bullet_flag = time - start_time;

	printf("%f\n", cos(bullet_flag));

	if (bullet_flag >= 0.5)
	{
		get_object(0, 0, object_bullet);
	}

	for (int i = 0; i < num; ++i)
	{
		if (list[i] == true)
		{
			mainobject[i]->update(time-start_time, type[i]);
			mainobject[i]->get_col(0);
		}
	}

	for (int i = 0; i < num; ++i)
	{

		if (list[i] == true)
		{
			for (int j = i + 1; j < num; ++j)
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
	for (int i = 0; i < num; ++i)
	{
		if (list[i] == true)
		{
			switch (type[i])
			{
			case object_character:
				image->DrawSolidRect((float)mainobject[i]->set_x(), (float)mainobject[i]->set_y(), 0, 8, 1.0f, 1.0f, 1.0f, 1);
				break;
			case object_building:
				image->DrawSolidRect((float)mainobject[i]->set_x(), (float)mainobject[i]->set_y(), 0, 50, 1.0f, 1.0f, 0.0f, 1);
				break;
			case object_bullet:
				image->DrawSolidRect((float)mainobject[i]->set_x(), (float)mainobject[i]->set_y(), 0, 2, 1.0f, 0.0f, 0.0f, 1);
				break;
			case object_arrow:
				break;
			}
			
		}
	}
}


void SceneMgr::get_object(float x, float y, int get_type)
{
	int tmp = 0;

	for (int i = 0; i < num; ++i)
	{
		if (!list[i])
		{
			type[i] = get_type;
			mainobject[i] = new object(x, y, type[i]);
			list[i] = true;
			
			break;
		}
		else
		{
			tmp += 1;
		}
	}

	if (tmp != num)
	{
		return;
	}
	else if (tmp == num && num < max - 1)
	{
		type[num] = get_type;
		mainobject[num] = new object(x, y, type[num]);
		list[num] = true;
	
		num += 1;
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
		printf("%d° �� : \n", i);
		mainobject[i]->printf_point();
	}
}

void SceneMgr::cul_object(int i, int j)
{
	
	double ix = mainobject[i]->set_x();
	double iy = mainobject[i]->set_y();
	double jx = mainobject[j]->set_x();
	double jy = mainobject[j]->set_y();

	switch (type[i])
	{
	case object_character:
		switch (type[j])
		{
		case object_character:
			if (-4 < ix - jx && ix - jx < 4)
			{
				if (-4 < iy - jy && iy - jy < 4)
				{
					mainobject[i]->get_col(1);
					mainobject[j]->get_col(1);
				}
			}
			break;
		case object_building:
			break;
			
		}
		break;
	case object_building:
		switch (type[j])
		{
		case object_character:
			if (-25 < ix - jx && ix - jx < 25)
			{
				if (-25 < iy - jy && iy - jy < 25)
				{
					mainobject[i]->minus_life(mainobject[j]->set_life());
					mainobject[j]->minus_life(mainobject[j]->set_life());
				}
			}
			break;
		case object_building:
			break;
		}
		break;
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

					printf("x �� %d %d �浹 \n", i, j);
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

					printf("x�� %d %d �浹 \n", i, j);
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

					printf("y�� %d %d �浹 \n", i, j);
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

					printf("y�� %d %d �浹 \n", i, j);
				}
			}
		}
		break;
	}
}

