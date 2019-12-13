#include "IntroObjects.h"




IntroObjects::IntroObjects(float x, float y, float vx, float vy, int type)
{
	this->x = x;
	this->y = y;
	this->vx = vx;
	this->vy = vy;
	this->type = type;
	switch (type)
	{
	case TYPE_INTRO_HELI:
		animation = Animations::GetInstance()->Get(TAG_INTROHELI, 0);
		break;
	case TYPE_INTRO_BAT:
		animation = Animations::GetInstance()->Get(TAG_INTROBAT, 0);
		break;
	case TYPE_INTRO_SIMON:
		animation = Animations::GetInstance()->Get(TAG_SIMON, 1); // ani walking
		break;
	case TYPE_INTRO_MENUBAT:
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
