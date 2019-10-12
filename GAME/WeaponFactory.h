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
		case 0:
			return new MorningStar(SIMON->morningstarlevel);
		case 1:
			return new Dagger();
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
		case 1:
			w = (Dagger*)w;
			break;
		}
		return w;
	}
};