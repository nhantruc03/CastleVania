#include"Item.h"

Item::Item(int type_id)
{
	tag = TAG_ITEM;
	vx = vy = 0;
	ExistTime = 2000;
	isDead = false;
	type = type_id;
	if (type == TYPE_ITEM_BIG_HEART)
	{
		animation = Animations::GetInstance()->Get(tag, TYPE_ITEM_BIG_HEART);
		width = 24;
		height = 20;
		vy = 0.2f;
	}
	else if (type == TYPE_ITEM_WHIP)
	{
		animation = Animations::GetInstance()->Get(tag, TYPE_ITEM_WHIP);
		width = 32;
		height = 32;
		vy = 0.2f;
	}
	else if (type == TYPE_ITEM_DAGGER)
	{
		animation = Animations::GetInstance()->Get(tag, TYPE_ITEM_DAGGER);
		width = 32;
		height = 18;
		vy = 0.2f;
	}
	else if (type == TYPE_ITEM_HEART)
	{
		animation = Animations::GetInstance()->Get(tag, TYPE_ITEM_HEART);
		width = 16;
		height = 16;
		vy = 0.05f;
		vx = 0.1f;
	}
	else if (type == TYPE_ITEM_MONEY_1000)
	{
		animation = Animations::GetInstance()->Get(tag, TYPE_ITEM_MONEY_1000);
		width = 30;
		height = 30;
		vy = 0.2f;
	}
	else if (type == TYPE_ITEM_MONEY_700)
	{
		animation = Animations::GetInstance()->Get(tag, TYPE_ITEM_MONEY_700);
		width = 30;
		height = 30;
		vy = 0.2f;
	}
	else if (type == TYPE_ITEM_MONEY_400)
	{
		animation = Animations::GetInstance()->Get(tag, TYPE_ITEM_MONEY_400);
		width = 30;
		height = 30;
		vy = 0.2f;
	}
	else if (type == TYPE_ITEM_HOLY_WATER)
	{
		animation = Animations::GetInstance()->Get(tag, TYPE_ITEM_HOLY_WATER);
		width = 32;
		height = 32;
		vy = 0.2f;
	}
	else if (type == TYPE_ITEM_HOLY_CROSS)
	{
		animation = Animations::GetInstance()->Get(tag, TYPE_ITEM_HOLY_CROSS);
		width = 32;
		height = 32;
		vy = 0.2f;
	}
	else if (type == TYPE_ITEM_STOP_WATCH)
	{
		animation = Animations::GetInstance()->Get(tag, TYPE_ITEM_STOP_WATCH);
		width = 30;
		height = 32;
		vy = 0.2f;
	}
	else if (type == TYPE_ITEM_CHICKEN)
	{
		animation = Animations::GetInstance()->Get(tag, TYPE_ITEM_CHICKEN);
		width = 32;
		height = 26;
		vy = 0.2f;
	}
}

void Item::Render()
{
	animation->Render(x, y);
}
void Item::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (abs(x - prevX) >= 16)
	{
		vx = -vx;
	}
	animation->Update();
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

		if (nx < 0) vx = 0;
		if (ny < 0)
		{
			vx = vy = 0;
		}
		
	}
	ExistTime -= dt;
	if (ExistTime <= 0)
	{
		this->isDead = true;
	}
}
