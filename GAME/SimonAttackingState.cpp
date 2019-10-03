#include "SimonAttackingState.h"



SimonAttackingState::SimonAttackingState()
{
	
	curstate = SIMON->State->StateName;
	SIMON->attacking = true;
	if (SIMON->sitting)
	{
		StateName = SIMON_STATE_SIT_ATTACKING;
	}
	else
	{
		StateName = SIMON_STATE_ATTACK;
	}
}

void SimonAttackingState::Update(float dt)
{
	this->HandleKeyboard();
	if (SIMON->curAni->CheckEndAni())
	{
		SIMON->attacking = false;
		SIMON->UsingMorningStar = false;
		SIMON->curAni->SetEndAniFalse();
		switch (curstate)
		{
		case SIMON_STATE_SITTING:
			SIMON->height += 17;
			SIMON->y -= 17 / 2;
			SIMON->ChangeState(new SimonSittingState());
			break;
		case SIMON_STATE_IDLE:case SIMON_STATE_WALKING:case SIMON_STATE_FALL:
			SIMON->ChangeState(new SimonStandingState());
			break;
		case SIMON_STATE_JUMP:
			SIMON->ChangeState(new SimonFallingState());
			break;
		}
	}
	else
	{
		switch (curstate)
		{
		case SIMON_STATE_WALKING:
			SIMON->vx = 0;
			break;
		case SIMON_STATE_FALL:
			SIMON->vx = 0;
			break;
		}

	}
}

void SimonAttackingState::HandleKeyboard()
{
}


