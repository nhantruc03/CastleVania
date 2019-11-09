#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <vector>
#include"Animations.h"
#include"Game.h"

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
	int id;

	float x;
	float y;
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
	bool isBurn;
	bool isReverse;

	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt
	DWORD dt;


	int topcell, botcell, leftcell, rightcell;
	int spawnx, spawny;

public:
	virtual void SetPosition(float x, float y) { this->x = x, this->y = y; }
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
	virtual RECT GetBoundingBox() {
		RECT temp;
		temp.left = x - width / 2;
		temp.top = y - height / 2;
		temp.right = temp.left + width;
		temp.bottom = temp.top + height;
		return temp;
	};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render() {}
	virtual void Burn() {};
	virtual void isHit() {};
	~CGameObject();

};