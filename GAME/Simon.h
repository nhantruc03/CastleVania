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
	// score board
	int instages;
	int lives;
	int score;
	bool checkkillboss;
	int count_attack_after_kill_boss;
	int heart;

	bool outside;




	float timetorespawn;

	// about holy cross
	float timeuseholycross;
	float timetochangecolorwhileusingholycross;
	float limittimetochangecolorwhileusingholycross;
	bool usingholycross;

	
	//about item gold potion
	bool usinggoldpotion;

	//about item stop watch
	float timeusingstopwatch;

	// about item whip
	float upgrade_time;

	// about stair
	bool isgoingtostair;
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


	// about state
	int State;
	int prevState;
	bool sitting;
	bool attacking;
	bool jumping;
	bool falling;
	bool ishit;
	int untouchable;
	float delayforsitting;
	float untouchable_start;



	// about weapon
	int secondweapon;
	int numweaponcanthrow;
	int numcurrentweaponthrowing;
	vector<Weapon*>Weapons;
	int morningstarlevel;


	// about respawn
	float respawnx;
	float respawny;

	CAnimation *curAni;
	
	CSimon();

	void Respawn();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);

	

	void ChangeState(int newState);
	static CSimon* GetInstance();
	void Update_State();
	bool isinjured;
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	void StartUsingHolyCross();
	void LoadAnimation();
	void ChangeTexture(int temp);
	void ResetRespawn(float tempx=30, float tempy=5) { respawnx = tempx; respawny = tempy; }

};

