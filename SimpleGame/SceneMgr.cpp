#include"stdafx.h"
#include"SceneMgr.h"
#include<Windows.h>
#include"Mmsystem.h"
#include"timer.h"
#pragma comment(lib, "winmm.lib")

float start_time;

#define character_half 30
#define build_half 50

int move_image_x = 0;
int move_image_y = 0;
float snow_time = 0.0f;


SceneMgr::SceneMgr()
{
	Cimage = new Renderer(x_size, y_size);
	m_sound = new Sound();
	object_time = new timer();
	start_time = (float)timeGetTime()*0.001f;

	m_Block_ID[0] = Cimage->CreatePngTexture("./resource/perfect_first.PNG");
	m_Block_ID[1] = Cimage->CreatePngTexture("./resource/runrun.PNG");
	background = Cimage->CreatePngTexture("./resource/addbuck.PNG");
	sprite = Cimage->CreatePngTexture("./resource/sprite_image.PNG");
	
	bullet_image = Cimage->CreatePngTexture("./resource/bullet.PNG");
	snow = Cimage->CreatePngTexture("./resource/snowflake.PNG");

	fly_monster = Cimage->CreatePngTexture("./resource/snowflake.PNG");

	soundBG = m_sound->CreateSound("./Dependencies/SoundSamples/MF-W-90.XM");
	bullet_crash = m_sound->CreateSound("./Dependencies/SoundSamples/bell.WAV");
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

	
	m_sound->PlaySoundW(soundBG, false, 1.0f);

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

	snow_time += 0.1f;

	printf("현재 수 : %d\n", num);
	for (int i = 0; i < num; ++i)
	{
		if (list[i])
		{
			switch (type[i])
			{
			case object_character:
				if (bullet_flag - time_cut >= 2)
				{
					get_object(mainobject[i]->set_x(), mainobject[i]->set_y(), object_arrow, mainobject[i]->set_Iteam());
					
				}
				break;
			case object_building:
				if (bullet_flag - time_cut>= 2)
				{
					get_object(mainobject[i]->set_x(), mainobject[i]->set_y(), object_bullet, mainobject[i]->set_Iteam());	
				}
				break;
			}
			
		}
	}

	if (bullet_flag - time_cut >= 2)
	{
		int temp = rand() % 2 + 1;
		//get_object(double(rand() % 500 - 250), double(rand() % 500), object_character, 1);
		switch (temp)
		{
		case 1:
			get_object_character(double(rand() % 500 - 250), double(rand() % 500), 1, temp);
			break;
		case 2:
			switch (rand() % 3)
			{
			case 0:
				get_object_character(mainobject[0]->set_x(), mainobject[0]->set_y(), 1, temp);
				break;
			case 1:
				get_object_character(mainobject[2]->set_x(), mainobject[2]->set_y(), 1, temp);
				break;
			case 2:
				get_object_character(mainobject[4]->set_x(), mainobject[4]->set_y(), 1, temp);
				break;
			}
			break;
		}
	}


	if (bullet_flag - time_cut>= 2)
	{
		time_cut += 2;
		FmakeTime += 2;
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
	//배경과 눈이미지
	Cimage->DrawTexturedRect(0, 0, 0, 800, 1.0f, 1.0f, 1.0f, 1, background, 0.9);
	Cimage->DrawParticleClimate(0, 0, 0, 1, 1, 1, 1, 1, -0.1, -0.1, snow, snow_time, 0.05);

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
					switch (mainobject[i]->set_object_type())
					{
					case 1:
						Cimage->DrawSolidRectGauge((float)mainobject[i]->set_x(), (float)mainobject[i]->set_y() + 20, 0, 30, 5, 1.0f, 0.0f, 0.0f, 1,
							(float)mainobject[i]->set_life() / 100.0, 0.1);
						Cimage->DrawTexturedRectSeq((float)mainobject[i]->set_x(), (float)mainobject[i]->set_y(), 0, 30, 1.0f, 0.0f, 1.0f, 1,
							sprite, move_image_x, move_image_y, 8, 3, 0.2);
						break;
					case 2:
						Cimage->DrawTexturedRect((float)mainobject[i]->set_x(), (float)mainobject[i]->set_y(), 0, 30, 1.0f, 1.0f, 1.0f, 1,
							fly_monster, 0.05);
						break;
					}
					
					break;
				case 2:
					switch (mainobject[i]->set_object_type())
					{
					case 1:
						Cimage->DrawSolidRectGauge((float)mainobject[i]->set_x(), (float)mainobject[i]->set_y() + 20, 0, 30, 5, 0.0f, 0.0f, 1.0f, 1,
							(float)mainobject[i]->set_life() / 100.0, 0.1);
						Cimage->DrawTexturedRectSeq((float)mainobject[i]->set_x(), (float)mainobject[i]->set_y(), 0, 30, 1.0f, 1.0f, 1.0f, 1,
							sprite, move_image_x, move_image_y, 8, 3, 0.2);
						break;
					case 2:
						Cimage->DrawTexturedRect((float)mainobject[i]->set_x(), (float)mainobject[i]->set_y(), 0, 30, 1.0f, 1.0f, 1.0f, 1,
							fly_monster, 0.05);
						break;
					}
					
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
					Cimage->DrawTextW((float)mainobject[i]->set_x(), (float)mainobject[i]->set_y() - 50,
						GLUT_BITMAP_TIMES_ROMAN_10, 0.0f, 0.0f, 0.0f, "building");
					break;
				case 2:
					Cimage->DrawSolidRectGauge((float)mainobject[i]->set_x(), (float)mainobject[i]->set_y() + 60, 0, 80, 10, 0.0f, 0.0f, 1.0f, 1,
						(float)mainobject[i]->set_life() / 500.0, 0.1);
					Cimage->DrawTexturedRect((float)mainobject[i]->set_x(), (float)mainobject[i]->set_y(), 0, 80, 1.0f, 1.0f, 1.0f, 1,
						m_Block_ID[1], 0.1);
					Cimage->DrawTextW((float)mainobject[i]->set_x(), (float)mainobject[i]->set_y() - 50,
						GLUT_BITMAP_TIMES_ROMAN_10, 0.0f, 0.0f, 0.0f, "building");
					break;
				}
				
				break;
			case object_bullet:
				switch (mainobject[i]->set_Iteam())
				{
				case 1:
					//Cimage->DrawSolidRect((float)mainobject[i]->set_x(), (float)mainobject[i]->set_y(), 0, 2, 1.0f, 0.0f, 0.0f, 1, 0.3);
					Cimage->DrawParticle((float)mainobject[i]->set_x(), (float)mainobject[i]->set_y(), 0, 2, 1.0f, 1.0f, 1.0f, 1,
						-mainobject[i]->set_speed_x()/3, -mainobject[i]->set_speed_y()/3, bullet_image, object_time->get_time(i), 0.3);
					object_time->set_time(0.1, i);
					break;
				case 2:
					Cimage->DrawParticle((float)mainobject[i]->set_x(), (float)mainobject[i]->set_y(), 0, 2, 1.0f, 1.0f, 1.0f, 1,
						-mainobject[i]->set_speed_x()/3, -mainobject[i]->set_speed_y()/3, bullet_image, object_time->get_time(i), 0.3);
					object_time->set_time(0.1, i);
					break;
				}
				break;
			case object_arrow:
				switch (mainobject[i]->set_Iteam())
				{
				case 1:
					Cimage->DrawSolidRect((float)mainobject[i]->set_x(), (float)mainobject[i]->set_y(), 0, 20, 0.5f, 0.2f, 0.7f, 1, 0.3);
					break;
				case 2:
					Cimage->DrawSolidRect((float)mainobject[i]->set_x(), (float)mainobject[i]->set_y(), 0, 20, 1.0f, 1.0f, 0.0f, 1, 0.3);
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
			if (mainobject[i] == NULL)
			{
				printf("문제 발생");
			}
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
		mainobject[num] = new object(x, y, type[num], Iteam);
		list[num] = true;
	
		num += 1;
	}
}

