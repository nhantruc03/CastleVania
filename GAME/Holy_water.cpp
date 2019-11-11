#include"Holy_water.h"
#include"Simon.h"
#include"HoldItemObject.h"
#include"Brick.h"
#include"Enemy.h"
Holy_water::Holy_water()
{
	tag = TAG_WEAPON;
	AddAnimation(tag, 4);
	AddAnimation(tag, 5);
	width = 16;
	height = 16;
	vx = vy = 0;
	type = TYPE_WEAPON_HOLY_WATER;
	available = false;
	isDead = false;
	animation = animations[0];
	x = SIMON->x;
	y = SIMON->y - 20;
	active = false;
}

void Holy_water::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	RECT Holy_water = GetBoundingBox();
	if (Camera::GetInstance()->IsContain(Holy_water) == false)
	{
		//SIMON->throwing = false;
		isDead = true;
		available = false;
	}
	if (animation == animations[1]&&animation->CheckEndAni())
	{
		animation->SetEndAniFalse();
		this->isDead = true;
		//SIMON->throwing = false;
		available = false;
	}
	if (available)
	{
		animation->Update();
		if (animation == animations[0])
		{
			vy += WEAPON_GRAVITY/2 * dt;
		}
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
			y += min_ty * dy + ny * 0.2f;
			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];
				if (dynamic_cast<HoldItemObject*>(e->obj))
				{
					dynamic_cast<HoldItemObject*>(e->obj)->isHit();
				}
				if (dynamic_cast<CBrick*>(e->obj))
				{
					if (!active)
					{
						active = true; 
						vx = vy = 0;
						animation = animations[1];
						y -= 5;
					}
				}
				if (dynamic_cast<Enemy*>(e->obj))
				{
					if (dynamic_cast<Enemy*>(e->obj)->timeshowhiteffect <= 0)
					{
						e->obj->isHit();
					}
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
					if (dynamic_cast<Enemy*>(coObjects->at(i))->timeshowhiteffect <= 0)
					{
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

void Holy_water::Render()
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
