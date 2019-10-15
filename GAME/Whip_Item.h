#pragma once
#include"Item.h"

class Whip_Item :public Item
{
public:
	Whip_Item()
	{
		type = TYPE_ITEM_WHIP;
		sprite = SpritesManager::GetInstance()->Get(TAG_ITEM, type);
		width = 32;
		height = 32;
		vx = 0;
		vy = 0.2f;
		isDead = false;
	}
};

