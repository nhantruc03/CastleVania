#pragma once
#include"Weapon.h"
#include"Camera.h"
class Holy_water :public Weapon
{
public:
	bool active;
	Holy_water();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void Render();

};