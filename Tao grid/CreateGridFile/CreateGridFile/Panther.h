#pragma once
#include "CGameObject.h"
class Panther :public CGameObject
{
public:
	Panther(float x, float y, int direction)
	{
		direct = direction;
		this->x = x;
		this->y = y;
		this->tag = 8;
		this->type = 1;
		this->width = 64;
		this->height = 32;
	}

	~Panther() {};
};

