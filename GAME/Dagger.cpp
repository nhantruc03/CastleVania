#include"Dagger.h"
#include"Simon.h"
#include"HoldItemObject.h"
#include"Brick.h"
#include"Enemy.h"
Dagger::Dagger()
{
	tag = TAG_WEAPON;
	type = TYPE_WEAPON_DAGGER;
	this->animation = Animations::GetInstance()->Get(TAG_WEAPON, 3);
	width = 32;
	height = 18;


	vx = vy = 0;
	available = false;
	isDead = false;

	x = SIMON->x;
	y = SIMON->y - 20;
}

void Dagger::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	RECT dagger = GetBoundingBox();
	if (Camera::GetInstance()->IsContain(dagger) == false)
	{
		//SIMON->throwing = false;
		isDead = true;
		available = false;
	}
	if (available)
	{
		animation->Update();
		CGameObject::Update(dt, coObjects);
		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();

		// turn off collision when die 
		CalcPotentialCollisions(coObjects, coEvents);
		// No collision occured, proceed normally

		if (coEvents.size() == 0)
		{
			x += dx;
			y += dy;
		}
		else
		{
			float min_tx, min_ty, nx = 0, ny;

			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

			// block 
			x += min_tx * dx + nx * 0.2f;		// nx*0.2f : need to push out a bit to avoid overlapping next frame
			//y += min_ty * dy + ny * 0.2f;
			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];
				if (dynamic_cast<HoldItemObject*>(e->obj))
				{
					dynamic_cast<HoldItemObject*>(e->obj)->isHit();
					isDead = true;
				//	SIMON->throwing = false;
				}
				if (dynamic_cast<CBrick*>(e->obj))
				{
					x += dx;
				}
				if (dynamic_cast<Enemy*>(e->obj))
				{
					dynamic_cast<Enemy*>(e->obj)->isHit();
					isDead = true;
					//SIMON->throwing = false;
				}
			}
		}
		for (UINT i = 0; i < coObjects->size(); i++)
		{
			float l, t, r, b;
			coObjects->at(i)->GetBoundingBox(l, t, r, b);
			if (this->IsContain(l, t, r, b) == true)
			{
				switch (coObjects->at(i)->tag)
				{
				case TAG_HOLDER:
					coObjects->at(i)->isHit();
					this->isDead = true;
					//SIMON->throwing = false;
					break;
				case TAG_ENEMY:
					if (dynamic_cast<Enemy*>(coObjects->at(i))->timeshowhiteffect <= 0)
					{
						isDead = true;
					//	SIMON->throwing = false;
						coObjects->at(i)->isHit();
					}
					break;
				}

			}
			if (isDead)
				return;
		}
	}
}

void Dagger::Render()
{
	if (!available)
	{
		int frameIndex = SIMON->curAni->currentFrame - 1;
		animation->isreverse = this->isReverse;
		switch (frameIndex)
		{
		case 1:
			if (SIMON->State == STATE_ATTACK || SIMON->State == STATE_ATTACK_ONSTAIR_DOWN || SIMON->State == STATE_ATTACK_ONSTAIR_UP)
			{
				x = SIMON->x;
				y = SIMON->y - 20;
				vx = isReverse ? WEAPON_SPEED*3 : -WEAPON_SPEED*3;
				available = true;
			}
			break;
		}
	}
	if (available == true)
	{
		animation->Render(x, y);
	}
}
