#pragma once
#include"stdafx.h"
#include"object.h"
#define max 100


class SceneMgr //�� �ȿ� ������Ʈ���� ����ְ� 
{
private:
	bool list[100];
	int num;
	object** mainobject = NULL;
public:
	SceneMgr();
	SceneMgr(int num);
	~SceneMgr();

	void get_object();
	void del_object();

	void draw();

};