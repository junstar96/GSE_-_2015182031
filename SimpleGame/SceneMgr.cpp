#include"stdafx.h"
#include"SceneMgr.h"
#include<Windows.h>
#include"Mmsystem.h"
#pragma comment(lib, "winmm.lib")

float start_time;

#define character_half 30
#define build_half 50

int move_image_x = 0;
int move_image_y = 0;
float particle_time = 0.0f;

SceneMgr::SceneMgr()
{
	Cimage = new Renderer(x_size, y_size);
	start_time = (float)timeGetTime()*0.001f;
	m_Block_ID[0] = Cimage->CreatePngTexture("./resource/perfect_first.PNG");
	m_Block_ID[1] = Cimage->CreatePngTexture("./resource/runrun.PNG");
	background = Cimage->CreatePngTexture("./resource/addbuck.PNG");
	sprite = Cimage->CreatePngTexture("./resource/sprite_image.PNG");
	bullet_image = Cimage->CreatePngTexture("./resource/bullet.PNG");
	for (int i = 0; i < 3; ++i)
	{
		type[2*i] = object_building;
		switch (i)
		{
		case 0:
			mainobject[2 * i] = new object(0, y_size/3, type[2*i], 1);
			break;
		case 1:
			mainobject[2 * i] = new object(-(x_size/3), y_size / 4, type[2*i], 1);
			break;
		case 2:
			mainobject[2 * i] = new object(x_size / 3, y_size / 4, type[2*i], 1);
			break;
		}
		
		list[2*i] = true;

		type[2 * i + 1] = object_building;
		switch (i)
		{
		case 0:
			mainobject[2 * i + 1] = new object(0, -y_size / 3, type[2*i+1], 2);
			break;
		case 1:
			mainobject[2 * i + 1] = new object(-(x_size / 3), -(y_size / 4), type[2*i + 1], 2);
			break;
		case 2:
			mainobject[2 * i + 1] = new object((x_size / 3), -(y_size / 4), type[2*i + 1], 2);
			break;
		}
		list[2 * i + 1] = true;
	}
	num = 6;
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
	delete Cimage;
	printf("전부 삭제\n");
}

