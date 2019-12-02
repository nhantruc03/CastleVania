#pragma once
#include"CGameObject.h"
class Special_brick :public CGameObject
{
public:
	int item;
	Special_brick(int type_id, int itemid)
	{

		tag = 10;
		item = itemid;
		type = type_id;
		if (type == 0)
		{
			width = 32;
			height = 32;
		}
		if (type == 1)
		{
			width = 32;
			height = 32;
		}
	}
};

