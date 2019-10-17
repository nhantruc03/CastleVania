#pragma once
#include"GameObject.h"
#include"Animations.h"
class HoldItemObject:public CGameObject 
{
protected:
	CAnimation* animation;
	
public:
	int item;
	HoldItemObject()
	{
		tag = TAG_HOLDER;
		isBurn = false;
	}
	void Render()
	{
		animation->Render(x, y);
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
	{
		if (isBurn)
		{
			if (animation->CheckEndAni())
			{
				isDead = true;
				animation->SetEndAniFalse();
				animation->currentFrame = -1;
				
			}
		}
	}
	void Burn()
	{
		animation = Animations::GetInstance()->Get(TAG_EFFECT, TYPE_EFFECT_BURN);
		isBurn = true;
	}
};

