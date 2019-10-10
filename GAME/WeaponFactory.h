#pragma once
#include"MorningStar.h"

class WeaponFactory
{
public:
	static Weapon* CreateWeapon(int weaponType)
	{
		switch (weaponType)
		{
		case 0:
			return new MorningStar(SIMON->morningstarlevel);

		default:
			return NULL;
		}
	}

	static Weapon* ConvertToWeapon(CGameObject* o)
	{
		Weapon* w = (Weapon*)o;

		switch (o->type)
		{
		case 0:
			w = (MorningStar*)w;
			break;
		}
		return w;
	}
};