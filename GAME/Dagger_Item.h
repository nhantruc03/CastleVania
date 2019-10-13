#pragma once
#include"Item.h"

class Dagger_Item :public Item
{
public:
	Dagger_Item()
	{
		type = TYPE_ITEM_DAGGER;
		sprite = SpritesManager::GetInstance()->Get(TAG_ITEM, type);
		width = 32;
		height = 18;
		vx = 0;
		vy = 0.2f;
		isDead = false;
	}

};

