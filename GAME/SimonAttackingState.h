#pragma once
#include"Simon.h"
#include"SimonState.h"
#include"SimonWalkingState.h"
#include"SimonSittingState.h"
#include"SimonStandingState.h"
#include"SimonFallingState.h"
class SimonAttackingState:public SimonState
{
private:
	int curstate;
public:

	SimonAttackingState();
	void Update(float dt);
	void HandleKeyboard();
};

