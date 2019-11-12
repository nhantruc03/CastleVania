#pragma once
#include"GameObject.h"
class invisibleObject : public CGameObject
{
public:
	CSprite* temp;
	invisibleObject(int width =32, int height =18)
	{
		tag = TAG_INVISIBLE_OBJECT;
		this->width = width;
		this->height = height;
		isDead = false;
		temp = Sprites::GetInstance()->Get(4, 2); // lay hinh dai de tuong trung cho invisible object
	}
	void Render()
	{
		temp->Draw(x, y);
	}
};