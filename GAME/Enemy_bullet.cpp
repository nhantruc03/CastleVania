#include"Enemy_bullet.h"
#include"Camera.h"
#include"Simon.h"

Enemy_bullet::Enemy_bullet(float x, float y, int direction)
{
	this->tag = TAG_ENEMY;
	this->type = TYPE_ENEMY_BULLET;
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
	animation = Animations::GetInstance()->Get(tag, 8);
	hit_effect = Sprites::GetInstance()->Get(TAG_EFFECT, TYPE_EFFECT_HIT);
	this->vx = ENEMY_WALKING_SPEED*1.5 * direct;
	this->vy = 0;
	this->width = 10;
	this->height = 12;
	this->health = 1;
}

void Enemy_bullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!SIMON->timeusingstopwatch)
	{
		CGameObject::Update(dt, coObjects);
		x += dx;
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
Enemy_bullet::~Enemy_bullet()
{
}
