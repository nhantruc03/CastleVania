#pragma once
#include"Simon.h"
#include"SimonState.h"
#include"SimonWalkingState.h"
#include"SimonSittingState.h"

class SimonStandingState:public SimonState
{
public:
	SimonStandingState();
	void Update(float dt);
	void HandleKeyboard();
};

