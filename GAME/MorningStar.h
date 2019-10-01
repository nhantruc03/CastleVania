#pragma once
#include"Weapon.h"
class MorningStar :public Weapon
{
public:
	int level;
	MorningStar(int level)
	{
		this->level = level;
		LPANIMATION ani;
		ani = new CAnimation(100);
		if (level == 1)
		{
			ani->Add(TAG_WEAPON, 0);
			ani->Add(TAG_WEAPON, 1);
			ani->Add(TAG_WEAPON, 2);
		}
		else if (level == 2)
		{
			ani->Add(TAG_WEAPON, 3);
			ani->Add(TAG_WEAPON, 4);
			ani->Add(TAG_WEAPON, 5);
		}
		else
		{
			ani->Add(TAG_WEAPON, 6);
			ani->Add(TAG_WEAPON, 7);
			ani->Add(TAG_WEAPON, 8);
		}

		this->animation = ani;
		vx = vy = 0;
		tag = 0;
		type = 0;
		/*width = 32;
		height = 32;*/
	}

	void Update(float dt)
	{
		//if(keyCode[DIK_A])
	}

	void Render(float translateX = 0, float translateY = 0)
	{
		auto frameIndex = SIMON->curAni->currentFrame - 1;
		if (frameIndex != 0 && frameIndex != 1 && frameIndex != 2) return;

		auto sprite = animation->frames[frameIndex]->GetSprite();// animation->GetSprite(frameIndex);
		auto x = SIMON->x;
		auto y = SIMON->y;
		sprite->isreverse = this->isReverse;

		switch (frameIndex)
		{
		case 0:
			x += (isReverse ? -36 : 36);
			if (SIMON->State->StateName == SIMON_STATE_ATTACK)
			{
				y += 7;
			}
			else y += 15;
			break;

		case 1:
			x += (isReverse ? -24 : 24);
			if (SIMON->State->StateName == SIMON_STATE_ATTACK)
			{
				y -= 4;
			}
			else y += 3;
			//this->isDead = true;
			break;
		case 2:
			if (level != 3)
			{
				x += (isReverse ? 49 : -49);
			}
			else
			{
				x += (isReverse ? 65 : -65);
			}
			if (SIMON->State->StateName == SIMON_STATE_ATTACK)
			{
				y -= 8;
			}
			else y -= 3;
			this->isDead = true;
			break;
		}
		sprite->Draw(x, y);
	}

};

