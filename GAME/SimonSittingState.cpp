#include "SimonSittingState.h"



SimonSittingState::SimonSittingState()
{
	SIMON->sitting = true;
	SIMON->vx = 0;
	SIMON->y += 17 / 2;
	SIMON->height -= 17;
	StateName = SIMON_STATE_SITTING;
}

void SimonSittingState::Update(float dt)
{
	this->HandleKeyboard();
}

void SimonSittingState::HandleKeyboard()
{
	if (!keyCode[DIK_DOWN])
	{
		SIMON->sitting = false;
		SIMON->height += 17;
		SIMON->y -= 17 / 2;

		if (keyCode[DIK_LEFT] || keyCode[DIK_RIGHT])
		{
			SIMON->ChangeState(new SimonWalkingState());
		}
		else
		{
			SIMON->ChangeState(new SimonStandingState());
		}
	}
	else if (keyCode[DIK_RIGHT])
	{
		SIMON->isReverse = true;
	}
	else if (keyCode[DIK_LEFT])
	{
		SIMON->isReverse = false;
	}
}


