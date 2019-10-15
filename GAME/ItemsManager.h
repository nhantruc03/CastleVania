#pragma once
#include "BigHeart_Item.h"
#include"Dagger_Item.h"	
#include"Whip_Item.h"
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
			return new BigHeart_Item();
		case 1:
			return new Whip_Item();
		case 2:
			return new Dagger_Item();
		default:
			return NULL;
		}
	}
};