void SceneMgr::del_object()
{
	if (num > 0)
	{
		delete mainobject[num - 1];
		list[num] = false;
		type[num] = 0;
		num -= 1;
	}
}

void SceneMgr::del_object(int i)
{
	if (list[i])
	{
		delete mainobject[i];
		list[i] = false;
		type[i] = 0;
		if (i == num - 1)
		{
			num -= 1;
		}
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
	if (mainobject[i]->set_Iteam() != mainobject[j]->set_Iteam())
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
						m_sound->PlaySoundW(bullet_crash, false, 1.0f);
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
						m_sound->PlaySoundW(bullet_crash, false, 1.0f);
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
						m_sound->PlaySoundW(bullet_crash, false, 1.0f);
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
		{
			printf("%d 삭제, 타입 : %d, 부딪힌 객체 : %d\n", i, type[i], j);
			switch (type[i])
			{
			case 1:
				printf("캐릭\n");
				break;
			case 2:
				printf("벽\n");
				break;
			case 3:
				printf("총알\n");
				break;
			case 4:
				printf("화살\n");
				break;
			default:
				printf("타입 없다\n");
				break;
			}
			del_object(i);
		}

		if (mainobject[j]->set_life() <= 0)
		{
			printf("%d 삭제, 타입 : %d\n", j, type[j]);
			switch (type[j])
			{
			case 1:
				printf("캐릭\n");
				break;
			case 2:
				printf("벽\n");
				break;
			case 3:
				printf("총알\n");
				break;
			case 4:
				printf("화살\n");
				break;
			default:
				printf("타입 없다\n");
				break;
			}
			del_object(j);
			
		}
	}
	
}

void SceneMgr::get_object_character(float x, float y, int lteam, int object_type)
{
	int tmp = 0;

	for (int i = 0; i < num; ++i)
	{
		if (!list[i])
		{
			type[i] = object_character;
			mainobject[i] = new object(x, y, type[i], lteam);
			mainobject[i]->get_object_type(object_type);
			if (mainobject[i] == NULL)
			{
				printf("문제 발생");
			}
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
		type[num] = object_character;
		mainobject[num] = new object(x, y, type[num], lteam);
		mainobject[num]->get_object_type(object_type);
		list[num] = true;

		num += 1;
	}
}

