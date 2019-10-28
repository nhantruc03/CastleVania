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
		AddAnimation(9, 0);
		AddAnimation(9, 1);
		AddAnimation(9, 2);
		AddAnimation(9, 3);
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