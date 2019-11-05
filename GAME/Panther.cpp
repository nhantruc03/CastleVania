#include "Panther.h"
#include"Simon.h"
Panther::Panther(float x, float y, int direction, float distancebeforejump)
{
	this->isDead = false;
	this->ishit = false;
	this->tag = TAG_ENEMY;
	this->type = 1;
	AddAnimation(tag, 1);
	AddAnimation(tag, 2);
	AddAnimation(tag, 3);
	this->distancebeforejump = distancebeforejump;
	issleeping = true;
	checkjump_only1time = false;
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
	hit_effect = Sprites::GetInstance()->Get(TAG_EFFECT, TYPE_EFFECT_HIT);
	this->vx = 0;
	this->vy = 0;
	this->width = 64;
	this->height = 32;
	this->health = 1;
	animation = animations[0];
}

void Panther::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!SIMON->timeusingstopwatch)
	{
		if (abs(SIMON->x - this->x) <= 160 && issleeping)
		{
			wakeup();
		}
		if (abs(x - prevX) >= distancebeforejump && !issleeping)
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
					if (checkjump_only1time)
					{
						x += dx;
					}
					if (ny == -1)
					{
						this->vy = 0;
						if (checkjump_only1time)
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
		if (!Camera::GetInstance()->IsContain(this->GetBoundingBox()) && !issleeping)
		{
			this->isDead = true;
		}
	}
}

void Panther::jump()
{
	if (checkjump_only1time == true)
		return;
	vy = -ENEMY_JUMP_SPEED_Y;
	checkjump_only1time = true;
	isrunning = false;
	animation = animations[2];
}

void Panther::wakeup()
{
	isrunning = true;
	issleeping = false;
	vx = ENEMY_WALKING_SPEED * 2 * direct;
	animation = animations[1];
}

void Panther::run()
{
	vx = ENEMY_WALKING_SPEED * -direct;
	this->isReverse = !isReverse;
	isrunning = true;
	animation = animations[1];
}

Panther::~Panther()
{
}
