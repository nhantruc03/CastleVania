#pragma once
#include "GameObject.h"
//#include"GameGlobal.h"
#include"SimonState.h"
#include"SimonStandingState.h"
#include"SimonJumpingState.h"
#include"SimonAttackingState.h"
#include"SimonFallingState.h"
#define SIMON_WALKING_SPEED		0.1f
#define SIMON_JUMP_SPEED_Y		0.45f
#define SIMON_GRAVITY			0.02f

#define SIMON_STATE_IDLE			0
#define SIMON_STATE_WALKING			1
#define SIMON_STATE_JUMP			2
#define SIMON_STATE_FALL			3
#define SIMON_STATE_ATTACK			4
#define SIMON_STATE_SITTING			5
#define SIMON_STATE_SIT_ATTACKING	6

#define SIMON_ANI_IDLE				0
#define SIMON_ANI_WALKING			1
#define SIMON_ANI_JUMPING			2
#define SIMON_ANI_ATTACKING			3
#define SIMON_ANI_SITTING			4

#define SIMON_WIDTH					60
#define SIMON_HEIGHT				62

class CSimon : public CGameObject
{
	static CSimon * _instance;
public:
	bool UsingMorningStar;
	int morningstarlevel;
	CSimon();
	void Respawn();
	void UpdateNotAttacking() { this->attacking = false; }
	void Update(DWORD dt);
	void Render();
	void SetState(int state);
	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);
	int iskeydown(int keyCode);
	SimonState* State;
	CAnimation *curAni;
	void ChangeState(SimonState* newState);
	static CSimon* GetInstance();

};