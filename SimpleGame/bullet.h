#pragma once
#include"stdafx.h"

class bullet
{
private:
	int type; // 1�̸� �Ʊ�, 2�� ����
	int atp;//��Ʋ������ �޴´�.
public:
	bullet() {};
	bullet(int type, int  atp) : type(type), atp(atp)
	{

	}
};