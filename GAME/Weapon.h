#pragma once
#include"GameObject.h"
class Weapon :public CGameObject
{
protected:
	CAnimation* animation;
public:
	bool available;
	Weapon()
	{
		tag = TAG_WEAPON;
		available = false;
	}
	virtual void Render() {};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {};
};