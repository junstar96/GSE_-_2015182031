#pragma once
#include"stdafx.h"
#include"Renderer.h"
#include"object.h"
#include<Windows.h>
#define max 100


class SceneMgr //�� �ȿ� ������Ʈ���� ����ְ� 
{
private:
	bool list[100];
	int num;
	object* mainobject[max];
	Renderer* image = NULL;
public:
	SceneMgr();
	SceneMgr(int num);
	~SceneMgr();

	void get_object(float x, float y);
	void del_object();
	void del_object(int i);

	void update();

	void draw();

	void printf_point();

	void crash_object(int i, int j);
	void cul_object(int i, int j);
};