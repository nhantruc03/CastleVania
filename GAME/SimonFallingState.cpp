#include "SimonFallingState.h"



SimonFallingState::SimonFallingState()
{
	SIMON->height = SIMON_HEIGHT;
	StateName = STATE_FALL;
}

void SimonFallingState::Update(DWORD dt)
{
	this->HandleKeyboard();
	if (SIMON->vy==0)
	{
		SIMON->ChangeState(new SimonStandingState());
	}
}

void SimonFallingState::HandleKeyboard()
{
}

