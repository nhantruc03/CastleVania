#pragma once
#include"CGameObject.h"
class invisibleObject : public CGameObject
{
public:
	invisibleObject(int width = 32, int height = 18)
	{
		tag = 999;
		this->width = width;
		this->height = height;
	}
};