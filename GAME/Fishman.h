#pragma once
#include"Enemy.h"
#include"Brick.h"
#include<time.h>
class Fishman :public Enemy
{
public:
	float timetoattack;
	bool canspawnbullet;
	bool isrunning;
	Fishman(float x, float y, int direction);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void run();
	void attack();
	bool attacking;
	~Fishman();
};
