#pragma once
#include "FirePillar.h"

class HoldItemObjectsManager
{
public:
	HoldItemObjectsManager() {};
	~HoldItemObjectsManager() {};

	static HoldItemObject* CreateHolder(int holderID, int itemID)
	{
		HoldItemObject* h;

		switch (holderID)
		{
		case TYPE_HOLDER_FIREPILLAR:
		{
			h = new FirePillar();
			break;
		}
		default:
			return NULL;
		}

		h->item = itemID;
		return h;
	}
};