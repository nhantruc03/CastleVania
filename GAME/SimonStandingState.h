#pragma once
#include"Simon.h"
#include"SimonState.h"
#include"SimonWalkingState.h"
#include"SimonSittingState.h"

class SimonStandingState:public SimonState
{
public:
	SimonStandingState();
	void Update(DWORD dt);
	void HandleKeyboard();
};

