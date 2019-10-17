#pragma once
#include"GameObject.h"
#include"Brick.h"
class Item:public CGameObject
{
protected:
	CAnimation* animation;
public:
	float ExistTime;
	Item();
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
};

