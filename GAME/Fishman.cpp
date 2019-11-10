#include "Fishman.h"
#include"Camera.h"
#include"Simon.h"
#include"Enemy_bullet.h"
#include"Special_brick.h"
Fishman::Fishman(float x, float y, int direction)
{
	srand(time(NULL));
	this->tag = TAG_ENEMY;
	this->type = TYPE_ENEMY_FISHMAN;
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
	AddAnimation(tag, 5);
	AddAnimation(tag, 6);
	AddAnimation(tag, 7);
	animation = animations[0];
	hit_effect = Sprites::GetInstance()->Get(TAG_EFFECT, TYPE_EFFECT_HIT);
	this->vx = 0;
	this->vy = -0.5f;
	this->width = 32;
	this->height = 62;
	this->health = 1;
	isrunning = false;
	timetoattack = 5000;
	attacking = false;
	canspawnbullet = false;;
}

void Fishman::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!SIMON->timeusingstopwatch)
	{
		Enemy::Update(dt, coObjects);
		if ((vx > 0 && x > SIMON->x +64) || (vx < 0 && x < SIMON->x-64))
		{
			vx = -vx;
			isReverse = !isReverse;
			direct = -direct;
		}
		if (!isBurn)
		{
			if (timetoattack > 0)
			{
				timetoattack -= dt;
			}
			else
			{
				if (!attacking)
				{
					attack();
				}
			}
			if (attacking && animation->CheckEndAni())
			{
				animation->SetEndAniFalse();
				animation->currentFrame = -1;
				attacking = false;
				timetoattack = 5000 + (rand() % 3000);
				run();
			}
		}
		if (!isBurn)
		{
			vy += ENEMY_GRAVITY / 2 * dt;
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
				if (dynamic_cast<CBrick*>(e->obj) || dynamic_cast<Special_brick*>(e->obj))
				{
					x += dx;
					if (ny == 1)
					{
						y += dy;
					}
					if (ny == -1)
					{
						this->vy = 0;
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

void Fishman::run()
{
	vx = ENEMY_WALKING_SPEED/2 * direct;
	isrunning = true;
	animation = animations[1];
}

void Fishman::attack()
{
	//isrunning = false;
	this->vx = 0;
	animation = animations[2];
	attacking = true;
	canspawnbullet = true;
}

Fishman::~Fishman()
{
}
