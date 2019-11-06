#include"MorningStar.h"
#include"Simon.h"
#include"Special_brick.h"
#include"Enemy.h"
MorningStar::MorningStar(int level)
{
	this->level = level;
	AddAnimation(tag, 0);
	AddAnimation(tag, 1);
	AddAnimation(tag, 2);
	if (level == 1)
	{
		animation = animations[0];
		width = 44;
		height = 16;
	}
	else if (level == 2)
	{
		this->animation = animations[1];
		width = 44;
		height = 12;
	}
	else
	{
		this->animation = animations[2];
		width = 75;
		height = 12;
	}

	vx = vy = 0;
	type = TYPE_WEAPON_MORNINGSTAR;
	available = false;
	isDead = false;
}

void MorningStar::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (SIMON->State!= STATE_ATTACK && SIMON->State!= STATE_SIT_ATTACKING && SIMON->State!=STATE_ATTACK_ONSTAIR_DOWN && SIMON->State!=STATE_ATTACK_ONSTAIR_UP)
	{
		this->isDead = true;
		available = false;
	}
	if (available)
	{
		for (UINT i = 0; i < coObjects->size(); i++)
		{
			float l, t, r, b;
			coObjects->at(i)->GetBoundingBox(l, t, r, b);
			if (this->IsContain(l, t, r, b) == true)
			{
				switch (coObjects->at(i)->tag)
				{
				case TAG_SPECIAL_BRICK:
					coObjects->at(i)->isDead=true;
					break;
				case TAG_HOLDER:
					coObjects->at(i)->isHit();
					break;
				case TAG_ENEMY:
					if (dynamic_cast<Enemy*>(coObjects->at(i))->timeshowhiteffect<=0)
					{
						coObjects->at(i)->isHit();
					}
					break;
				default:
					break;
				}

			}
		}
	}
}

void MorningStar::Render()
{
	int frameIndex = SIMON->curAni->currentFrame - 1;
	if (frameIndex != 0 && frameIndex != 1 && frameIndex != 2) return;

	CSprite* sprite = animation->frames[frameIndex]->GetSprite();

	sprite->isreverse = this->isReverse;
	x = SIMON->x;
	y = SIMON->y;
	switch (frameIndex)
	{
	case 0:
		x += isReverse ? -36 : 36;
		if (SIMON->State == STATE_ATTACK_ONSTAIR_UP)
		{
			x += isReverse ? -3 : 3;
		}
		if (SIMON->State== STATE_ATTACK || SIMON->State==STATE_ATTACK_ONSTAIR_DOWN || SIMON->State==STATE_ATTACK_ONSTAIR_UP)
		{
			y += 7;
		}
		else y += 15;
		break;

	case 1:
		x += (isReverse ? -24 : 24);
		if (SIMON->State == STATE_ATTACK_ONSTAIR_UP)
		{
			x += isReverse ? -12 : 12;
		}
		if (SIMON->State== STATE_ATTACK || SIMON->State == STATE_ATTACK_ONSTAIR_DOWN || SIMON->State == STATE_ATTACK_ONSTAIR_UP)
		{
			y -= 4;
		}
		else y += 3;
		break;
	case 2:
		if (level != 3)
		{
			x += (isReverse ? 50 : -50);
			if (SIMON->State == STATE_ATTACK_ONSTAIR_DOWN )
			{
				x+= (isReverse ? 1 : -1);
			}
		}
		else
		{
			x += (isReverse ? 63 : -63);
			if (SIMON->State == STATE_ATTACK_ONSTAIR_DOWN)
			{
				x += (isReverse ? 2 : -2);
			}
		}
		if (SIMON->State == STATE_ATTACK_ONSTAIR_UP)
		{
			x += (isReverse ? -6 : 6);
		}
		if (SIMON->State== STATE_ATTACK)
		{
			y -= 8;
		}
		else if (SIMON->State == STATE_ATTACK_ONSTAIR_DOWN || SIMON->State == STATE_ATTACK_ONSTAIR_UP)
		{
			y -= 10;
		}
		else y -= 3;
		available = true;

		break;
	}
	sprite->Draw(x, y);

}
