#pragma once
#include"GameObject.h"
class Weapon :public CGameObject
{
protected:
	CAnimation* animation;
public:
	//virtual void Update(float dt) {};
	Weapon()
	{
		tag = TAG_WEAPON;
	}
	virtual void Render()
	{
		animation->Render(x, y);
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
	{
		animation->isreverse = this->isReverse;
	}
};