#include "Simon.h"
#include"WeaponsManager.h"
#include"Brick.h"
CSimon*CSimon::_instance = NULL;
CSimon::CSimon()
{
	upgrade_time = 0;
	tag = TAG_SIMON;
	AddAnimation(tag, 0); // stand
	AddAnimation(tag, 1); // walk
	AddAnimation(tag, 2); // jumo
	AddAnimation(tag, 3); // fall
	AddAnimation(tag, 4); // attacking
	AddAnimation(tag, 5); // sit
	AddAnimation(tag, 6); // sit attack
	AddAnimation(tag, 7);// stand on stair
	AddAnimation(tag, 8); // walk up stair
	morningstarlevel = 1;
	width = SIMON_WIDTH;
	height = SIMON_HEIGHT;
	srand(time(NULL));
	check_auto_move = false;
	isWalkingOnStair = false;
}
void CSimon::Respawn()
{
	check_auto_move = false;
	throwing = false;
	secondweapon = NULL;
	heart = 5;
	jumping = false;
	attacking = false;
	isReverse = true;
	ChangeState(STATE_STANDING);
}
void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	isCollidewith_DWNLTR = false;
	isCollidewith_DWNRTL = false;
	isCollidewith_UPLTR = false;
	isCollidewith_UPRTL = false;
	CGameObject::Update(dt);

	Update_State();
	curAni->Update();
	// simple fall down
	if (!isOnStair)
	{
		vy += SIMON_GRAVITY * dt;
	}
	if (vx < 0 && x < 16) x = 16;
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
		//y += min_ty * dy + ny * 0.2f;
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CBrick*>(e->obj))
			{
				if (isOnStair)
				{
					x += dx;
				}
				if (ny == -1)
				{
					y += min_ty * dy + ny * 0.4f;
				}
				else
				{
					y += dy;
				}
				if (ny == -1)
				{
					vy = 0;
				}

				//if (ny > 0) y -= min_ty * dy + ny * 0.2f;;

			}
			/*if (dynamic_cast<Item *>(e->obj))
			{

				e->obj->isDead = true;
				if (dynamic_cast<BigHeart_Item*>(e->obj))
				{
					heart += 5;
				}
				if (dynamic_cast<Dagger_Item*>(e->obj))
				{
					secondweapon = TYPE_WEAPON_DAGGER;
				}
				if (dynamic_cast<Whip_Item*>(e->obj))
				{
					morningstarlevel += 1;
					if (morningstarlevel > 3)
					{
						morningstarlevel = 3;
					}
				}
			}*/

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
					upgrade_time = 1000;
					morningstarlevel += 1;
					if (morningstarlevel > 3)
					{
						morningstarlevel = 3;
					}
				}
				coObjects->at(i)->isDead = true;
				break;
			case 999:
				switch (coObjects->at(i)->type)
				{
				case 1:
					isCollidewith_UPLTR = true;
					
					break;
				case -1:
					isCollidewith_UPRTL = true;
					break;
				case 2:
					isCollidewith_DWNRTL = true;
					break;
				case -2:
					isCollidewith_DWNLTR = true;
					break;
				}
				stair_collide = coObjects->at(i)->GetBoundingBox();
				break;
			}
		}
	}
	onstair_handle(dt);
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
				it = Weapons.erase(it);
				delete w;
				continue;
			}
			w->Update(dt, coObjects);
			break;
		}
		}
		++it;
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

}

