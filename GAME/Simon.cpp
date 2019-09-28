#include "Simon.h"

CSimon*CSimon::_instance = NULL;
CSimon::CSimon()
{
	 width = SIMON_WIDTH; 
	 height = SIMON_HEIGHT; 
	// this->ChangeState(new SimonStandingState()); 
}
void CSimon::Respawn()
{
	this->jumping=false;
	this->attacking=false;
	this->isReverse = true;
	this->ChangeState(new SimonStandingState());
}
void CSimon::Update(DWORD dt)
{
	CGameObject::Update(dt);
	State->Update(dt);
	// simple fall down
	vy += SIMON_GRAVITY;
	
	if (y + height / 2 > 150)
	{
		vy = 0; y = 150 - height / 2;
		//if (jumping)
		//{
		//	jumping = false;
		//	ChangeState(new SimonStandingState());
		//}
	}
	/*else
	{
		ChangeState(new SimonFallingState());
	}*/

	// simple screen edge collision!!!
	if (vx > 0 && x > 290) x = 290;
	if (vx < 0 && x < 0) x = 0;
	/*if (keyCode[DIK_RIGHT])
	{
		SetState(SIMON_STATE_WALKING);
		isReverse = true;
	}
	else if (keyCode[DIK_LEFT])
	{
		SetState(SIMON_STATE_WALKING);
		isReverse = false;
	}
	else
	{	
		
			SetState(SIMON_STATE_IDLE);
		
	}*/
}

void CSimon::Render()
{
	//int ani;
	/*if (vx == 0)
	{
		if (jumping)
		{
			if (attacking)
			{
				ani = SIMON_ANI_ATTACKING;
			}
			else
			{
				ani = SIMON_ANI_JUMPING;
			}
		}
		else
		{
			if (attacking)
			{
				ani = SIMON_ANI_ATTACKING;
			}
			else
			{
				if (sitting)
				{
					ani = SIMON_ANI_SITTING;
				}
				else
				{
					ani = SIMON_ANI_IDLE;
				}
			}
		}
	}
	else if (vx != 0)
	{

		if (jumping)
			if (attacking)
			{
				ani = SIMON_ANI_ATTACKING;
			}
			else
			{
				ani = SIMON_ANI_JUMPING;
			}
		else
		{
			if (attacking)
			{
				vx = 0;
				ani = SIMON_ANI_ATTACKING;
			}
			else
			{
				if (sitting)
				{
					ani = SIMON_ANI_SITTING;
				}
				else ani = SIMON_ANI_WALKING;
			}
		}
	}

	if (attacking)
	{
		if (animations[ani]->CheckEndAni())
		{
			attacking = false;
			animations[ani]->SetEndAniFalse();
		}
	}
	animations[ani]->isreverse = this->isReverse;
	animations[ani]->Render(x, y);*/
	curAni->isreverse = this->isReverse;
	curAni->Render(x, y);

}

void CSimon::SetState(int state)
{
	/*CGameObject::SetState(state);
	switch (state)
	{
	case SIMON_STATE_WALKING:
		if (jumping || attacking) {}
		else if (sitting)
		{
			if (isReverse==true)
			{
				nx = 1;
			}
			else
				nx = -1;
		}
		else
		{
			if (isReverse==true)
			{
				vx = SIMON_WALKING_SPEED;
				nx = 1;
			}
			else
			{
				vx = -SIMON_WALKING_SPEED;
				nx = -1;
			}
		}
		break;
	case SIMON_STATE_JUMP:
		if (attacking || sitting) {}
		else
		{
			if (y == 150-height/2)
			{
				vy = -SIMON_JUMP_SPEED_Y;
				jumping = true;
			}
		}
		break;
	case SIMON_STATE_IDLE:
		if (jumping || attacking) {}
		else
		{
			vx = 0;
		}
		break;
	case SIMON_STATE_ATTACK:
		attacking = true;
		break;
	case SIMON_STATE_SITTING:
		if (jumping || attacking) {}
		else
		{
			if (!sitting)
			{
				sitting = true;
				height -= 17;
				y += 17 / 2;
				vx = 0;
			}
		}
		
		break;
	}*/
}

void CSimon::OnKeyDown(int key)
{
	//switch (key)
	//{
	//case DIK_SPACE:
	//	SetState(SIMON_STATE_JUMP);
	//	break;
	//case DIK_A:
	//	SetState(SIMON_STATE_ATTACK);
	//	break;
	//case DIK_DOWN:
	//	SetState(SIMON_STATE_SITTING);
	//	break;
	//}
	switch (key)
	{
	case DIK_SPACE:
		if (!jumping && !sitting && !attacking)
		{
			ChangeState(new SimonJumpingState());
		}
		break;
	case DIK_DOWN:
		if (!jumping && !attacking)
		{
			ChangeState(new SimonSittingState());
		}
		break;
	case DIK_A:
		if (!attacking)
		{
			ChangeState(new SimonAttackingState());
		}
		break;
	}

	


}

void CSimon::OnKeyUp(int key)
{
	/*if (key == DIK_DOWN)
	{
		if (sitting)
		{
			height += 17;
			y -= 17 / 2;
			sitting = false;
		}
	}*/
}

int CSimon::iskeydown(int keyCode)
{
	BYTE  keyStates[256];
	return (keyStates[keyCode] & 0x80) > 0;
}

void CSimon::ChangeState(SimonState * newState)
{
	delete State;
	State = newState;
	state = newState->StateName;
	curAni = animations[state];
}

CSimon * CSimon::GetInstance()
{
	if(_instance == NULL)
		_instance = new CSimon();
	return _instance;
}
