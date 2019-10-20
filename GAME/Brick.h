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
		isDead = false;
	}
};