#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <vector>
#include"AnimationsManager.h"
//#include "Sprites.h"


using namespace std;

class CGameObject
{
public:
	bool sitting;
	bool attacking;
	bool jumping;
	float x;
	float y;
	bool isReverse;
	float vx;
	float vy;

	int nx;
	float width;
	float height;
	int state;
	int ani;
	vector<LPANIMATION> animations;

	int tag;
	int type;
	bool isDead;

public:
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	//void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }

	void SetState(int state) { this->state = state; }
	int GetState() { return this->state; }


	void AddAnimation(int tag, int index);

	CGameObject();

	void Update(DWORD dt);
	void setreverse(bool check) { this->isReverse = check; };
	//void Render();
	virtual void Render() {}
	~CGameObject();

};