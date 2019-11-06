#pragma once
#include"GameObject.h"
#include"Animations.h"
class Special_brick :public CGameObject
{
protected:
	CAnimation* animation;
	LPSPRITE hit_effect;

public:
	bool check_spawnitem;
	int item;
	Special_brick(int type_id, int itemid);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
};

