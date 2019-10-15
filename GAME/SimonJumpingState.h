#pragma once
#include"Simon.h"
#include"SimonState.h"
#include"SimonWalkingState.h"	
#include"SimonStandingState.h"
class SimonJumpingState:public SimonState
{
public:
	SimonJumpingState();
	void Update(DWORD dt);
	void HandleKeyboard();
};

