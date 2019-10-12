#pragma once
#include "GameObject.h"
#include"GameGlobal.h"
#include"SimonStandingState.h"
#include"SimonJumpingState.h"
#include"SimonAttackingState.h"
#include"SimonFallingState.h"
#include<unordered_set>

class CSimon : public CGameObject
{
	static CSimon * _instance;
public:
	bool throwing;
	vector<CGameObject*>Weapons;
	bool UsingMorningStar;
	int morningstarlevel;
	CSimon();
	void Respawn();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);
	SimonState* State;
	CAnimation *curAni;
	void ChangeState(SimonState* newState);
	static CSimon* GetInstance();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);

};

