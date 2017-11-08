#include"stdafx.h"
#include"SceneMgr.h"
#include<Windows.h>
#include"Mmsystem.h"
#pragma comment(lib, "winmm.lib")

float start_time;

SceneMgr::SceneMgr()
{
	Cimage = new Renderer(500, 500);
	start_time = (float)timeGetTime()*0.001f;
	m_Block_ID = Cimage->CreatePngTexture("./resource/perfect_first.PNG");
	type[0] = object_building;
	mainobject[0] = new object(0, 0, type[0]);
	list[0] = true;
	num = 1;
}

SceneMgr::SceneMgr(int get_num) : num(get_num)
{
	Cimage = new Renderer(500, 500);
	start_time = (float)timeGetTime()*0.001f;
	type[0] = object_building;
	mainobject[0] = new object(0, 0, type[0]);
	m_Block_ID = Cimage->CreatePngTexture("./resource/perfect_first.PNG");

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
	printf("전부 삭제\n");
}

void SceneMgr::update()
{
	float time = timeGetTime()*0.001f;
	float bullet_flag = time - start_time;
	static float time_cut = 0;

	printf("%f\n", bullet_flag - (float)time_cut);
	

	for (int i = 0; i < num; ++i)
	{
		if (list[i])
		{
			switch (type[i])
			{
			case object_character:
				if (bullet_flag - time_cut >= 0.5)
				{
					get_object(mainobject[i]->set_x() + 4.0, mainobject[i]->set_y()+ 4.0, object_arrow);
				}
				break;
			case object_building:
				if (bullet_flag - time_cut>= 0.5)
				{
					get_object(mainobject[i]->set_x(), mainobject[i]->set_y(), object_bullet);
				}
				break;
			}
		}
	}
	
	if (bullet_flag - time_cut>= 0.5)
	{
		time_cut += 0.5;
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
				if (list[i] == true&&list[j] == true)
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
				Cimage->DrawSolidRect((float)mainobject[i]->set_x(), (float)mainobject[i]->set_y(), 0, 8, 1.0f, 1.0f, 1.0f, 1);
				break;
			case object_building:
				Cimage->DrawTexturedRect((float)mainobject[i]->set_x(), (float)mainobject[i]->set_y(), 0, 80, 0.0f, 1.0f, 0.0f, 0, 
					m_Block_ID);
				break;
			case object_bullet:
				Cimage->DrawSolidRect((float)mainobject[i]->set_x(), (float)mainobject[i]->set_y(), 0, 2, 1.0f, 0.0f, 0.0f, 1);
				break;
			case object_arrow:
				Cimage->DrawSolidRect((float)mainobject[i]->set_x(), (float)mainobject[i]->set_y(), 0, 2, 0.0f, 1.0f, 0.0f, 1);
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

	switch (type[i])
	{
	case object_character:
		switch (type[j])
		{
		case object_character:
			break;
		case object_building:
			break;
		case object_bullet:
		case object_arrow:
			if (-8 < ix - jx && ix - jx < 8)
			{
				if (-8 < iy - jy && iy - jy < 8)
				{
					mainobject[i]->minus_life(mainobject[j]->set_life());
					mainobject[j]->minus_life(mainobject[j]->set_life());
				}
			}
			break;
		}
		break;
	case object_building:
		switch (type[j])
		{
		case object_character:
			if (-40 < ix - jx && ix - jx < 40)
			{
				if (-40 < iy - jy && iy - jy < 40)
				{
					mainobject[i]->minus_life(mainobject[j]->set_life());
					mainobject[j]->minus_life(mainobject[j]->set_life());
				}
			}
			break;
		case object_building:
			break;
		case object_bullet:
			break;
		case object_arrow:
			if (-40 < ix - jx && ix - jx < 40)
			{
				if (-40 < iy - jy && iy - jy < 40)
				{
					mainobject[i]->minus_life(mainobject[j]->set_life());
					mainobject[j]->minus_life(mainobject[j]->set_life());
				}
			}
			break;
		}
	case object_bullet:
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
		case object_bullet:
			break;
		case object_arrow:
			break;
		}
		break;
	case object_arrow:
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
			if (-25 < ix - jx && ix - jx < 25)
			{
				if (-25 < iy - jy && iy - jy < 25)
				{
					mainobject[i]->minus_life(mainobject[j]->set_life());
					mainobject[j]->minus_life(mainobject[j]->set_life());
				}
			}
			break;
		case object_bullet:
			break;
		case object_arrow:
			break;
		}
		break;
	}
	
	
	if (mainobject[i]->set_life() <= 0)
		del_object(i);

	if (mainobject[j]->set_life() <= 0)
		del_object(j);
	
}