void SceneMgr::update()
{
	float time = timeGetTime()*0.001f;
	float bullet_flag = time - start_time;
	static float time_cut = 0;

	if (move_image_x == 7)
	{
		move_image_x = 0;
		move_image_y = (move_image_y + 1) % 3;
	}
	else
	{
		move_image_x += 1;
	}
	particle_time += 0.1;

	printf("%f\n", bullet_flag - (float)time_cut);
	printf("%d\n", mainobject[0]->set_Iteam());

	for (int i = 0; i < num; ++i)
	{
		if (list[i])
		{
			switch (type[i])
			{
			case object_character:
				if (bullet_flag - time_cut >= 1)
				{
					get_object(mainobject[i]->set_x(), mainobject[i]->set_y(), object_arrow, mainobject[i]->set_Iteam());
				}
				break;
			case object_building:
				if (bullet_flag - time_cut>= 1)
				{
					get_object(mainobject[i]->set_x(), mainobject[i]->set_y(), object_bullet, mainobject[i]->set_Iteam());	
				}
				break;
			}
			
		}
	}

	if (bullet_flag - time_cut >= 1)
			{
				get_object(double(rand() % 500 - 250), double(rand() % 500), object_character, 1);
			}
	
	if (bullet_flag - time_cut>= 1)
	{
		time_cut += 1;
		FmakeTime += 1;
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
	
	Cimage->DrawTexturedRect(0, 0, 0, 800, 1.0f, 1.0f, 1.0f, 1, background, 0.9);
	for (int i = 0; i < num; ++i)
	{
		if (list[i] == true)
		{
			switch (type[i])
			{
			case object_character:
				switch (mainobject[i]->set_Iteam())
				{
				case 1:
					Cimage->DrawSolidRectGauge((float)mainobject[i]->set_x(), (float)mainobject[i]->set_y() + 20, 0, 30, 5, 1.0f, 0.0f, 0.0f, 1,
						(float)mainobject[i]->set_life() / 100.0, 0.1);
					Cimage->DrawTexturedRectSeq((float)mainobject[i]->set_x(), (float)mainobject[i]->set_y(), 0, 30, 1.0f, 0.0f, 1.0f, 1,
						sprite, move_image_x, move_image_y, 8, 3, 0.2);
					break;
				case 2:
					Cimage->DrawSolidRectGauge((float)mainobject[i]->set_x(), (float)mainobject[i]->set_y() + 20, 0, 30, 5, 0.0f, 0.0f, 1.0f, 1,
						(float)mainobject[i]->set_life() / 100.0, 0.1);
					Cimage->DrawTexturedRectSeq((float)mainobject[i]->set_x(), (float)mainobject[i]->set_y(), 0, 30, 1.0f, 1.0f, 1.0f, 1,
						sprite, move_image_x, move_image_y, 8, 3, 0.2);
					break;
				}
				break;
			case object_building:
				switch (mainobject[i]->set_Iteam())
				{
				case 1:
					Cimage->DrawSolidRectGauge((float)mainobject[i]->set_x(), (float)mainobject[i]->set_y() + 60, 0, 80, 10, 1.0f, 0.0f, 0.0f, 1,
						(float)mainobject[i]->set_life() / 500.0, 0.1);
					Cimage->DrawTexturedRect((float)mainobject[i]->set_x(), (float)mainobject[i]->set_y(), 0, 80, 1.0f, 1.0f, 1.0f, 1,
						m_Block_ID[0], 0.1);
					break;
				case 2:
					Cimage->DrawSolidRectGauge((float)mainobject[i]->set_x(), (float)mainobject[i]->set_y() + 60, 0, 80, 10, 0.0f, 0.0f, 1.0f, 1,
						(float)mainobject[i]->set_life() / 500.0, 0.1);
					Cimage->DrawTexturedRect((float)mainobject[i]->set_x(), (float)mainobject[i]->set_y(), 0, 80, 1.0f, 1.0f, 1.0f, 1,
						m_Block_ID[1], 0.1);
					break;
				}
				
				break;
			case object_bullet:
				switch (mainobject[i]->set_Iteam())
				{
				case 1:
					//Cimage->DrawSolidRect((float)mainobject[i]->set_x(), (float)mainobject[i]->set_y(), 0, 2, 1.0f, 0.0f, 0.0f, 1, 0.3);
					Cimage->DrawParticle((float)mainobject[i]->set_x(), (float)mainobject[i]->set_y(), 0, 2, 1.0f, 1.0f, 1.0f, 1,
						-mainobject[i]->set_speed_x(), -mainobject[i]->set_speed_y(), bullet_image, particle_time);
					break;
				case 2:
					Cimage->DrawParticle((float)mainobject[i]->set_x(), (float)mainobject[i]->set_y(), 0, 2, 1.0f, 1.0f, 1.0f, 1,
						-mainobject[i]->set_speed_x(), -mainobject[i]->set_speed_y(), bullet_image, particle_time);
					break;
				}
				break;
			case object_arrow:
				switch (mainobject[i]->set_Iteam())
				{
				case 1:
					Cimage->DrawSolidRect((float)mainobject[i]->set_x(), (float)mainobject[i]->set_y(), 0, 2, 0.5f, 0.2f, 0.7f, 1, 0.3);
					break;
				case 2:
					Cimage->DrawSolidRect((float)mainobject[i]->set_x(), (float)mainobject[i]->set_y(), 0, 2, 1.0f, 1.0f, 0.0f, 1, 0.3);
					break;
				}
				break;
			}
			
		}
	}
}


void SceneMgr::get_object(float x, float y, int get_type, int Iteam)
{
	int tmp = 0;

	for (int i = 0; i < num; ++i)
	{
		if (!list[i])
		{
			type[i] = get_type;
			mainobject[i] = new object(x, y, type[i], Iteam);
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
		mainobject[num] = new object(x, y, type[num], 1);
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

	if (mainobject[i]->set_Iteam() != mainobject[j]->set_Iteam())
	{
		switch (type[i])
		{
		case object_character:
			switch (type[j])
			{
			case object_character:
				break;
			case object_building:
				if (-50 < ix - jx && ix - jx < 50)
				{
					if (-50 < iy - jy && iy - jy < 50)
					{
						mainobject[i]->minus_life(mainobject[j]->set_life());
						mainobject[j]->minus_life(mainobject[i]->set_life());
					}
				}
				break;
			case object_bullet:
				if (-15 < ix - jx && ix - jx < 15)
				{
					if (-15 < iy - jy && iy - jy < 15)
					{
						mainobject[i]->minus_life(mainobject[j]->set_life());
						mainobject[j]->minus_life(mainobject[i]->set_life());
					}
				}
				break;
			case object_arrow:
				if (-15 < ix - jx && ix - jx < 15)
				{
					if (-15 < iy - jy && iy - jy < 15)
					{
						mainobject[i]->minus_life(mainobject[j]->set_life());
						mainobject[j]->minus_life(mainobject[i]->set_life());
					}
				}
				break;
			}
			break;
		case object_building:
			switch (type[j])
			{
			case object_character:
				if (-50 < ix - jx && ix - jx < 50)
				{
					if (-50 < iy - jy && iy - jy < 50)
					{
						mainobject[i]->minus_life(mainobject[j]->set_life());
						mainobject[j]->minus_life(mainobject[i]->set_life());
					}
				}
				break;
			case object_building:
				break;
			case object_bullet:
				if (-50 < ix - jx && ix - jx < 50)
				{
					if (-50 < iy - jy && iy - jy < 50)
					{
						mainobject[i]->minus_life(mainobject[j]->set_life());
						mainobject[j]->minus_life(mainobject[i]->set_life());
					}
				}
				break;
			case object_arrow:
				if (-50 < ix - jx && ix - jx < 50)
				{
					if (-50 < iy - jy && iy - jy < 50)
					{
						mainobject[i]->minus_life(mainobject[j]->set_life());
						mainobject[j]->minus_life(mainobject[i]->set_life());
					}
				}
				break;
			}
		case object_bullet:
			switch (type[j])
			{
			case object_character:
				if (-15 < ix - jx && ix - jx < 15)
				{
					if (-15 < iy - jy && iy - jy < 15)
					{
						mainobject[i]->minus_life(mainobject[j]->set_life());
						mainobject[j]->minus_life(mainobject[i]->set_life());
					}
				}
				break;
			case object_building:
				if (-50 < ix - jx && ix - jx < 50)
				{
					if (-50 < iy - jy && iy - jy < 50)
					{
						mainobject[i]->minus_life(mainobject[j]->set_life());
						mainobject[j]->minus_life(mainobject[i]->set_life());
					}
				}
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
				if (-15 < ix - jx && ix - jx < 15)
				{
					if (-15 < iy - jy && iy - jy < 15)
					{
						mainobject[i]->minus_life(mainobject[j]->set_life());
						mainobject[j]->minus_life(mainobject[i]->set_life());
					}
				}
				break;
			case object_building:
				if (-50 < ix - jx && ix - jx < 50)
				{
					if (-50 < iy - jy && iy - jy < 50)
					{
						mainobject[i]->minus_life(mainobject[j]->set_life());
						mainobject[j]->minus_life(mainobject[i]->set_life());
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
	
}


