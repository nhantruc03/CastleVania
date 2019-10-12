#pragma once
#include"Weapon.h"
#include"Camera.h"
class Dagger :public Weapon
{
public:
	
	bool available;
	Dagger()
	{
		this->animation = AnimationsManager::GetInstance()->Get(TAG_WEAPON, 3);
		width = 32;
		height = 18;
		
		
		vx=vy = 0;
		type = 1;
		available = false;
		isDead = false;

		x = SIMON->x ;
		y = SIMON->y -20;
		
		tag = TAG_WEAPON;
	}

	virtual void Update(float dt, vector<LPGAMEOBJECT> *coObjects)
	{
		RECT dagger;
		dagger.left = x - width / 2;
		dagger.right = dagger.left + width;
		dagger.top = y - height / 2;
		dagger.bottom = dagger.top + height;
		if(Camera::GetInstance()->IsContain(dagger)==false)
		{
			SIMON->throwing = false;
			isDead = true;
			available = false;
		}
	
		if (available)
		{
			CGameObject::Update(dt, coObjects);
			x += dx;
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
						this->isDead = true;
						SIMON->throwing = false;
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
		int frameIndex = SIMON->curAni->currentFrame - 1;
		CSprite* sprite = animation->frames[0]->GetSprite();
		sprite->isreverse = this->isReverse;
		switch (frameIndex)
		{
		case 1:
			if (SIMON->State->StateName == SIMON_STATE_ATTACK)
			{
				x = SIMON->x;
				y = SIMON->y - 20;
				vx = isReverse ? 0.8f : -0.8f;
				available = true;
			}
			break;
		}
		if (available == true)
		{
			sprite->Draw(x, y);
		}
	}

};