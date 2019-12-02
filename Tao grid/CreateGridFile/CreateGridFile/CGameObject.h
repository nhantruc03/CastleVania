#pragma once
#include <Windows.h>
#include <vector>

using namespace std;
class CGameObject;
typedef CGameObject * LPGAMEOBJECT;

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

	int tag;
	int type;



	int topcell, botcell, leftcell, rightcell;

	int direct;

public:
	virtual void SetPosition(float x, float y) { this->x = x, this->y = y; }

	CGameObject() {};
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) {
		left = x - width / 2;
		top = y - height / 2;
		right = left + width;
		bottom = top + height;
	};
	virtual RECT GetBoundingBox() {
		RECT temp;
		temp.left = x - width / 2;
		temp.top = y - height / 2;
		temp.right = temp.left + width;
		temp.bottom = temp.top + height;
		return temp;
	};
	~CGameObject() {};

};