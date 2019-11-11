#pragma once
#include "GameObject.h"
#include"GameGlobal.h"
#include<unordered_set>
#include"Weapon.h"
#include<time.h>
class CSimon : public CGameObject
{
	static CSimon * _instance;
public:
	DWORD timeuseholycross;
	DWORD timetochangecolorwhileusingholycross;
	DWORD limittimetochangecolorwhileusingholycross;
	bool usingholycross;

	float delayforsitting;

	bool isgoingtostair;

	float timeusingstopwatch;
	bool falling;
	bool ishit;
	int untouchable;
	DWORD untouchable_start;
	int stair_type;
	bool gotoleft;
	bool goup;
	bool gotoright;
	bool godown;
	RECT stair_collide;
	void inoutstair_handle(DWORD dt);
	bool isCollidewith_UPLTR;
	bool isCollidewith_UPRTL;
	bool isCollidewith_DWNLTR;
	bool isCollidewith_DWNRTL;
	float isWalkingOnStair;
	float prevY;
	float prevX;
	bool isOnStair;
	bool check_auto_move;
	float upgrade_time;
	int prevState;
	bool sitting;
	bool attacking;
	bool jumping;
	int heart;

	int secondweapon;
	bool throwing;
	int numweaponcanthrow;
	int numcurrentweaponthroing;

	vector<Weapon*>Weapons;
	int morningstarlevel;
	CSimon();
	void Respawn();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);
	int State;
	CAnimation *curAni;
	void ChangeState(int newState);
	static CSimon* GetInstance();
	void Update_State();
	bool isinjured;
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	void StartUsingHolyCross();

	//virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);

};

