#pragma once
#include"Weapon.h"
class MorningStar:public Weapon
{
public:
	MorningStar()
	{
		CTextures * textures = CTextures::GetInstance();
		CSprites* sprites = CSprites::GetInstance();
		CAnimations * a = CAnimations::GetInstance();
		LPDIRECT3DTEXTURE9 texMorningStar = textures->Get(1);
		sprites->Add(100, 136, 18, 136 + 16, 18 + 48,texMorningStar);
		sprites->Add(101, 280, 12, 280 + 32, 12+ 38, texMorningStar);
		sprites->Add(102, 352, 16, 352+ 44, 16 + 18, texMorningStar);
		LPANIMATION ani;
		ani = new CAnimation(100);
		ani->Add(100);
		ani->Add(101);
		ani->Add(102);
		a->Add(600, ani);
		AddAnimation(600);
		this->animation = animations[7];
		vx = vy = 0;
		tag = 0;
		type = 0;
		/*width = 32;
		height = 32;*/
	}
	void Render(float translateX = 0, float translateY = 0)
	{
		auto frameIndex = SIMON->curAni->currentFrame-1;
		if (frameIndex != 0 && frameIndex != 1 && frameIndex!=2) return;

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
			x += (isReverse ? 49 : -49);
			if (SIMON->State->StateName==SIMON_STATE_ATTACK)
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

