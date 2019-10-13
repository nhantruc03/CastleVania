#include "Simon.h"
#include"WeaponFactory.h"
#include"FirePillar.h"
#include"Brick.h"
#include"ItemsManager.h"
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
	throwing = false;
}
void CSimon::Respawn()
{
	this->jumping = false;
	this->attacking = false;
	this->isReverse = true;
	this->ChangeState(new SimonStandingState());
}
void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects )
{
	CGameObject::Update(dt);
	State->Update(dt);
	// simple fall down
	vy += SIMON_GRAVITY*dt;
	if (vx < 0 && x < 16) x = 16;
	if (vx > 0 && x > 1536)x = 1536;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	CalcPotentialCollisions(coObjects, coEvents);


	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
	
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CBrick*>(e->obj))
			{
				x += min_tx * dx + nx * 0.1f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
				y += min_ty * dy + ny * 0.1f;

				if (nx != 0) vx = 0;
				if (ny != 0) vy = 0;
			}
			if (dynamic_cast<Item *>(e->obj)) // if e->obj is Goomba 
			{
				e->obj->isDead = true;
				if (dynamic_cast<BigHeart*>(e->obj))
				{
				}
				if (dynamic_cast<Dagger_Item*>(e->obj))
				{
				}
				if (dynamic_cast<Whip*>(e->obj))
				{
					morningstarlevel += 1;
					if (morningstarlevel > 3)
					{
						morningstarlevel = 3;
					}
				}
			}
		}
	}
	vector<CGameObject*>::iterator it = Weapons.begin();
	while (it != Weapons.end())
	{
		CGameObject* o = *it;
		switch (o->tag)
		{
		case TAG_WEAPON:
		{
			Weapon* w = WeaponFactory::ConvertToWeapon(o);
			if (w->isDead)//state != SIMON_STATE_ATTACK && state != SIMON_STATE_SIT_ATTACKING)
			{
				it=Weapons.erase(it);
				delete w;
				continue;
			}
			w->Update(dt,coObjects);
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
			if (!keyCode[DIK_UP])
			{
				Weapon* weapon = WeaponFactory::CreateWeapon(ID_WEAPON_MORNINGSTAR);
				if (UsingMorningStar == false)
				{
					weapon->isReverse = isReverse;
					Weapons.push_back(weapon);
					UsingMorningStar = true;
				}
				ChangeState(new SimonAttackingState());

			}
			else
			{
				if (State->StateName != SIMON_STATE_SITTING && throwing == false)
				{
					Weapon* weapon = WeaponFactory::CreateWeapon(ID_WEAPON_DAGGER);
					weapon->isReverse = isReverse;
					Weapons.push_back(weapon);
					throwing = true;
					ChangeState(new SimonAttackingState());
				}
			}
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
	curAni = animations[State->StateName];
}

CSimon * CSimon::GetInstance()
{
	if (_instance == NULL)
		_instance = new CSimon();
	return _instance;
}

void CSimon::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x - width / 2;
	right = left + width;
	top = y - height / 2;
	bottom = top + height;

}
