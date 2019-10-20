#include"HoldItemObject.h"

HoldItemObject::HoldItemObject(int type_id, int itemid)
{
	hit_effect = Sprites::GetInstance()->Get(5, 4);
	ishit = false;
	tag = TAG_HOLDER;
	isBurn = false;
	item = itemid;
	type = type_id;
	if (type == TYPE_HOLDER_FIREPILLAR)
	{
		width = 32;
		height = 64;
		animation = Animations::GetInstance()->Get(tag, 0);
		vx = vy = 0;
		isBurn = false;
		isDead = false;
	}
}

void HoldItemObject::Render()
{
	if (ishit)
	{
		hit_effect->Draw(x-8, y-8);
		Burn();
	}
	animation->Render(x, y);
}

void HoldItemObject::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isBurn)
	{
		if (animation->CheckEndAni())
		{
			isDead = true;
			animation->SetEndAniFalse();
			animation->currentFrame = -1;

		}
	}
}

void HoldItemObject::Burn()
{
	animation = Animations::GetInstance()->Get(TAG_EFFECT, TYPE_EFFECT_BURN);
	isBurn = true;
}

void HoldItemObject::isHit()
{
	ishit = true;
}
