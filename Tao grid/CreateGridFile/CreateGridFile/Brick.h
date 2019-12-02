#pragma once
#include "CGameObject.h"
class CBrick : public CGameObject
{
public:
	CBrick()
	{
		tag = 7;
		width = 32;
		height = 32;
	}
};