#include "stdafx.h"
#include "timer.h"


timer::timer()
{
	for (int i = 0; i < 100; ++i)
	{
		time[i] = 0.0;
	}
}


timer::~timer()
{
}

const float timer::get_time(int i)
{
	return time[i];
}

void timer::set_time(float get, int i)
{
	time[i] += get;
}