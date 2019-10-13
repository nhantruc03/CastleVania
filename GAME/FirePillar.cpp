#include "FirePillar.h"



FirePillar::FirePillar()
{
	tag = TAG_HOLDER;
	isDead = false;
	width = 32;
	height = 64;
	animation = AnimationsManager::GetInstance()->Get(TAG_HOLDER, 0);
	vx = vy = 0;
	isDead = false;
}

void FirePillar::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	
}

FirePillar::~FirePillar()
{
}
