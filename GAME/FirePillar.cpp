#include "FirePillar.h"



FirePillar::FirePillar()
{
	type = TYPE_HOLDER_FIREPILLAR;
	tag = TAG_HOLDER;
	width = 32;
	height = 64;
	animation = Animations::GetInstance()->Get(TAG_HOLDER, 0);
	vx = vy = 0;
	isBurn = false;
	isDead = false;
}

FirePillar::~FirePillar()
{
}
