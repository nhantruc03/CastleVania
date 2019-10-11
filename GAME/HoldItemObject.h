#pragma once
#include"GameObject.h"
#include"AnimationsManager.h"
class HoldItemObject:public CGameObject 
{
protected:
	CAnimation* animation;
public:
	//virtual void Update(float dt) {};
	HoldItemObject()
	{
		tag = TAG_HOLDER;
	}
	virtual void Render()
	{
		animation->Render(x, y);
	}
	virtual void Update(float dt)
	{
		animation->isreverse = this->isReverse;
	}
};

