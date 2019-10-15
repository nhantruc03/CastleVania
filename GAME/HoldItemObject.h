#pragma once
#include"GameObject.h"
#include"AnimationsManager.h"
class HoldItemObject:public CGameObject 
{
protected:
	CAnimation* animation;
	
public:
	int item;
	HoldItemObject()
	{
		tag = TAG_HOLDER;
	}
	void Render()
	{
		animation->Render(x, y);
	}
};

