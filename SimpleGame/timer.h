#pragma once
class timer
{
private:
	float time[100];
public:
	timer();
	~timer();

	const float get_time(int);
	void set_time(float, int);
};

