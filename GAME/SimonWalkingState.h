#pragma once
#include"Simon.h"
#include"SimonState.h"
#include"SimonStandingState.h"
#include"SimonSittingState.h"
class SimonWalkingState:public SimonState
{
public:
	SimonWalkingState();
	void Update(DWORD dt);
	void HandleKeyboard();
};

