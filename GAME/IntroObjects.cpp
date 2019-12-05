#include "IntroObjects.h"




IntroObjects::IntroObjects(float x, float y, float vx, float vy, int direct, int type)
{
	this->x = x;
	this->y = y;
	this->vx = vx * direct;
	this->vy = vy;
	this->type = type;
	switch (type)
	{
	case 0:
		animation = Animations::GetInstance()->Get(TAG_INTROHELI, 0);
		break;
	case 1:
		animation = Animations::GetInstance()->Get(TAG_INTROBAT, 0);
		break;
	case 2:
		animation = Animations::GetInstance()->Get(TAG_SIMON, 1);
		break;
	case 3:
		animation = Animations::GetInstance()->Get(TAG_MAIN_MENU_BAT, 0);
		break;
	}

}

IntroObjects::~IntroObjects()
{
}

void IntroObjects::Render()
{
	animation->Render(x, y);
}

void IntroObjects::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	x += dx;
	y += dy;
	animation->Update();
}
