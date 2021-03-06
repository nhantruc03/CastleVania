#include "Ghost.h"
#include"Camera.h"
#include"Simon.h"
#include"Special_brick.h"
Ghost::Ghost(float x, float y, int direction)
{
	this->x = x;
	this->tag = TAG_ENEMY;
	this->type = TYPE_ENEMY_GHOST;
	this->y = y;
	this->direct = direction;
	if (direct == -1)
	{
		isReverse = false;
	}
	else
		isReverse = true;
	turn = false;
	this->isDead = false;
	this->ishit = false;
	animation = Animations::GetInstance()->Get(tag, 0); // animation moving

	this->vx = ENEMY_WALKING_SPEED * direct;
	this->vy = 0;
	this->width = 32;
	this->height = 64;
	this->health = 1;
}

void Ghost::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Enemy::Update(dt, coObjects);
	if (!SIMON->timeusingstopwatch)
	{	
		vy += ENEMY_GRAVITY * dt;
		
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
				if (dynamic_cast<CBrick*>(e->obj)||dynamic_cast<Special_brick*>(e->obj))
				{
					if (nx != 0)
					{
						turn = true;
					}
					if (ny == -1)
					{
						this->vy = 0;
					}
				}
			}
		}
		if (turn)
		{
			vx = -vx;
			isReverse = !isReverse;
			turn = false;
		}
	}
}
Ghost::~Ghost()
{
}
