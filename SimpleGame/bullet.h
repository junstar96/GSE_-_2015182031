#pragma once
#include"stdafx.h"

class bullet
{
private:
	int type; // 1이면 아군, 2면 적군
	int atp;//배틀쉽에서 받는다.
public:
	bullet() {};
	bullet(int type, int  atp) : type(type), atp(atp)
	{

	}
};