#pragma once
#include"GameObject.h"
#include"Brick.h"
class Item:public CGameObject
{
protected:
	CAnimation* animation;
	CSprite* effect;
public:
	float timetoshoweffect;
	bool rewarded;
	float prevX;
	float ExistTime;
	Item(int type_id);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void SetPosition(float x, float y) { this->x = x, this->y = y; prevX = x; }
	void GetReward()
	{
		vx = vy = 0;
		if (type == TYPE_ITEM_MONEY_1000 || type == TYPE_ITEM_MONEY_700 || type == TYPE_ITEM_MONEY_400)
		{
			rewarded = true;

		}
		else
		{
			this->isDead = true;
		}
	}
};

