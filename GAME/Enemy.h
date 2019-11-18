#pragma once
#include"GameObject.h"
#include"Animations.h"
#include"listeffect_global.h"
#include"hit.h"
#include"burn.h"
#include"Simon.h"
class Enemy :public CGameObject
{
protected:
	CAnimation* animation;
public:
	bool isSleeping;
	float timedelaytogetdmg;
	int item;
	int direct;
	int healthtosub;
	Enemy(){}	
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	
		if (timedelaytogetdmg)
		{
			timedelaytogetdmg -= dt;
		}
		if (ishit && timedelaytogetdmg <= 0)
		{
			timedelaytogetdmg = 700;
			health -= healthtosub;
			ishit = false;

			listeffect.push_back(new hit(x - 8, y - 8));
			if (type != TYPE_ENEMY_BOSS_1)
			{
				if (health == 0)
				{

					listeffect.push_back(new burn(x, y,0));
					this->isDead = true;
				}
			}
			else
			{
				if (health <= 0)
				{
					health = 0;
					listeffect.push_back(new burn(x, y, 1));
					this->isDead = true;
					SIMON->score += 3000;
				}
			}
		}
		if (!SIMON->timeusingstopwatch)
		{
			animation->Update();
		}
		if (!Camera::GetInstance()->IsContain(this->GetBoundingBox()))
		{
			if (type == TYPE_ENEMY_BOSS_1)
			{
				if (!isSleeping)
				{
					this->isDead = true;
				}
			}
			else if (type == TYPE_ENEMY_PANTHER)
			{
				if (!isSleeping)
				{
					this->isDead = true;
				}
			}
			else
			{
				this->isDead = true;
			}
		}
	}
	virtual void Render()
	{
		animation->isreverse = isReverse;
		animation->Render(x, y);
	}
	virtual void isHit(int healthtosub = 1) 
	{
		ishit = true;
		this->healthtosub = healthtosub; 
	};
};

