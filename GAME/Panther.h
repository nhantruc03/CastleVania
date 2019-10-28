#pragma once
#include"Enemy.h"
#include"Brick.h"
class Panther :public Enemy
{
public:
	bool available;
	bool issleeping;
	bool checkjump_only1time;
	bool isrunning;
	float distancebeforejump;
	float prevX;
	Panther(float x, float y, int direction, float distancebeforejump);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void jump();
	void run();
	~Panther();
};

