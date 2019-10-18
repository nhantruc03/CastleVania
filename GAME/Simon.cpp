#include "Simon.h"
#include"WeaponsManager.h"
#include"Brick.h"
#include"Item.h"
CSimon*CSimon::_instance = NULL;
CSimon::CSimon()
{
	tag = TAG_SIMON;
	AddAnimation(tag, 0); // stand
	AddAnimation(tag, 1); // walk
	AddAnimation(tag, 2); // jumo
	AddAnimation(tag, 3); // fall
	AddAnimation(tag, 4); // attacking
	AddAnimation(tag, 5); // sit
	AddAnimation(tag, 6); // sit attack
	morningstarlevel = 1;
	width = SIMON_WIDTH;
	height = SIMON_HEIGHT;
	
}
void CSimon::Respawn()
{
	throwing = false;
	secondweapon = NULL;
	heart = 5;
	jumping = false;
	attacking = false;
	isReverse = true;
	ChangeState(new SimonStandingState());
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
		x += min_tx * dx + nx * 0.2f;		// nx*0.2f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.2f;		
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CBrick*>(e->obj))
			{
				if (nx < 0) vx = 0;
				if (ny < 0) vy = 0;

			}
			if (dynamic_cast<Item *>(e->obj))
			{

				e->obj->isDead = true;
				switch (e->obj->type)
				{
				case TYPE_ITEM_BIG_HEART:
					heart += 5;
					break;
				case TYPE_ITEM_WHIP:
					morningstarlevel += 1;
					if (morningstarlevel > 3)
					{
						morningstarlevel = 3;
					}
					break;
				case TYPE_ITEM_DAGGER:
					secondweapon = TYPE_WEAPON_DAGGER;
					break;

				default:
					break;
				}
			}
			
		}
	}
	// xu ly va nhan vat va cham voi item khi item vua duoc sinh ra
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		float l, t, r, b;
		coObjects->at(i)->GetBoundingBox(l, t, r, b);
		if (this->IsContain(l, t, r, b) == true)
		{
			switch (coObjects->at(i)->tag)
			{
			case TAG_ITEM:
				switch (coObjects->at(i)->type)
				{
				case TYPE_ITEM_BIG_HEART:
					heart += 5;
					break;
				case TYPE_ITEM_DAGGER:
					secondweapon = TYPE_WEAPON_DAGGER;
					break;
				case TYPE_ITEM_WHIP:
					morningstarlevel += 1;
					if (morningstarlevel > 3)
					{
						morningstarlevel = 3;
					}
				}
				coObjects->at(i)->isDead = true;
				break;
			}
		}
	}
	vector<Weapon*>::iterator it = Weapons.begin(); // iterator: con tro chi den 1 phan tu ben trong container, khong can biet thu tu phan tu ben trong mang
	while (it != Weapons.end())
	{
		Weapon* o = *it;
		switch (o->tag)
		{
		case TAG_WEAPON:
		{
			Weapon* w = WeaponsManager::ConvertToWeapon(o);
			if (w->isDead)
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
	for (Weapon* o : Weapons)
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
		if (!jumping && !attacking && !sitting)
		{
			ChangeState(new SimonSittingState());
		}
		break;
	case DIK_A:
		if (!attacking)
		{
			if (!keyCode[DIK_UP])
			{
				Weapon* weapon = WeaponsManager::CreateWeapon(TYPE_WEAPON_MORNINGSTAR);
				weapon->isReverse = isReverse;
				Weapons.push_back(weapon);
				ChangeState(new SimonAttackingState());

			}
			else
			{
				if (State->StateName != STATE_SITTING && throwing == false && secondweapon!=NULL && heart>=1)
				{
					heart -= 1;
					Weapon* weapon = WeaponsManager::CreateWeapon(secondweapon);
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