void CSimon::onstair_handle(DWORD dt)
{
	if (isCollidewith_UPLTR && keyCode[DIK_UP]&& !isOnStair)
	{
		check_auto_move = true;
		if (x > stair_collide.left + (stair_collide.right - stair_collide.left) / 2)
		{
			gotoleft = true;
		}
		else if (x < stair_collide.left+(stair_collide.right-stair_collide.left)/2)
		{
			gotoright = true;
		}
	}

	if (gotoright)
	{
		ChangeState(STATE_WALKING);
		isReverse = true;
		vx = SIMON_WALKING_SPEED;
		if (x >= stair_collide.left + (stair_collide.right - stair_collide.left) / 2)
		{
			if (!isOnStair)
			{
				x = stair_collide.left + (stair_collide.right - stair_collide.left) / 2;
				gotoright = false;
				gotoleft = false;
				goup = true;
			}
		}

	}
	if (gotoleft)
	{
		ChangeState(STATE_WALKING);
		isReverse = false;
		vx = -SIMON_WALKING_SPEED;
		if (x <= stair_collide.left + (stair_collide.right - stair_collide.left) / 2)
		{
			if (!isOnStair) {
				x = stair_collide.left + (stair_collide.right - stair_collide.left) / 2;
				gotoright = false;
				gotoleft = false;
				goup = true;
			}
		}
	}
	if(goup&&!gotoleft&&!gotoright&&!isOnStair)
	{
		//isOnStair = true;
		prevY = y;
		isReverse = true;
		check_auto_move = false;
		keyCode.clear();
		goup = false;
		ChangeState(STATE_WALK_ONSTAIR_UP);
	}

	if (State == STATE_WALK_ONSTAIR_UP && isCollidewith_DWNRTL)
	{
		ChangeState(STATE_STANDING);
	}
}
void CSimon::Render()
{
	curAni->isreverse = this->isReverse;
	if (upgrade_time)
	{
		int r = rand() % 255;
		int g = rand() % 255;
		int b = rand() % 255;
		curAni->Render(x, y, 255, r, g, b);
	}
	else
	{
		curAni->Render(x, y);
	}
	for (Weapon* o : Weapons)
	{
		o->Render();
	}
}

