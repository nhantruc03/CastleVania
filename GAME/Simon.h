#pragma once
#include "GameObject.h"
#include"GameGlobal.h"
//#include"Weapon.h"
//#include"SimonState.h"
//#include"WeaponFactory.h"
#include"SimonStandingState.h"
#include"SimonJumpingState.h"
#include"SimonAttackingState.h"
#include"SimonFallingState.h"
#include<unordered_set>

class CSimon : public CGameObject
{
	static CSimon * _instance;
public:
	unordered_set<CGameObject*>Weapons;
	bool UsingMorningStar;
	int morningstarlevel;
	CSimon();
	void Respawn();
	void Update(DWORD dt);
	void Render();
	void SetState(int state);
	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);
	SimonState* State;
	CAnimation *curAni;
	void ChangeState(SimonState* newState);
	static CSimon* GetInstance();

};

