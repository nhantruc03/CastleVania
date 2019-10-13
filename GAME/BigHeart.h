#pragma once
#include"Item.h"

class BigHeart:public Item
{
public:
	BigHeart()
	{
		type = TYPE_ITEM_BIG_HEART;
		sprite = SpritesManager::GetInstance()->Get(TAG_ITEM, type);
		width = 24;
		height = 20;
		vx = 0;
		vy = 0.2f;
		isDead = false;
	}


};

