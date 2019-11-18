#include"Enemy_bullet.h"
#include"Camera.h"
#include"Simon.h"

Enemy_bullet::Enemy_bullet(float x, float y, int direction, float vx , float vy )
{
	this->tag = TAG_WEAPON;
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
	animation = Animations::GetInstance()->Get(tag, 7);
	this->vx = vx * direct;
	this->vy = vy;
	this->width = 10;
	this->height = 12;
}

void Enemy_bullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (ishit)
	{
		listeffect.push_back(new hit(x - 8, y - 8));
		listeffect.push_back(new burn(x, y, 0));
		this->isDead = true;
	}
	if (!SIMON->timeusingstopwatch)
	{
		CGameObject::Update(dt, coObjects);
		x += dx;
		y += dy;
		
		animation->Update();
		if (!Camera::GetInstance()->IsContain(this->GetBoundingBox()))
		{
			this->isDead = true;
		}
	}
}
void Enemy_bullet::Render()
{
	animation->Render(x, y);
}
Enemy_bullet::~Enemy_bullet()
{
}
