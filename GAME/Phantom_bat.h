#pragma once
#include"Enemy.h"
#include"Brick.h"
#define STATE_BODY_ATTACK_1 0
#define STATE_GO_POS_1 1
#define STATE_IDLE 2
#define STATE_GO_POS_2 3
#define STATE_GO_POS_3 4
#define STATE_GO_POS_4 5
#define STATE_GO_POS_5 6
#define STATE_BODY_ATTACK_2 7
#define STATE_SHOOT 8

#define TAGGETX_POS1 5376
#define TARGETY_POS1 208

#define TAGGETX_POS2 5232
#define TARGETY_POS2 144

#define TAGGETX_POS3 5321
#define TARGETY_POS3 112

#define TAGGETX_POS4 5472
#define TARGETY_POS4 112

#define TAGGETX_POS5 5552
#define TARGETY_POS5 144



class Phantom_bat :public Enemy
{
public:
	float bulletvx, bulletvy;
	bool canshoot;
	bool attacking;
	int prevState;
	int state;
	bool attackstraigt;
	bool attackcurve;
	bool ready;
	float timewait;
	float prevY;
	float prevX;
	float targetX, targetY;
	Phantom_bat();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void ChangeState(int newState);
	void Update_State();
	~Phantom_bat();
};

