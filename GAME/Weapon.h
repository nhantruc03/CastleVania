#pragma once
//#include"Simon.h"
#include"GameGlobal.h"
#include"Animation.h"
#include"GameObject.h"
#include"Textures.h"
#include<unordered_map>
class Weapon:public CGameObject
{
protected:
	CAnimation* animation;
public:
	//virtual void Update(float dt) {};
	Weapon()
	{
		tag = TAG_WEAPON;
	}
	virtual void Render()
	{
		auto x = this->x ;
		auto y = this->y ;
		animation->Render(x, y);
	}
	virtual void Update(float dt)
	{
		animation->isreverse = this->isReverse;
	}
};

