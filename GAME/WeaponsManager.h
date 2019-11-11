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

	//static Weapon* ConvertToWeapon(Weapon* o)
	//{
	//	Weapon* w = o;

	//	switch (o->type)
	//	{
	//	case TYPE_WEAPON_MORNINGSTAR:
	//		w = (MorningStar*)w;
	//		break;
	//	case TYPE_WEAPON_DAGGER:
	//		w = (Dagger*)w;
	//		break;
	//	case TYPE_WEAPON_HOLY_WATER:
	//		w = (Holy_water*)w;
	//		break;
	//	}
	//	return w;
	//}
};