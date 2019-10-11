#include "SimonFallingState.h"



SimonFallingState::SimonFallingState()
{
	SIMON->height = SIMON_HEIGHT;
	StateName = SIMON_STATE_FALL;
}

void SimonFallingState::Update(float dt)
{
	this->HandleKeyboard();
	if (SIMON->vy==0)
	{
		SIMON->jumping = false;
		SIMON->ChangeState(new SimonStandingState());
	}
}

void SimonFallingState::HandleKeyboard()
{
}

