#pragma once
#include"Weapon.h"
#include"Camera.h"
class Dagger :public Weapon
{
public:
	Dagger();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void Render();

};