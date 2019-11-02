#pragma once
#include"Enemy.h"
#include"Brick.h"
class Bat :public Enemy
{
public:
	float prevY;
	Bat(float x, float y, int direction);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	~Bat();
};

