#pragma once
#include"Weapon.h"
#include"Camera.h"
class Axe:public Weapon
{
public:
	Axe();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void Render();

};