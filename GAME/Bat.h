#pragma once
#include"Enemy.h"
#include"Brick.h"
#define BAT_VY 0.03f
#define DISTANCE_TOCHANGEVY 20
class Bat :public Enemy
{
public:
	float prevY;
	Bat(float x, float y, int direction);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	~Bat();
};

