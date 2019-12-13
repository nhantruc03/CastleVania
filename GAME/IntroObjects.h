#pragma once
#include"Animation.h"
#include"GameObject.h"
#define TAG_INTROBAT 16
#define TAG_INTROHELI 15
#define TAG_MAIN_MENU_BAT 17
class IntroObjects:public CGameObject
{
public:
	CAnimation* animation;
	IntroObjects(float x, float y, float vx, float vy, int type);
	~IntroObjects();

	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
};

