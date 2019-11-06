#pragma once
#include"Enemy.h"
#include"Brick.h"
class Panther :public Enemy
{
public:
	RECT brick;
	bool available;
	bool issleeping;
	bool isjumping;
	bool isrunning;
	float prevX;
	Panther(float x, float y, int direction);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void jump();
	void wakeup();
	void run();
	~Panther();
};

