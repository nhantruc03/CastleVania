#pragma once
#include"Simon.h"
//#include"Sprites.h"
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
	virtual void Render(float translateX = 0, float translateY = 0)
	{
		auto x = this->x + translateX;
		auto y = this->y + translateY;
		animation->Render(x, y);
	}
	virtual void Update(float dt)
	{
		animation->isreverse = this->isReverse;
	}
};

