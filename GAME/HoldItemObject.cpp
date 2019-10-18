#include"HoldItemObject.h"

HoldItemObject::HoldItemObject(int type_id, int itemid)
{
	tag = TAG_HOLDER;
	isBurn = false;
	item = itemid;
	if (type_id == TYPE_HOLDER_FIREPILLAR)
	{
		type = TYPE_HOLDER_FIREPILLAR;
		width = 32;
		height = 64;
		animation = Animations::GetInstance()->Get(TAG_HOLDER, 0);
		vx = vy = 0;
		isBurn = false;
		isDead = false;
	}
}

void HoldItemObject::Render()
{
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
