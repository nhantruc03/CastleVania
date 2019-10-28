#include "Ghost.h"
#include"Camera.h"


Ghost::Ghost(float x, float y, int direction)
{
	this->x = x;
	this->y = y;
	this->direct = direction;
	if (direct == -1)
	{
		isReverse = false;
	}
	else
		isReverse = true;

	this->isDead = false;
	this->ishit = false;
	animation = Animations::GetInstance()->Get(8, 0);

	hit_effect = Sprites::GetInstance()->Get(5, 3);
	this->vx = ENEMY_WALKING_SPEED * direct;
	this->vy = 0;
	this->width = 32;
	this->height = 64;
	this->tag = TAG_ENEMY;
	this->type = TYPE_ENEMY_GHOST;
	this->health = 1;
}

void Ghost::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	vy += ENEMY_GRAVITY * dt;
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
				if (nx != 0)
				{
					this->vx *= -1;
					this->isReverse = !isReverse;
				}
				if (ny == -1)
				{
					this->vy = 0;
				}
			}
		}
	}
	animation->Update();
	if (isBurn)
	{
		vx = vy = 0;
		if (animation->CheckEndAni())
		{
			isDead = true;
			animation->SetEndAniFalse();
			animation->currentFrame = -1;

		}
	}
	if (!Camera::GetInstance()->IsContain(this->GetBoundingBox()))
	{
		this->isDead = true;
	}
}
Ghost::~Ghost()
{
}
