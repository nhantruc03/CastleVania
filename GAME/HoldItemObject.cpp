#include"HoldItemObject.h"

HoldItemObject::HoldItemObject(int type_id, int itemid)
{
	hit_effect = Sprites::GetInstance()->Get(TAG_EFFECT, TYPE_EFFECT_HIT);
	
	tag = TAG_HOLDER;
	item = itemid;
	type = type_id;

	vx = vy = 0;
	ishit = false;
	isBurn = false;
	isDead = false;
	if (type == TYPE_HOLDER_FIREPILLAR)
	{
		width = 32;
		height = 64;
		animation = Animations::GetInstance()->Get(tag, TYPE_HOLDER_FIREPILLAR);
	}
	if (type == TYPE_HOLDER_CANDLE)
	{
		width = 16;
		height = 32;
		animation = Animations::GetInstance()->Get(tag, TYPE_HOLDER_CANDLE);
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
	animation->Update();
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
	animation->isreverse = false;
	isBurn = true;
}

void HoldItemObject::isHit()
{
	ishit = true;
}
