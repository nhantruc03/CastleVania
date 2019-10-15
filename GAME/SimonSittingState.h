#pragma once
#include"Simon.h"
#include"SimonState.h"
#include"SimonWalkingState.h"	
#include"SimonStandingState.h"

class SimonSittingState:public SimonState
{
public:
	SimonSittingState();
	void Update(DWORD dt);
	void HandleKeyboard();
};

