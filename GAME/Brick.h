#pragma once
#include "GameObject.h"
class CBrick : public CGameObject
{
public:
	CBrick()
	{
		tag = TAG_BRICK;
		width = 32;
		height = 32;
		isDead = false;
	}
};