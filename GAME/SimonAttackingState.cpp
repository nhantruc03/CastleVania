#include "SimonAttackingState.h"



SimonAttackingState::SimonAttackingState()
{
	
	curstate = SIMON->State->StateName;
	if (curstate == STATE_JUMP)
	{
		SIMON->height = SIMON_HEIGHT;
	}
	
	SIMON->attacking = true;
	if (SIMON->sitting)
	{
		StateName = STATE_SIT_ATTACKING;
	}
	else
	{
		StateName = STATE_ATTACK;
	}
}

void SimonAttackingState::Update(DWORD dt)
{
	this->HandleKeyboard();
	if (SIMON->curAni->CheckEndAni())
	{
		SIMON->attacking = false;
		SIMON->curAni->SetEndAniFalse();
		switch (curstate)
		{
		case STATE_SITTING:
			SIMON->height = SIMON_SITTING_HEIGHT;
			SIMON->y -= 16 / 2;
			SIMON->ChangeState(new SimonSittingState());
			break;
		case STATE_STANDING:case STATE_WALKING:
			SIMON->ChangeState(new SimonStandingState());
			break;
		case STATE_FALL:case STATE_JUMP:
			if (SIMON->vy>0)
			{
				SIMON->ChangeState(new SimonFallingState());
			}
			else if(SIMON->vy==0)
			{
				SIMON->ChangeState(new SimonStandingState());
			}
			
			break;
		}
	}
	else
	{
		switch (curstate)
		{
		case STATE_WALKING:
			SIMON->vx = 0;
			break;
		case STATE_FALL:
			SIMON->vx = 0;
			break;
		}

	}
}

void SimonAttackingState::HandleKeyboard()
{
}


