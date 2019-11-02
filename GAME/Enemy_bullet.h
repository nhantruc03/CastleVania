#pragma once
#include"Enemy.h"
#include"Brick.h"
class Enemy_bullet :public Enemy
{
public:
	Enemy_bullet(float x, float y, int direction);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	~Enemy_bullet();
};

