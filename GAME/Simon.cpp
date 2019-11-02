﻿#include "Simon.h"
#include"WeaponsManager.h"
#include"Brick.h"
#include"HoldItemObject.h"
#include"Item.h"
#include"Enemy.h"
#include"Door.h"
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
	AddAnimation(tag, 7); // stand on stair_up
	AddAnimation(tag, 8); // walk up stair_up
	AddAnimation(tag, 9); // stand on stair_down
	AddAnimation(tag, 10);// walk on stair_down
	AddAnimation(tag, 11); // injured
	AddAnimation(tag, 12); // attack on stair down
	AddAnimation(tag, 13);	// attack on stair up
	morningstarlevel = 1;
	width = SIMON_WIDTH;
	height = SIMON_HEIGHT;


	srand(time(NULL));

	ishit = false;
	untouchable = 0;
	upgrade_time = 0;
	isinjured = false;

	falling = false;
	
	sitting = false;
	secondweapon = NULL;
	throwing = false;
	jumping = false;
	heart = 5;
	attacking = false;

	
	isWalkingOnStair = false;
	isOnStair = false;
	goup = gotoleft = gotoright = godown = false;


	check_auto_move = false;
}
void CSimon::Respawn()
{
	isWalkingOnStair = false;
	isOnStair = false;
	check_auto_move = false;
	sitting = false;
	throwing = false;
	jumping = false;
	attacking = false;
	isReverse = true;
	goup = gotoleft = gotoright = godown = false;
	ChangeState(STATE_STANDING);
}
void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (timeusingstopwatch)
	{
		timeusingstopwatch -= dt;
	}
	isCollidewith_DWNLTR = false;
	isCollidewith_DWNRTL = false;
	isCollidewith_UPLTR = false;
	isCollidewith_UPRTL = false;



	curAni->Update();

	// simple fall down
	if (!isOnStair)
	{
		vy += SIMON_GRAVITY * dt;
	}
	CGameObject::Update(dt);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	CalcPotentialCollisions(coObjects, coEvents);
	if (GetTickCount() - untouchable_start > 2000)
	{
		untouchable_start = 0;
		untouchable = 0;
	}
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
			
				if (isOnStair)
				{
					x += dx;
					y += dy;
				}
				if (ny == 1)
				{
					y += dy;
					vx = 0;
				}
				if (ny == -1)
				{
					vy = 0;
				}
			}
			if (dynamic_cast<Door*>(e->obj))
			{
				if (nx < 0)
				{
					x += dx;
				}
			}
			if (dynamic_cast<Item *>(e->obj))
			{
				if (!dynamic_cast<Item *>(e->obj)->rewarded)
				{
					if (ny > 0)
					{
						y -= min_ty * dy + ny * 0.2f;
					}
					if (e->obj->type == TYPE_ITEM_BIG_HEART)
					{
						heart += 5;
					}
					if (e->obj->type == TYPE_ITEM_HEART)
					{
						heart += 1;
					}
					if (e->obj->type == TYPE_ITEM_DAGGER)
					{
						secondweapon = TYPE_WEAPON_DAGGER;
					}
					if (e->obj->type == TYPE_ITEM_HOLY_WATER)
					{
						secondweapon = TYPE_WEAPON_HOLY_WATER;
					}
					if (e->obj->type == TYPE_ITEM_STOP_WATCH)
					{
						secondweapon = TYPE_WEAPON_STOP_WATCH;
					}
					if (e->obj->type == TYPE_ITEM_WHIP)
					{
						upgrade_time = 1000;
						morningstarlevel += 1;
						if (morningstarlevel > 3)
						{
							morningstarlevel = 3;
						}
					}
					dynamic_cast<Item*>(e->obj)->GetReward();
				}
			
			}
			if (dynamic_cast<Enemy*> (e->obj))
			{
				if (untouchable == 0)
				{
					StartUntouchable();
					if (dynamic_cast<Enemy*> (e->obj)->type == TYPE_ENEMY_BULLET)
					{
						dynamic_cast<Enemy*> (e->obj)->isDead = true;
					}
					if (!isOnStair) // khi tren cau thang va bi thuong thi khong bi vang di
					{
						if (nx <= 0)
						{
							isReverse = false;
						}
						else
						{
							isReverse = true;
						}
						ishit = true;
					}
				}
				else
				{
					if (e->ny < 0)
					{
						y += dy;
					}
				}
			}
		}
	}

	// cho roi nhanh hon khi roi tu cau thang xuong
	if (vy > 0 &&!jumping && !isinjured && !isOnStair )
	{
		falling = true;
	}
	if (falling)
	{
		if (vx > 0)
		{
			x += 0.2f; // tranh overlapping
		}
		else
			x -= 0.2f;
		vx = 0;
		vy = vy * 2;
		falling = false;
		ChangeState(STATE_FALL);
	}
	// kiem tra va cham voi quai vat va chuyen state injured
	if (ishit)
	{
		ChangeState(STATE_INJURED);
		ishit = false;
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
				if (!dynamic_cast<Item *>(coObjects->at(i))->rewarded)
				{
					switch (coObjects->at(i)->type)
					{
					case TYPE_ITEM_BIG_HEART:
						heart += 5;
						break;
					case TYPE_ITEM_HEART:
						heart += 1;
						break;
					case TYPE_ITEM_DAGGER:
						secondweapon = TYPE_WEAPON_DAGGER;
						break;
					case TYPE_ITEM_HOLY_WATER:
						secondweapon = TYPE_WEAPON_HOLY_WATER;
						break;
					case TYPE_ITEM_STOP_WATCH:
						secondweapon = TYPE_WEAPON_STOP_WATCH;
						break;
					case TYPE_ITEM_WHIP:
						upgrade_time = 1000;
						morningstarlevel += 1;
						if (morningstarlevel > 3)
						{
							morningstarlevel = 3;
						}
						break;
					}
					dynamic_cast<Item*>(coObjects->at(i))->GetReward();
				}
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
			case TAG_ENEMY:
					if (untouchable == 0 && coObjects->at(i)->isBurn==false)
					{
						StartUntouchable();
						if (coObjects->at(i)->type == TYPE_ENEMY_BULLET)
						{
							coObjects->at(i)->isDead = true;
						}
						if (!isOnStair)
						{
							isReverse = false;
							ChangeState(STATE_INJURED);
						}
					}
				break;
			}
		}
	}
	Update_State(); // de sau doan kiem tra tren de kiem tra va cham voi diem len xuong cau thang

	inoutstair_handle(dt);
	vector<Weapon*>::iterator it = Weapons.begin(); // iterator: con tro chi den 1 phan tu ben trong container, khong can biet thu tu phan tu ben trong mang
	while (it != Weapons.end())
	{
		Weapon* o = *it;
		switch (o->tag)
		{
		case TAG_WEAPON:
		{
			Weapon* w = (Weapon*) o;
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
void CSimon::inoutstair_handle(DWORD dt)
{
	if ((((isCollidewith_UPLTR||isCollidewith_UPRTL) && keyCode[DIK_UP]&& !isOnStair) || ((isCollidewith_DWNRTL||isCollidewith_DWNLTR) && keyCode[DIK_DOWN] && !isOnStair)) && (State==STATE_STANDING||State==STATE_WALKING))
	{
		if (isCollidewith_UPLTR || isCollidewith_DWNRTL)
		{
			stair_type = 1;
		}
		else
		{
			stair_type = 2;
		}
		check_auto_move = true;
		if (x >= stair_collide.left + (stair_collide.right - stair_collide.left) / 2)
		{
			gotoleft = true;
		}
		else if (x <= stair_collide.left+(stair_collide.right-stair_collide.left)/2)
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
				if (isCollidewith_UPLTR||isCollidewith_UPRTL)
				{
					goup = true;
				}
				else if (isCollidewith_DWNRTL||isCollidewith_DWNLTR)
				{
					godown = true;
				}
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
				if (isCollidewith_UPLTR||isCollidewith_UPRTL)
				{
					goup = true;
				}
				else if (isCollidewith_DWNRTL||isCollidewith_DWNLTR)
				{
					godown = true;
				}
			}
		}
	}
	if(goup && !gotoleft && !gotoright && !isOnStair)
	{
		prevX = x;
		prevY = y;
		check_auto_move = false;
		keyCode.clear();
		goup = false;
		ChangeState(STATE_WALK_ONSTAIR_UP);
	}
	else if (godown && !gotoleft && !gotoright && !isOnStair)
	{
		prevX = x;
		prevY = y;
		check_auto_move = false;
		keyCode.clear();
		godown = false;
		ChangeState(STATE_WALK_ONSTAIR_DOWN);
	}

	if (State == STATE_WALK_ONSTAIR_UP && (isCollidewith_DWNRTL||isCollidewith_DWNLTR))
	{
		y = prevY - 16;
		ChangeState(STATE_STANDING);
	}
	else if (State == STATE_WALK_ONSTAIR_DOWN && (isCollidewith_UPLTR||isCollidewith_UPRTL))
	{
		ChangeState(STATE_STANDING);
	}
}
void CSimon::Render()
{
	curAni->isreverse = this->isReverse;
	int r = 255;
	int g = 255;
	int b = 255;
	int alpha = 255;
	if (upgrade_time)
	{
		r = rand() % 255;
		g = rand() % 255;
		b = rand() % 255;
	}
	else
	{
		if (untouchable) alpha = rand() % 255;
	}
	curAni->Render(x, y, alpha,r,g,b);
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
			if (!jumping && !sitting && !attacking&&!isOnStair && !isinjured)
			{
				ChangeState(STATE_JUMP);
			}
			break;
		case DIK_DOWN:
			if (!jumping && !attacking && !sitting&&!isOnStair && !isCollidewith_DWNRTL && !isCollidewith_DWNLTR && !isinjured)
			{
				ChangeState(STATE_SITTING);
			}
			break;
		case DIK_A:
			if (!attacking && !isinjured)
			{
				if (!keyCode[DIK_UP] &&State!=STATE_WALK_ONSTAIR_UP&&State!=STATE_WALK_ONSTAIR_DOWN)
				{
					Weapon* weapon = WeaponsManager::CreateWeapon(TYPE_WEAPON_MORNINGSTAR);
					weapon->isReverse = isReverse;
					Weapons.push_back(weapon);
					ChangeState(STATE_ATTACK);

				}
				else
				{
					if (keyCode[DIK_UP] && State != STATE_SITTING && throwing == false && secondweapon ==1 && heart >= 1)
					{
						heart -= 1;
						Weapon* weapon = WeaponsManager::CreateWeapon(secondweapon);
						weapon->isReverse = isReverse;
						Weapons.push_back(weapon);
						throwing = true;
						if (isWalkingOnStair)
						{
							vx = vy = 0;
						}
						ChangeState(STATE_ATTACK);
					}
					else if (keyCode[DIK_UP] && State != STATE_SITTING && throwing == false && secondweapon == 2 && heart >= 1)
					{
						heart -= 1;
						Weapon* weapon = WeaponsManager::CreateWeapon(secondweapon);
						weapon->isReverse = isReverse;
						Weapons.push_back(weapon);
						throwing = true;
						if (isWalkingOnStair)
						{
							vx = vy = 0;
						}
						ChangeState(STATE_ATTACK);
					}
					if (keyCode[DIK_UP] && secondweapon == 3 && heart >= 5 && !timeusingstopwatch)
					{
						heart -= 5;
						timeusingstopwatch = 5000;
					}
				}
			}
			break;
		case DIK_M:
			secondweapon = 2;
			heart += 5;
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
		jumping = false;
		sitting = false;
		isinjured = false;
		attacking = false;
		isOnStair = false;
		isWalkingOnStair = false;
		break;
	case STATE_WALKING:
		attacking = false;
		sitting = false;
		jumping = false;
		//vy = 0;
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
		else if (prevState == STATE_STAND_ONSTAIR_DOWN || prevState==STATE_WALK_ONSTAIR_DOWN)
		{
			State = STATE_ATTACK_ONSTAIR_DOWN;
		}
		else if (prevState == STATE_STAND_ONSTAIR_UP || prevState == STATE_WALK_ONSTAIR_UP)
		{
			State = STATE_ATTACK_ONSTAIR_UP;
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
	case STATE_STAND_ONSTAIR_DOWN:
		isWalkingOnStair = false;
		isOnStair = true;
		height = SIMON_HEIGHT;
		vx = 0;
		vy = 0;
		jumping = false;
		sitting = false;
		attacking = false;
		break;
	case STATE_WALK_ONSTAIR_DOWN:
		isWalkingOnStair = true;
		isOnStair = true;
		attacking = false;
		sitting = false;
		jumping = false;
		height = SIMON_HEIGHT;
		break;
	case STATE_INJURED:
		height = SIMON_HEIGHT;
		isinjured = true;
		if (isReverse)
		{
			vx = SIMON_WALKING_SPEED;
		}
		else
		{
			vx = -SIMON_WALKING_SPEED;
		}
		if (prevState == STATE_SITTING)
		{
			y -= 16 / 2;
		}
		vy = -(SIMON_JUMP_SPEED_Y/1.3f);
		attacking = false;
		sitting = false;
		jumping = false;
		if (prevState == STATE_ATTACK || prevState == STATE_SIT_ATTACKING)
		{
			if (animations[prevState]->CheckEndAni() == false)
			{
				animations[prevState]->currentFrame = -1;
			}
		}
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
		else if (keyCode[DIK_DOWN] && !isCollidewith_DWNLTR && !isCollidewith_DWNRTL)
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
		else
		{
			ChangeState(STATE_STANDING);
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
	case STATE_ATTACK:case STATE_SIT_ATTACKING:case STATE_ATTACK_ONSTAIR_DOWN:case STATE_ATTACK_ONSTAIR_UP:

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
			case STATE_STAND_ONSTAIR_UP:
				ChangeState(STATE_STAND_ONSTAIR_UP);
				break;
			case STATE_STAND_ONSTAIR_DOWN:
				ChangeState(STATE_STAND_ONSTAIR_DOWN);
				break;
			case STATE_WALK_ONSTAIR_DOWN:
				ChangeState(STATE_WALK_ONSTAIR_DOWN);
				break;
			case STATE_WALK_ONSTAIR_UP:
				ChangeState(STATE_WALK_ONSTAIR_UP);
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
		if (keyCode[DIK_UP] || keyCode[DIK_RIGHT])
		{
			ChangeState(STATE_WALK_ONSTAIR_UP);
		}
		if (keyCode[DIK_DOWN] || keyCode[DIK_LEFT] )
		{
			ChangeState(STATE_WALK_ONSTAIR_DOWN);
		}
		break;
	case STATE_WALK_ONSTAIR_UP:
		isOnStair = true;
		isWalkingOnStair = true;
		if (stair_type == 1)
		{
			isReverse = true;
			vx = SIMON_WALKING_SPEED / 2;
			vy = -SIMON_WALKING_SPEED / 2;
			if (prevY - y >= 16 && x - prevX >= 16)
			{
				if (x - prevX > 16)
				{
					x -= x - prevX - 16;
					prevX = x;
				}
				if (prevY - y > 16)
				{
					y += prevY - y - 16;
					prevY = y;
				}
				isWalkingOnStair = false;
			}
		}
		else if (stair_type == 2)
		{
			isReverse = false;
			vx = -SIMON_WALKING_SPEED / 2;
			vy = -SIMON_WALKING_SPEED / 2;
			if (prevY - y >= 16 &&  prevX -x >= 16)
			{
				if (prevX -x > 16)
				{
					x += prevX - x- 16;
					prevX = x;
				}
				if (prevY - y > 16)
				{
					y += prevY - y - 16;
					prevY = y;
				}
				isWalkingOnStair = false;
			}
		}
		if (!keyCode[DIK_UP] && !isWalkingOnStair  && !keyCode[DIK_RIGHT])
		{
			ChangeState(STATE_STAND_ONSTAIR_UP);
		}
		break;
	case STATE_STAND_ONSTAIR_DOWN:
		isWalkingOnStair = false;
		if (keyCode[DIK_UP] || keyCode[DIK_RIGHT])
		{
			ChangeState(STATE_WALK_ONSTAIR_UP);
		}
		if (keyCode[DIK_DOWN] || keyCode[DIK_LEFT])
		{
			ChangeState(STATE_WALK_ONSTAIR_DOWN);
		}
		break;
	case STATE_WALK_ONSTAIR_DOWN:
		
		isOnStair = true;
		isWalkingOnStair = true;
		if (stair_type == 1)
		{
			isReverse = false;
			vx = -SIMON_WALKING_SPEED / 2;
			vy = SIMON_WALKING_SPEED / 2;
			if (y - prevY >= 16 && prevX - x >= 16)
			{
				if (prevX - x > 16)
				{
					x += prevX - x - 16;
					prevX = x;
				}
				if (y - prevY > 16)
				{
					y -= y - prevY - 16;
					prevY = y;
				}
				isWalkingOnStair = false;
			}
		}
		else if (stair_type == 2)
		{
			isReverse = true;
			vx = SIMON_WALKING_SPEED / 2;
			vy = SIMON_WALKING_SPEED / 2;
			if (y - prevY >= 16 && x-prevX >= 16)
			{
				if (x-prevX > 16)
				{
					x -= x- prevX - 16;
					prevX = x;
				}
				if (y - prevY > 16)
				{
					y -= y - prevY - 16;
					prevY = y;
				}
				isWalkingOnStair = false;
			}
		}
		if (!keyCode[DIK_DOWN] && !isWalkingOnStair && !keyCode[DIK_LEFT])
		{
			ChangeState(STATE_STAND_ONSTAIR_DOWN);
		}
		break;
	case STATE_INJURED:
		if (vy == 0)
		{
			ChangeState(STATE_STANDING);
		}
		break;
	}

}
