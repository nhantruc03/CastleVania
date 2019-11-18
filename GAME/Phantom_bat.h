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

