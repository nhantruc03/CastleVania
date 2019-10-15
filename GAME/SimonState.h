#pragma once
#include"GameGlobal.h"
class SimonState
{
public:
	SimonState() {};
	virtual void Update(DWORD dt) = 0;
	virtual void HandleKeyboard() = 0;
	int StateName;
};

