#include "Axe.h"
#include"Simon.h"
#include"HoldItemObject.h"
#include"Brick.h"
#include"Enemy.h"

Axe::Axe()
{
	tag = TAG_WEAPON;
	type = TYPE_WEAPON_AXE;
	this->animation = Animations::GetInstance()->Get(TAG_WEAPON, 6);
	width = 30;
	height = 28;


	vx = 0;
	vy = -0.6;
	available = false;
	isDead = false;

	x = SIMON->x;
	y = SIMON->y - 20;
}

void Axe::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	RECT dagger = GetBoundingBox();
	if (Camera::GetInstance()->IsContain(dagger) == false && this->GetBoundingBox().top>Camera::GetInstance()->GetBound().bottom)
	{
		//SIMON->throwing = false;
		isDead = true;
		available = false;
	}
	if (available)
	{
		animation->Update();
		vy += WEAPON_GRAVITY * dt;
		CGameObject::Update(dt, coObjects);
		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();


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

			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				x += dx;
				y += dy;
				LPCOLLISIONEVENT e = coEventsResult[i];
				if (dynamic_cast<HoldItemObject*>(e->obj))
				{
					e->obj->isHit();
				}
				if (dynamic_cast<Enemy*>(e->obj))
				{
					if (e->obj->type == TYPE_ENEMY_BOSS_1)
					{
						e->obj->isHit(2);
					}
					else
					{
						e->obj->isHit();
						SIMON->score += 100;
					}
				}
				if (dynamic_cast<Weapon*>(e->obj))
				{
					SIMON->score += 100;
					e->obj->isHit();
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
					break;
				case TAG_ENEMY:
					if (dynamic_cast<Enemy*>(coObjects->at(i))->timedelaytogetdmg <= 0)
					{
						
						if (coObjects->at(i)->type == TYPE_ENEMY_BOSS_1)
						{
							coObjects->at(i)->isHit(2);
						}
						else
						{
							coObjects->at(i)->isHit();
							SIMON->score += 100;
						}
					}
					break;
				case TAG_WEAPON:
					SIMON->score += 100;
					coObjects->at(i)->isHit();
					break;
				}

			}
			if (isDead)
				return;
		}
	}
}

void Axe::Render()
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
				vx = isReverse ? WEAPON_SPEED : -WEAPON_SPEED;
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

