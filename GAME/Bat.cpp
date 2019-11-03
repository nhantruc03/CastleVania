#include "Bat.h"
#include"Camera.h"
#include"Simon.h"
Bat::Bat(float x, float y, int direction)
{
	this->tag = TAG_ENEMY;
	this->type = TYPE_ENEMY_BAT;
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
	animation = Animations::GetInstance()->Get(tag, 4);
	hit_effect = Sprites::GetInstance()->Get(TAG_EFFECT, TYPE_EFFECT_HIT);
	this->vx = ENEMY_WALKING_SPEED  * direct;
	this->vy = 0.03f;
	this->width = 32;
	this->height = 32;
	this->health = 1;
	prevY = y;
}

void Bat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!SIMON->timeusingstopwatch)
	{
		if (abs(y - prevY) >= 20)
		{
			vy = -vy;
		}
		CGameObject::Update(dt, coObjects);

		x += dx;
		y += dy;
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
}
Bat::~Bat()
{
}
