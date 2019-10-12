#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <vector>
#include"AnimationsManager.h"
#include"Game.h"
//#include "Sprites.h"


using namespace std;
class CGameObject;
typedef CGameObject * LPGAMEOBJECT;

struct CCollisionEvent;
typedef CCollisionEvent * LPCOLLISIONEVENT;
struct CCollisionEvent
{
	CGameObject* obj;
	float t, nx, ny;
	CCollisionEvent(float t, float nx, float ny, LPGAMEOBJECT obj = NULL) { this->t = t; this->nx = nx; this->ny = ny; this->obj = obj; }

	static bool compare(const LPCOLLISIONEVENT &a, LPCOLLISIONEVENT &b)
	{
		return a->t < b->t;
	}
};


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
	int ani;
	vector<LPANIMATION> animations;

	int tag;
	int type;
	bool isDead;

	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt
	DWORD dt;

public:
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; }
	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents);
	void FilterCollision(
		vector<LPCOLLISIONEVENT> &coEvents,
		vector<LPCOLLISIONEVENT> &coEventsResult,
		float &min_tx,
		float &min_ty,
		float &nx,
		float &ny);


	void AddAnimation(int tag, int index);

	CGameObject();
	bool IsContain(float ol, float ot, float or, float ob)
	{
		float left, top, right, bottom;
		GetBoundingBox(left, top, right, bottom);
		if (ol> right || ot> bottom || ob< top || or< left)
		{
			return false;
		}
		return true;
	};
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) {
		left = x - width / 2;
		top = y - height / 2;
		right = left + width;
		bottom = top+ height;
	};
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void setreverse(bool check) { this->isReverse = check; };
	//void Render();
	virtual void Render() {}
	~CGameObject();

};