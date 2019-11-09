#pragma once
#include"GameObject.h"
class invisibleObject : public CGameObject
{
public:
	CSprite* temp;
	invisibleObject()
	{
		tag = 999;
		width = 32;
		height = 18;
		isDead = false;
		temp = Sprites::GetInstance()->Get(4, 2);
	}
	void Render()
	{
		//temp->Draw(x, y);
	}
};