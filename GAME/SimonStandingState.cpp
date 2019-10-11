#include "SimonStandingState.h"



SimonStandingState::SimonStandingState()
{
	SIMON->height = SIMON_HEIGHT;
	SIMON->vx = 0;
	SIMON->vy = 0;
	SIMON->jumping = false;
	SIMON->sitting = false;
	SIMON->attacking = false;
	StateName = SIMON_STATE_IDLE;
}

void SimonStandingState::Update(float dt)
{
	this->HandleKeyboard();
}

void SimonStandingState::HandleKeyboard()
{
	// Nhấn phím di chuyển -> WALKING
	if (keyCode[DIK_LEFT] || keyCode[DIK_RIGHT])
	{
		SIMON->ChangeState(new SimonWalkingState());
	}
	// Nhấn phím DOWN -> SITTING
	else if (keyCode[DIK_DOWN])
	{
		SIMON->ChangeState(new SimonSittingState());
	}
}


