#include "SimonFallingState.h"



SimonFallingState::SimonFallingState()
{
	StateName = SIMON_STATE_FALL;
}

void SimonFallingState::Update(float dt)
{
	this->HandleKeyboard();
	if (SIMON->y == 292-SIMON->height / 2 )
	{
		
			SIMON->jumping = false;
			SIMON->ChangeState(new SimonStandingState());
		
	}
}

void SimonFallingState::HandleKeyboard()
{
}

