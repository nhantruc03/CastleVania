#pragma once
#include"GameObject.h"
#include"Animations.h"
class Enemy :public CGameObject
{
protected:
	CAnimation* animation;
	LPSPRITE hit_effect;

public:
	float timeshowhiteffect;

	bool ishit;
	int item;
	int direct;
	Enemy(){}	
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	
		if (timeshowhiteffect)
		{
			timeshowhiteffect -= dt;
		}
		if (health == 0)
		{
			Burn();
		}
		animation->Update();
		if (isBurn)
		{
			vx = vy = 0;
			if (animation->CheckEndAni())
			{
				isDead = true;
				animation->SetEndAniFalse();
				animation->currentFrame = -1;
			}
		}
		if (!Camera::GetInstance()->IsContain(this->GetBoundingBox()))
		{
			this->isDead = true;
		}
	}

	virtual void isHit() { ishit = true; }
	virtual void Burn()
	{
		animation = Animations::GetInstance()->Get(TAG_EFFECT, TYPE_EFFECT_BURN);
		animation->isreverse = false;
		isBurn = true;
	}

	virtual void Render()
	{
		if (ishit && timeshowhiteffect<=0)
		{
			timeshowhiteffect = 200;
			health -= 1;
			ishit = false;
			if (health == 0)
			{
				Burn();
			}
		}
		
		animation->isreverse = isReverse;
		animation->Render(x, y);
		if (timeshowhiteffect>0)
		{
			hit_effect->Draw(x - 8, y - 8);
		}
	}
};

