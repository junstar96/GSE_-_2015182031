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
				if (list[j] == true && i != j)
				{
					crash_object(i, j);
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
		printf("%d째 점 : \n", i);
		mainobject[i]->printf_point();
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