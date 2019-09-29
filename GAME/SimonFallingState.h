#pragma once
#include"Simon.h"
#include"SimonState.h"
#include"SimonWalkingState.h"
class SimonFallingState:public SimonState
{
public:
	SimonFallingState();
	void Update(float dt);
	void HandleKeyboard();
};

