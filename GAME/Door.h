#pragma once
#include "GameObject.h"
class Door : public CGameObject
{
public:
	CAnimation* animation;
	
	//bool isclosed;
//	bool isopened;
	void open()
	{
		animation = animations[1];
	}
	void close()
	{
		animation = animations[3];
	}
	bool isclosed()
	{
		if (animation == animations[0])
			return true;
		if (animation == animations[3] && animation->CheckEndAni())
			return true;
		return false;
	}

	bool isopened()
	{
		if (animation == animations[1] && animation->CheckEndAni())
			return true;
		return false;
	}
	Door(int id)
	{
		tag = 9;
		type = id;
		width = 48;
		height = 96;
		isDead = false;
		AddAnimation(tag, 0); // dong
		AddAnimation(tag, 1); // dang mo
		AddAnimation(tag, 2); // mo
		AddAnimation(tag, 3); // dang dong
		animation = animations[0];
	}
	void Render()
	{
		animation->Render(x, y);
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
	{
		if (isopened())
		{
			animation = animations[2];
		}
		if (isclosed())
		{
			animation = animations[0];
		}
		animation->Update();
	}
};