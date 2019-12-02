#pragma once
#include"CGameObject.h"
class HoldItemObject :public CGameObject
{
public:
	int item;
	HoldItemObject(int type_id, int itemid)
	{
		tag = 3;
		item = itemid;
		type = type_id;

		if (type == 0)
		{
			width = 32;
			height = 64;
		}
		if (type == 1)
		{
			width = 16;
			height = 32;
		}
	}

};

