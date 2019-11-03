#include"Special_brick.h"

Special_brick::Special_brick(int type_id, int itemid)
{
	hit_effect = Sprites::GetInstance()->Get(TAG_EFFECT, TYPE_EFFECT_HIT);

	tag = TAG_SPECIAL_BRICK;
	item = itemid;
	type = type_id;
	vx = vy = 0;
	isDead = false;
	if (type == TYPE_SPECIAL_BRICK1)
	{
		width = 32;
		height = 32;
		animation = Animations::GetInstance()->Get(tag, TYPE_SPECIAL_BRICK1);
	}
	if (type == TYPE_SPECIAL_BRICK2)
	{
		width = 32;
		height = 32;
		animation = Animations::GetInstance()->Get(tag, TYPE_SPECIAL_BRICK2);
	}
}

void Special_brick::Render()
{
	animation->Render(x, y);
}

void Special_brick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	animation->Update();
}