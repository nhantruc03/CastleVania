#include "SimonWalkingState.h"



SimonWalkingState::SimonWalkingState()
{
	SIMON->attacking = false;
	SIMON->sitting = false;
	SIMON->jumping = false;
	SIMON->vy = 0;
	SIMON->height = SIMON_HEIGHT;
	StateName = SIMON_STATE_WALKING;
}

void SimonWalkingState::Update(DWORD dt)
{
	this->HandleKeyboard();
}

void SimonWalkingState::HandleKeyboard()
{
	if (keyCode[DIK_RIGHT])
	{
		SIMON->isReverse = true;
		SIMON->vx = SIMON_WALKING_SPEED;
	}
	else if (keyCode[DIK_LEFT])
	{
		SIMON->isReverse = false;
		SIMON->vx = -SIMON_WALKING_SPEED;
	}
	else
	{
		SIMON->ChangeState(new SimonStandingState());
	}
}



