#pragma once
#include"GameObject.h"
#include"Animations.h"
#include"listeffect_global.h"
#include"hit.h"
#include"burn.h"
class Enemy :public CGameObject
{
protected:
	CAnimation* animation;
public:
	float timedelaytogetdmg;
	int item;
	int direct;
	Enemy(){}	
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	
		if (timedelaytogetdmg)
		{
			timedelaytogetdmg -= dt;
		}
		if (ishit && timedelaytogetdmg <= 0)
		{
			timedelaytogetdmg = 200;
			health -= 1;
			ishit = false;
			listeffect.push_back(new hit(x - 8, y - 8));
			if (health == 0)
			{

				listeffect.push_back(new burn(x, y));
				this->isDead = true;
			}
		}
		animation->Update();
		if (!Camera::GetInstance()->IsContain(this->GetBoundingBox()))
		{
			this->isDead = true;
		}
	}
	virtual void Render()
	{
		animation->isreverse = isReverse;
		animation->Render(x, y);
	}
};

