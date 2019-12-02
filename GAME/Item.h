#pragma once
#include"GameObject.h"
#include"Brick.h"
#define ITEM_VY 0.2f
#define ITEM_VX 0.1f
class Item:public CGameObject
{
protected:
	CAnimation* animation;
public:
	float prevX;
	float ExistTime;
	Item(int type_id);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void SetPosition(float x, float y) { this->x = x, this->y = y; prevX = x; }

};

