#pragma once
#include"GameObject.h"
#include"Brick.h"
class Item:public CGameObject
{
protected:
	CSprite* sprite;
public:
	float ExistTime;
	Item();
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
};
