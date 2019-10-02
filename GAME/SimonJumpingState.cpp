#include "SimonJumpingState.h"



SimonJumpingState::SimonJumpingState()
{
	
	if (SIMON->y = 292 - SIMON->height / 2)
	{
		SIMON->vy = -SIMON_JUMP_SPEED_Y;
		SIMON->jumping = true;
	}
	StateName = SIMON_STATE_JUMP;
}

void SimonJumpingState::Update(float dt)
{
	
	this->HandleKeyboard();
	if (SIMON->vy >= 0)
	{
		SIMON->ChangeState(new SimonFallingState());
	}
}

void SimonJumpingState::HandleKeyboard()
{

}


