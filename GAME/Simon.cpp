#include "Simon.h"

CSimon*CSimon::_instance = NULL;
CSimon::CSimon()
{
	CAnimations *animations = CAnimations::GetInstance();
	LPANIMATION ani;
	// idle
	ani = new CAnimation(100);
	ani->Add(TAG_SIMON, 0);
	animations->Add(1, ani);
	// walk
	ani = new CAnimation(100);
	ani->Add(TAG_SIMON, 0);
	ani->Add(TAG_SIMON, 1);
	ani->Add(TAG_SIMON, 2);
	ani->Add(TAG_SIMON, 3);
	animations->Add(2, ani);
	// jump
	ani = new CAnimation(100);
	ani->Add(TAG_SIMON, 4);
	animations->Add(3, ani);
	// fall
	ani = new CAnimation(100);
	ani->Add(TAG_SIMON, 0);
	animations->Add(4, ani);
	// attack
	ani = new CAnimation(100);
	ani->Add(TAG_SIMON, 0);
	ani->Add(TAG_SIMON, 5);
	ani->Add(TAG_SIMON, 6);
	ani->Add(TAG_SIMON, 7);
	animations->Add(5, ani);
	// sit
	ani = new CAnimation(100);
	ani->Add(TAG_SIMON, 4);
	animations->Add(6, ani);
	// attack sit
	ani = new CAnimation(100);
	ani->Add(TAG_SIMON, 4);
	ani->Add(TAG_SIMON, 8);
	ani->Add(TAG_SIMON, 9);
	ani->Add(TAG_SIMON, 10);
	animations->Add(7, ani);
	AddAnimation(1); // idle
	AddAnimation(2); // walk
	AddAnimation(3); // jumo
	AddAnimation(4); // fall
	AddAnimation(5); // attacking
	AddAnimation(6); //sit
	AddAnimation(7); // sit attack
	morningstarlevel = 1;
	width = SIMON_WIDTH;
	height = SIMON_HEIGHT;
	UsingMorningStar = false;
	// this->ChangeState(new SimonStandingState()); 
}
void CSimon::Respawn()
{
	this->jumping = false;
	this->attacking = false;
	this->isReverse = true;
	this->ChangeState(new SimonStandingState());
}
void CSimon::Update(DWORD dt)
{
	CGameObject::Update(dt);
	State->Update(dt);
	// simple fall down
	vy += SIMON_GRAVITY;

	if (y + height / 2 > 292)
	{
		vy = 0; y = 292- height / 2;
	}
	if (vx < 0 && x < 0) x = 0;
}

void CSimon::Render()
{
	curAni->isreverse = this->isReverse;
	curAni->Render(x, y);

}

void CSimon::SetState(int state)
{
}

void CSimon::OnKeyDown(int key)
{
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
	case DIK_M:
		morningstarlevel += 1;
		if (morningstarlevel > 3)
		{
			morningstarlevel = 1;
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
	if (_instance == NULL)
		_instance = new CSimon();
	return _instance;
}
