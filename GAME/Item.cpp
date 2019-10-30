#include"Item.h"

Item::Item(int type_id)
{
	rewarded = false;
	tag = TAG_ITEM;
	vx = vy = 0;
	ExistTime = 2000;
	isDead = false;
	type = type_id;
	timetoshoweffect = 1000;
	if (type == TYPE_ITEM_BIG_HEART)
	{
		animation = Animations::GetInstance()->Get(tag, 0);
		width = 24;
		height = 20;
		vy = 0.2f;
	}
	else if (type == TYPE_ITEM_WHIP)
	{
		animation = Animations::GetInstance()->Get(tag, 1);
		width = 32;
		height = 32;
		vy = 0.2f;
	}
	else if (type == TYPE_ITEM_DAGGER)
	{
		animation = Animations::GetInstance()->Get(tag, 2);
		width = 32;
		height = 18;
		vy = 0.2f;
	}
	else if (type == TYPE_ITEM_HEART)
	{
		animation = Animations::GetInstance()->Get(tag, 3);
		width = 16;
		height = 16;
		vy = 0.05f;
		vx = 0.1f;
	}
	else if (type == TYPE_ITEM_MONEY_1000)
	{
		animation = Animations::GetInstance()->Get(tag, 4);
		width = 30;
		height = 30;
		vy = 0.2f;
	}
	else if (type == TYPE_ITEM_MONEY_700)
	{
		effect = Sprites::GetInstance()->Get(5, 5);
		animation = Animations::GetInstance()->Get(tag, 5);
		width = 30;
		height = 30;
		vy = 0.2f;
	}
	else if (type == TYPE_ITEM_MONEY_400)
	{
		effect = Sprites::GetInstance()->Get(5, 4);
		animation = Animations::GetInstance()->Get(tag, 6);
		width = 30;
		height = 30;
		vy = 0.2f;
	}
	else if (type == TYPE_ITEM_HOLY_WATER)
	{
		animation = Animations::GetInstance()->Get(tag, 7);
		width = 32;
		height = 32;
		vy = 0.2f;
	}
	else if (type == TYPE_ITEM_HOLY_CROSS)
	{
		animation = Animations::GetInstance()->Get(tag, 8);
		width = 32;
		height = 32;
		vy = 0.2f;
	}
	else if (type == TYPE_ITEM_STOP_WATCH)
	{
		animation = Animations::GetInstance()->Get(tag, 9);
		width = 30;
		height = 32;
		vy = 0.2f;
	}
}

void Item::Render()
{
	if (rewarded)
	{
		effect->Draw(x + 32, y);
	}
	else
	{
		animation->Render(x, y);
	}
}
void Item::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//effect->Draw(x + 8, y);
	if (rewarded)
	{
		timetoshoweffect -= dt;
		if (timetoshoweffect <= 0)
		{
			this->isDead = true;
		}
	}
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
