#include"Item.h"

Item::Item(int type_id)
{
	tag = TAG_ITEM;
	vx = 0;
	vy = 0.2f;
	ExistTime = 2000;
	isDead = false;
	type = type_id;
	if (type == TYPE_ITEM_BIG_HEART)
	{
		animation = Animations::GetInstance()->Get(TAG_ITEM, 0);
		width = 24;
		height = 20;
		vx = 0;
		vy = 0.2f;
	}
	else if (type == TYPE_ITEM_WHIP)
	{
		animation = Animations::GetInstance()->Get(TAG_ITEM, 1);
		width = 32;
		height = 32;
		vx = 0;
		vy = 0.2f;
	}
	else if (type == TYPE_ITEM_DAGGER)
	{
		animation = Animations::GetInstance()->Get(TAG_ITEM, 2);
		width = 32;
		height = 18;
		vx = 0;
		vy = 0.2f;
	}
}

void Item::Render()
{
	animation->Render(x, y);
}
void Item::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	CalcPotentialCollisions(coObjects, coEvents);
	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		x += min_tx * dx + nx * 0.2f;		// nx*0.2f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.2f;

		if (nx < 0) vx = 0;
		if (ny < 0) vy = 0;
		
	}
	ExistTime -= dt;
	if (ExistTime <= 0)
	{
		this->isDead = true;
	}
}
