#pragma once
#include "GameObject.h"
class CBrick : public CGameObject
{
public:
	CBrick()
	{
		tag = NULL;
		width = 32;
		height = 32;
	}
	virtual void Render();
	//virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};