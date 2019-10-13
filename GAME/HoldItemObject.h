#pragma once
#include"GameObject.h"
#include"AnimationsManager.h"
class HoldItemObject:public CGameObject 
{
protected:
	CAnimation* animation;
	
public:
	int item;
	//virtual void Update(float dt) {};
	HoldItemObject()
	{
		tag = TAG_HOLDER;
	}
	virtual void Render()
	{
		animation->Render(x, y);
	}
	virtual void Update(float dt, vector<LPGAMEOBJECT> *coObjects)
	{
		//animation->isreverse = this->isReverse;
	}
};

