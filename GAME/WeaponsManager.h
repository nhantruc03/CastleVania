#pragma once
#include"MorningStar.h"
#include"Dagger.h"
#include"Holy_water.h"
#include"Axe.h"
class WeaponsManager
{
public:
	static Weapon* CreateWeapon(int weaponType)
	{
		switch (weaponType)
		{
		case TYPE_WEAPON_MORNINGSTAR:
			return new MorningStar(SIMON->morningstarlevel);
		case TYPE_WEAPON_DAGGER:
			return new Dagger();
		case TYPE_WEAPON_HOLY_WATER:
			return new Holy_water();
		case TYPE_WEAPON_AXE:
			return new Axe();
		default:
			return NULL;
		}
	}
};