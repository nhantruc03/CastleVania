#pragma once
#include"GameObject.h"
#include"Animations.h"
class HoldItemObject:public CGameObject 
{
protected:
	CAnimation* animation;
	LPSPRITE hit_effect;
	
public:
	bool ishit;
	int item;
	HoldItemObject(int type_id, int itemid);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void Burn();
	void isHit();
};

