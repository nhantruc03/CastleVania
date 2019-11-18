#pragma once
#include"Enemy.h"
#include"Brick.h"
#include"Weapon.h"
class Enemy_bullet :public Weapon
{
public:
	int direct;
	//bool ishit;
	Enemy_bullet(float x, float y, int direction, float vx = ENEMY_WALKING_SPEED * 1.5, float vy = 0);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void Render();
	~Enemy_bullet();
};

