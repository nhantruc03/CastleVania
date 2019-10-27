#pragma once
#include"GameObject.h"
#include"Animations.h"
class Enemy :public CGameObject
{
protected:
	CAnimation* animation;
	LPSPRITE hit_effect;

public:
	int health;
	bool ishit;
	int item;
	int direct;
	Enemy(){}	
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {}

	virtual void isHit() { ishit = true; }
	virtual void Burn()
	{
		animation = Animations::GetInstance()->Get(TAG_EFFECT, TYPE_EFFECT_BURN);
		animation->isreverse = false;
		isBurn = true;
	}

	virtual void Render()
	{
		if (ishit)
		{
			hit_effect->Draw(x - 8, y - 8);
			health -= 1;
			ishit = false;
			if (health == 0)
			{
				Burn();
			}
		}
		animation->isreverse = isReverse;
		animation->Render(x, y);
	}
};