void CSimon::OnKeyDown(int key)
{
	if (!upgrade_time)
	{
		switch (key)
		{
		case DIK_SPACE:
			if (!jumping && !sitting && !attacking&&!isOnStair)
			{
				ChangeState(STATE_JUMP);
			}
			break;
		case DIK_DOWN:
			if (!jumping && !attacking && !sitting&&!isOnStair)
			{
				ChangeState(STATE_SITTING);
			}
			break;
		case DIK_A:
			if (!attacking)
			{
				if (!keyCode[DIK_UP] &&State!=STATE_WALK_ONSTAIR_UP&&State!=STATE_WALK_ONSTIAR_DOWN)
				{
					Weapon* weapon = WeaponsManager::CreateWeapon(TYPE_WEAPON_MORNINGSTAR);
					weapon->isReverse = isReverse;
					Weapons.push_back(weapon);
					ChangeState(STATE_ATTACK);

				}
				else
				{
					if (State != STATE_SITTING && throwing == false && secondweapon != NULL && heart >= 1)
					{
						heart -= 1;
						Weapon* weapon = WeaponsManager::CreateWeapon(secondweapon);
						weapon->isReverse = isReverse;
						Weapons.push_back(weapon);
						throwing = true;
						ChangeState(STATE_ATTACK);
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
}

void CSimon::OnKeyUp(int key)
{
	if (State == STATE_WALKING)
	{
		if (key == DIK_LEFT || key == DIK_RIGHT)
		{
			ChangeState(STATE_STANDING);
		}
	}


}

void CSimon::ChangeState(int newState)
{
	prevState = State;
	State = newState;
	switch (State)
	{
	case STATE_STANDING:
		height = SIMON_HEIGHT;
		vx = 0;
		vy = 0;
		jumping = false;
		sitting = false;
		attacking = false;
		isOnStair = false;
		isWalkingOnStair = false;
		break;
	case STATE_WALKING:
		attacking = false;
		sitting = false;
		jumping = false;
		vy = 0;
		height = SIMON_HEIGHT;
		break;
	case STATE_SITTING:
		sitting = true;
		vx = 0;
		vy = 0;
		y += 16 / 2;
		height = SIMON_SITTING_HEIGHT;
		break;
	case STATE_JUMP:
		height = SIMON_SITTING_HEIGHT;
		vy = -SIMON_JUMP_SPEED_Y;
		jumping = true;
		STATE_JUMP;
		break;
	case STATE_FALL:
		height = SIMON_HEIGHT;
		break;
	case STATE_ATTACK:
		if (prevState == STATE_JUMP)
		{
			height = SIMON_HEIGHT;
		}
		attacking = true;
		if (sitting)
		{
			State = STATE_SIT_ATTACKING;
		}
		else
		{
			State = STATE_ATTACK;
		}
		break;
	case STATE_STAND_ONSTAIR_UP:
		isWalkingOnStair = false;
		isOnStair = true;
		height = SIMON_HEIGHT;
		vx = 0;
		vy = 0;
		jumping = false;
		sitting = false;
		attacking = false;
		break;
	case STATE_WALK_ONSTAIR_UP:
		isWalkingOnStair = true;
		isOnStair = true;
		attacking = false;
		sitting = false;
		jumping = false;
		height = SIMON_HEIGHT;
		break;
	}
	curAni = animations[State];
}

CSimon * CSimon::GetInstance()
{
	if (_instance == NULL)
		_instance = new CSimon();
	return _instance;
}

void CSimon::Update_State()
{
	switch (State)
	{
	case STATE_STANDING:

		// Nhấn phím di chuyển -> WALKING
		if (keyCode[DIK_LEFT] || keyCode[DIK_RIGHT])
		{
			ChangeState(STATE_WALKING);
		}
		// Nhấn phím DOWN -> SITTING
		else if (keyCode[DIK_DOWN])
		{
			ChangeState(STATE_SITTING);
		}

		break;
	case STATE_WALKING:

		if (keyCode[DIK_RIGHT])
		{
			isReverse = true;
			vx = SIMON_WALKING_SPEED;
		}
		else if (keyCode[DIK_LEFT])
		{
			isReverse = false;
			vx = -SIMON_WALKING_SPEED;
		}
		break;
	case STATE_SITTING:

		if (!keyCode[DIK_DOWN])
		{
			sitting = false;
			height = SIMON_HEIGHT;
			y -= 16 / 2;

			if (keyCode[DIK_LEFT] || keyCode[DIK_RIGHT])
			{
				ChangeState(STATE_WALKING);
			}
			else
			{
				ChangeState(STATE_STANDING);
			}
		}
		else if (keyCode[DIK_RIGHT])
		{
			isReverse = true;
		}
		else if (keyCode[DIK_LEFT])
		{
			isReverse = false;
		}
		break;
	case STATE_JUMP:

		if (vy > 0)
		{
			ChangeState(STATE_FALL);
		}
		break;
	case STATE_FALL:
		if (vy == 0)
		{
			ChangeState(STATE_STANDING);
		}
		break;
	case STATE_ATTACK:case STATE_SIT_ATTACKING:

		if (curAni->CheckEndAni())
		{
			attacking = false;
			curAni->SetEndAniFalse();
			switch (prevState)
			{
			case STATE_SITTING:
				height = SIMON_SITTING_HEIGHT;
				y -= 16 / 2;
				ChangeState(STATE_SITTING);
				break;
			case STATE_STANDING:case STATE_WALKING:
				ChangeState(STATE_STANDING);
				break;
			case STATE_WALK_ONSTAIR_UP:case STATE_STAND_ONSTAIR_UP:
				ChangeState(STATE_STAND_ONSTAIR_UP);
				break;
			case STATE_FALL:case STATE_JUMP:
				if (vy > 0)
				{
					ChangeState(STATE_FALL);
				}
				else if (vy == 0)
				{
					ChangeState(STATE_STANDING);
				}

				break;
			}
		}
		else
		{
			switch (prevState)
			{
			case STATE_WALKING:
				vx = 0;
				break;
			}
			if (vy == 0)
			{
				vx = 0;
			}

		}
		break;
	case STATE_STAND_ONSTAIR_UP:
		isWalkingOnStair = false;
		if (keyCode[DIK_UP])
		{
			ChangeState(STATE_WALK_ONSTAIR_UP);
		}
		break;
	case STATE_WALK_ONSTAIR_UP:
		isOnStair = true;
		isWalkingOnStair = true;
		isReverse = true;
		vx = SIMON_WALKING_SPEED / 2;
		vy = -SIMON_WALKING_SPEED / 2;
		if (prevY - y >= 16)
		{
			if (prevY - y > 16)
			{
				y += prevY - y - 16;
				prevY = y;
				isWalkingOnStair = false;
			}
			
		}
		if (!keyCode[DIK_UP] && !isWalkingOnStair)
		{
			ChangeState(STATE_STAND_ONSTAIR_UP);
		}
		break;
	}

}
