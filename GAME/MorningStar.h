#pragma once
#include"Weapon.h"
class MorningStar :public Weapon
{
public:
	int level;
	int frameIndex;
	bool available;
	MorningStar(int level)
	{
		this->level = level;
		if (level == 1)
		{
			this->animation = AnimationsManager::GetInstance()->Get(TAG_WEAPON, 0);
			width = 44;
			height = 16;
		}
		else if (level == 2)
		{
			this->animation = AnimationsManager::GetInstance()->Get(TAG_WEAPON, 1);
			width = 44;
			height = 12;
		}
		else
		{
			this->animation = AnimationsManager::GetInstance()->Get(TAG_WEAPON, 2);
			width = 75;
			height = 12;
		}
		vx = vy = 0;
		type = 0;
		available = false;
		isDead = false;
	}

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
	{
		if (SIMON->State->StateName != SIMON_STATE_ATTACK && SIMON->State->StateName != SIMON_STATE_SIT_ATTACKING)
		{
			this->isDead = true;
		}
		if (available)
		{
			for (UINT i = 0; i < coObjects->size(); i++)
			{
				float l, t, r, b;
				coObjects->at(i)->GetBoundingBox(l, t, r, b);
				if (this->IsContain(l, t, r, b) == true)
				{
					switch (coObjects->at(i)->tag)
					{
					case TAG_HOLDER:
						coObjects->at(i)->isDead = true;
						break;
					default:
						break;
					}

				}
				if (isDead)
					return;
			}
		}
	}

	void Render()
	{
		frameIndex = SIMON->curAni->currentFrame - 1;
		if (frameIndex != 0 && frameIndex != 1 && frameIndex != 2) return;

		CSprite* sprite = animation->frames[frameIndex]->GetSprite();
		
		sprite->isreverse = this->isReverse;
		x = SIMON->x;
		y = SIMON->y;
		switch (frameIndex)
		{
		case 0:
			x += isReverse ? -36 : 36 ;
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
				x += (isReverse ? 50 : -50);
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
			available = true;
			
			break;
		}
		sprite->Draw(x, y);
	}

};