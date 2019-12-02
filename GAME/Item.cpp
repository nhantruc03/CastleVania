#include"Item.h"

Item::Item(int type_id)
{
	tag = TAG_ITEM;
	vx = vy = 0;
	ExistTime = 2000;
	isDead = false;
	type = type_id;
	animation = Animations::GetInstance()->Get(tag, type);
	vy = ITEM_VY;
	if (type == TYPE_ITEM_BIG_HEART)
	{
		width = 24;
		height = 20;
	}
	else if (type == TYPE_ITEM_WHIP)
	{
		width = 32;
		height = 32;
	}
	else if (type == TYPE_ITEM_DAGGER)
	{
		width = 32;
		height = 18;
	}
	else if (type == TYPE_ITEM_HEART)
	{
		width = 16;
		height = 16;
		vy = ITEM_VY / 4;
		vx = ITEM_VX;
	}
	else if (type == TYPE_ITEM_MONEY_1000)
	{
		width = 30;
		height = 30;
	}
	else if (type == TYPE_ITEM_MONEY_700)
	{
		width = 30;
		height = 30;
	}
	else if (type == TYPE_ITEM_MONEY_400)
	{
		width = 30;
		height = 30;
	}
	else if (type == TYPE_ITEM_HOLY_WATER)
	{
		width = 32;
		height = 32;
	}
	else if (type == TYPE_ITEM_HOLY_CROSS)
	{
		width = 32;
		height = 32;
	}
	else if (type == TYPE_ITEM_STOP_WATCH)
	{
		width = 30;
		height = 32;
	}
	else if (type == TYPE_ITEM_CHICKEN)
	{
		width = 32;
		height = 26;
	}
	else if (type == TYPE_ITEM_AXE)
	{
		width = 30;
		height = 32;
	}
	else if (type == TYPE_ITEM_DOUBLE_SHOT)
	{
		width = 27;
		height = 28;
	}
	else if (type == TYPE_ITEM_GOLD_POTION)
	{
		width = 26;
		height = 32;
	}
	else if (type == TYPE_ITEM_CRYSTAL)
	{
		width = 28;
		height = 32;
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
		if (type != TYPE_ITEM_CRYSTAL)
		{
			this->isDead = true;
		}
	}
}
