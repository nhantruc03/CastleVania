#pragma once
#include"Item.h"

class Whip_Item :public Item
{
public:
	Whip_Item()
	{
		type = TYPE_ITEM_WHIP;
		animation = Animations::GetInstance()->Get(TAG_ITEM, 1);
		width = 32;
		height = 32;
		vx = 0;
		vy = 0.2f;
		isDead = false;
	}
};

