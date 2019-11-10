#pragma once
#include"GameObject.h"
#include"Brick.h"
#include"Camera.h"
class Effect :public CGameObject
{
protected:
	CAnimation* animation;
	CSprite* effect;
public:
	virtual void Render()
	{
		effect->Draw(x, y);
	}
	virtual void Update(DWORD dt)
	{
		vy += ENEMY_GRAVITY / 2 * dt;
		CGameObject::Update(dt);
		x += dx;
		y += dy;
		if (!Camera::GetInstance()->IsContain(this->GetBoundingBox()))
		{
			this->isDead = true;
		}
	}
};

