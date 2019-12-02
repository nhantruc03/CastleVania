#pragma once
#include "CGameObject.h"
class Door : public CGameObject
{
public:

	Door(int id)
	{
		tag = 9;
		type = id;
		width = 48;
		height = 96;
	}
};