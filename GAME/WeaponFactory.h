#pragma once
#include"MorningStar.h"
#include"Dagger.h"

class WeaponFactory
{
public:
	static Weapon* CreateWeapon(int weaponType)
	{
		switch (weaponType)
		{
		case ID_WEAPON_MORNINGSTAR:
			return new MorningStar(SIMON->morningstarlevel);
		case ID_WEAPON_DAGGER:
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
		case 0:
			w = (MorningStar*)w;
			break;
		case 1:
			w = (Dagger*)w;
			break;
		}
		return w;
	}
};