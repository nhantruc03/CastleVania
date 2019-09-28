#pragma once
#include "Simon.h"
#include"GameGlobal.h"
class SimonState
{
public:
	SimonState() {};
	virtual void Update(float dt) = 0;
	virtual void HandleKeyboard() = 0;
	int StateName;
};

