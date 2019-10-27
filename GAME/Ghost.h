#pragma once
#include"Enemy.h"
#include"Brick.h"
class Ghost:public Enemy
{
public:
	Ghost(float x, float y, int direction);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	/*void Burn();
	void isHit() { ishit = true; }
	void Render();*/
	~Ghost();
};

