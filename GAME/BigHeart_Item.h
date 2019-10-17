#pragma once
#include"Item.h"

class BigHeart_Item:public Item
{
public:
	BigHeart_Item()
	{
		type = TYPE_ITEM_BIG_HEART;
		animation = AnimationsManager::GetInstance()->Get(TAG_ITEM, 0);
		width = 24;
		height = 20;
		vx = 0;
		vy = 0.2f;
		isDead = false;
	}


};

