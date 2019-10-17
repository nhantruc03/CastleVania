#pragma once
#include"MorningStar.h"
#include"Dagger.h"

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
		default:
			return NULL;
		}
	}

	static Weapon* ConvertToWeapon(Weapon* o)
	{
		Weapon* w = o;

		switch (o->type)
		{
		case TYPE_WEAPON_MORNINGSTAR:
			w = (MorningStar*)w;
			break;
		case TYPE_WEAPON_DAGGER:
			w = (Dagger*)w;
			break;
		}
		return w;
	}
};