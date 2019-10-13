#pragma once
#include "BigHeart.h"
#include"Dagger_Item.h"	
#include"Whip.h"
class ItemsManager
{
public:
	ItemsManager() {};
	~ItemsManager() {};

	static Item* CreateItem(int type)
	{
		switch (type)
		{
		case 0:
			return new BigHeart();
		case 1:
			return new Whip();
		case 2:
			return new Dagger_Item();
		default:
			return NULL;
		}
	}
};