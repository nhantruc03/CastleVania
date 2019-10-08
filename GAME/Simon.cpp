#include "Simon.h"
#include"WeaponFactory.h"
CSimon*CSimon::_instance = NULL;
CSimon::CSimon()
{
	tag = TAG_SIMON;
	AddAnimation(tag, 0); // idle
	AddAnimation(tag, 1); // walk
	AddAnimation(tag, 2); // jumo
	AddAnimation(tag, 3); // fall
	AddAnimation(tag, 4); // attacking
	AddAnimation(tag, 5); //sit
	AddAnimation(tag, 6); // sit attack
	morningstarlevel = 1;
	width = SIMON_WIDTH;
	height = SIMON_HEIGHT;
	UsingMorningStar = false;
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
	vy += SIMON_GRAVITY*dt;

	if (y + height / 2 > 292)
	{
		vy = 0; y = 292- height / 2;
	}
	if (vx < 0 && x < 0) x = 0;

	auto it = Weapons.begin();
	while (it != Weapons.end())
	{
		auto o = *it;
		switch (o->tag)
		{
		case TAG_WEAPON:
		{
			auto w = WeaponFactory::ConvertToWeapon(o);

			if (state != SIMON_STATE_ATTACK && state != SIMON_STATE_SIT_ATTACKING)
			{
				it = Weapons.erase(it);
				delete w;
				continue;
			}

			w->Update(dt);
			break;
		}
		}
		++it;

	}
}

void CSimon::Render()
{
	
	curAni->isreverse = this->isReverse;
	curAni->Render(x, y);
	for (auto o : Weapons)
	{
		o->Render();
	}
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
			Weapon* weapon = WeaponFactory::CreateWeapon(ID_WEAPON_MORNINGSTAR);
			if (UsingMorningStar == false)
			{
				weapon->isReverse = isReverse;
				Weapons.insert(weapon);
				UsingMorningStar = true;
			}
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
