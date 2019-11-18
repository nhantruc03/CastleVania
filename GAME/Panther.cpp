#include "Panther.h"
#include"Simon.h"
Panther::Panther(float x, float y, int direction)
{
	this->isDead = false;
	this->ishit = false;
	this->tag = TAG_ENEMY;
	this->type = 1;
	AddAnimation(tag, 1); // animation sleeping
	AddAnimation(tag, 2); // animation moving
	AddAnimation(tag, 3); // animation jumping
	isSleeping = true;
	isjumping = false;
	isrunning = false;
	this->x = x;
	this->y = y;
	prevX = x;
	this->direct = direction;
	if (direct == -1)
	{
		isReverse = false;
	}
	else
		isReverse = true;

	this->vx = 0;
	this->vy = 0;
	this->width = 64;
	this->height = 32;
	this->health = 1;
	spawnx = x;
	spawny = y;
	animation = animations[0];
}

void Panther::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Enemy::Update(dt, coObjects);
	if (!SIMON->timeusingstopwatch)
	{
		if (isSleeping)
		{
			vx = 0;
		}

		if (abs(SIMON->x - this->x) <= 160 && isSleeping)
		{
			wakeup();
		}
		if ((x <= brick.left + 1 || x >= brick.right - 1) && !isSleeping && !isjumping)
		{
			jump();
		}
		
		vy += ENEMY_GRAVITY * dt;// Simple fall down
		
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
				if (dynamic_cast<CBrick*>(e->obj))
				{

					if (isjumping)
					{
						x += dx;
					}
					if (ny == -1)
					{
						brick = e->obj->GetBoundingBox();
						this->vy = 0;
						if (isjumping)
						{
							if (!isrunning)
							{
								run();
							}
						}
					}
				}
			}
		}
	}
}

void Panther::jump()
{
	vy = -ENEMY_JUMP_SPEED_Y;
	isjumping = true;
	isrunning = false;
	animation = animations[2];
}

void Panther::wakeup()
{
	isrunning = true;
	isSleeping = false;
	vx = ENEMY_WALKING_SPEED * 2 * direct;
	animation = animations[1];
}

void Panther::run()
{
	direct = -direct;
	isjumping = false;
	isrunning = true;
	vx = ENEMY_WALKING_SPEED * 2* direct;
	this->isReverse = !isReverse;
	animation = animations[1];
}

Panther::~Panther()
{
}
