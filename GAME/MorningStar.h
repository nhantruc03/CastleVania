#pragma once
#include"Weapon.h"
class MorningStar :public Weapon
{
public:
	int level;
	MorningStar(int level);

	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);

	void Render();

};