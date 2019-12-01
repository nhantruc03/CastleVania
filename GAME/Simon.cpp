#include "Simon.h"
#include"WeaponsManager.h"
#include"Brick.h"
#include"HoldItemObject.h"
#include"Item.h"
#include"Enemy.h"
#include"Door.h"
#include"Special_brick.h"
#include"money_400.h"	
#include"money_700.h"
#include"steam.h"
#include"invisibleObject.h"
#include"Board.h"
CSimon*CSimon::_instance = NULL;
CSimon::CSimon()
{

	tag = TAG_SIMON;
	LoadAnimation();
	morningstarlevel = 1;
	width = SIMON_WIDTH;
	height = SIMON_HEIGHT;

	srand(time(NULL));

	numweaponcanthrow = 1;
	numcurrentweaponthrowing = 0;

	ishit = false;
	untouchable = 0;
	upgrade_time = 0;
	usingholycross = false;
	isinjured = false;

	falling = false;
	delayforsitting = 0;
	
	sitting = false;
	secondweapon = NULL;
	jumping = false;
	heart = 5;
	attacking = false;

	isgoingtostair = false;
	isWalkingOnStair = false;
	isOnStair = false;
	goup = gotoleft = gotoright = godown = false;
	usinggoldpotion = false;
	isReverse = true;
	check_auto_move = false;
	isDead = false;
	checkkillboss = false;
	instages = 1;
	lives = 4;
	health = 16;
	count_attack_after_kill_boss = 0;
	globle_time = GLOBAL_TIME;
	ChangeState(STATE_STANDING);

	respawnx = 4000;
	respawny = 5;

}
void CSimon::Respawn()
{
	//if (instages == 1)
	//{
	//	Camera::GetInstance()->inzone1 = true;
	//	Camera::GetInstance()->inzone2 = false;
	//	Camera::GetInstance()->inzone3 = false;
	//	Camera::GetInstance()->inzoneBoss = false;
	//	Camera::GetInstance()->movedownstair = false;
	//	Camera::GetInstance()->SetPosition(x, 0);
	//	x = 30;//5200;
	//	y = 5;
	//}
	//else if (instages == 2)
	//{
	//	Camera::GetInstance()->inzone1 = false;
	//	Camera::GetInstance()->inzone2 = true;
	//	Camera::GetInstance()->inzone3 = false;
	//	Camera::GetInstance()->inzoneBoss = false;
	//	Camera::GetInstance()->movedownstair = false;
	//	Camera::GetInstance()->SetPosition(x, 0);
	//	x = 3200;//5200;
	//	y = 5;
	//}
	//else if (instages == 3)
	//{
	//	Camera::GetInstance()->inzone1 = false;
	//	Camera::GetInstance()->inzone2 = false;
	//	Camera::GetInstance()->inzone3 = true;
	//	Camera::GetInstance()->inzoneBoss = false;
	//	Camera::GetInstance()->movedownstair = false;
	//	Camera::GetInstance()->SetPosition(x, 0);
	//	x = 4200;//5200;
	//	y = 5;
	//}
	if (Camera::GetInstance()->movedownstair)
	{
		Camera::GetInstance()->movedownstair = false;
	}
	x = respawnx;
	y = respawny;
	


	lives -= 1;
	health = 16;
	isWalkingOnStair = false;
	isOnStair = false;
	check_auto_move = false;
	sitting = false;
	jumping = false;
	attacking = false;
	isReverse = true;
	numweaponcanthrow = 1;
	if (isDead)
	{
		secondweapon = NULL;
		heart = 5;
	}
	isDead = false;
	goup = gotoleft = gotoright = godown = false;
	checkkillboss = false;
	count_attack_after_kill_boss = 0;
	globle_time = GLOBAL_TIME;
	ChangeState(STATE_STANDING);
}
void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (timeusingstopwatch)
	{
		timeusingstopwatch -= dt;
	}
	if (delayforsitting > 0)
	{
		delayforsitting -= dt;
	}
	if (timetorespawn > 0)
	{
		timetorespawn -= dt;
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

	CalcPotentialCollisions(coObjects, coEvents);
	if (GetTickCount() - untouchable_start > UNTOUCHABLETIME)
	{
		untouchable_start = 0;
		untouchable = 0;
		if (usinggoldpotion)
		{
			usinggoldpotion = false;
			ChangeTexture(1);
		}

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
			if (dynamic_cast<CBrick*>(e->obj) || dynamic_cast<Special_brick*>(e->obj))
			{

				if (isOnStair)
				{
					x += dx;
					y += dy;
				}
				else
				{
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
			}
			if (!isDead)
			{
				if (dynamic_cast<Door*>(e->obj))
				{
					if (nx < 0)
					{
						x += dx;
					}
				}
				if (dynamic_cast<Item *>(e->obj))
				{
					if (ny != 0)
					{
						y -= min_ty * dy + ny * 0.2f;
					}
					switch (e->obj->type)
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
					case TYPE_ITEM_HOLY_CROSS:
						usingholycross = true;
						break;
					case TYPE_ITEM_WHIP:
						upgrade_time = UPGRADE_TIME;
						morningstarlevel += 1;
						if (morningstarlevel > 3)
						{
							morningstarlevel = 3;
						}
						break;
					case TYPE_ITEM_MONEY_400:
						score += 400;
						listeffect.push_back(new money_400(x + 40, y - 20));
						break;
					case TYPE_ITEM_MONEY_700:
						score += 700;
						listeffect.push_back(new money_700(x + 40, y - 20));
						break;
					case TYPE_ITEM_AXE:
						secondweapon = TYPE_WEAPON_AXE;
						break;
					case TYPE_ITEM_GOLD_POTION:
						usinggoldpotion = true;
						ChangeTexture(2);
						StartUntouchable();
						break;
					case TYPE_ITEM_CHICKEN:
						health += 4;
						if (health > 16)
						{
							health = 16;
						}
						break;
					case TYPE_ITEM_DOUBLE_SHOT:
						numweaponcanthrow = 2;
						break;
					case TYPE_ITEM_CRYSTAL:
						health = 16;
						checkkillboss = true;
						break;
					}
					e->obj->isDead = true;
				}
				if (dynamic_cast<Enemy*> (e->obj) || (dynamic_cast<Weapon*>(e->obj) && e->obj->type == TYPE_ENEMY_BULLET))
				{
					StartUntouchable();
					if (dynamic_cast<Enemy*> (e->obj) && dynamic_cast<Enemy*> (e->obj)->type == TYPE_ENEMY_BAT)
					{
						e->obj->isHit();
					}

					if (!isOnStair) // khi khong tren cau thang thi bi vang
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
					else
					{
						x -= min_tx * dx + nx * 0.2f; // tranh bi day di khi tren cau thang
						y -= min_ty * dy + ny * 0.2f;
						health -= 2;
					}
				}
				if (dynamic_cast<invisibleObject*>(e->obj))
				{
					x += dx;
					y += dy;

					if (e->obj->type == TYPE_INVI_O_WATER)
					{
						if (!isDead)
						{

							listeffect.push_back(new steam(x, e->obj->GetBoundingBox().top, 1));
							listeffect.push_back(new steam(x, e->obj->GetBoundingBox().top, 2));
							listeffect.push_back(new steam(x, e->obj->GetBoundingBox().top, 3));
							ChangeState(STATE_DEAD);
						}
					}

				}
			}
			else
			{
				x -= min_tx * dx + nx * 0.2f;
				y -= min_ty * dy + ny * 0.2f;

			}
		}
	}

	// cho roi nhanh hon khi roi tu cau thang xuong
	if (vy > 0 && vy<999 &&!jumping && !isinjured && !isOnStair && !sitting)
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
		delayforsitting = TIME_DELAY_FOR_SITTING;
		ChangeState(STATE_FALL);
	}
	// kiem tra va cham voi quai vat va chuyen state injured
	if (ishit)
	{
		ChangeState(STATE_INJURED);
		ishit = false;
	}
	// xu ly va nhan vat va cham voi object khi object xuat hien ben trong nhan vat
	if (!isDead)
	{
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
					case TYPE_ITEM_HOLY_CROSS:
						usingholycross = true;
						break;
					case TYPE_ITEM_WHIP:
						upgrade_time = UPGRADE_TIME;
						morningstarlevel += 1;
						if (morningstarlevel > 3)
						{
							morningstarlevel = 3;
						}
						break;
					case TYPE_ITEM_MONEY_400:
						score += 400;
						listeffect.push_back(new money_400(x + 40, y - 20));
						break;
					case TYPE_ITEM_MONEY_700:
						score += 700;
						listeffect.push_back(new money_700(x + 40, y - 20));
						break;
					case TYPE_ITEM_AXE:
						secondweapon = TYPE_WEAPON_AXE;
						break;
					case TYPE_ITEM_GOLD_POTION:
						usinggoldpotion = true;
						ChangeTexture(2);
						StartUntouchable();
						
						break;
					case TYPE_ITEM_CHICKEN:
						health += 4;
						if (health > 16)
						{
							health = 16;
						}
						break;
					case TYPE_ITEM_DOUBLE_SHOT:
						numweaponcanthrow = 2;
						break;
					case TYPE_ITEM_CRYSTAL:
						health = 16;
						checkkillboss = true;
						break;
					}
					coObjects->at(i)->isDead = true;
					break;
				case TAG_INVISIBLE_OBJECT:
					switch (coObjects->at(i)->type)
					{
					case TYPE_INVI_O_GO_UP_STAIR_LTR:
						if (y < coObjects->at(i)->y)
						{
							isCollidewith_UPLTR = true;
						}
						break;
					case TYPE_INVI_O_GO_UP_STAIR_RTL:
						if (y < coObjects->at(i)->y)
						{
							isCollidewith_UPRTL = true;
						}
						break;
					case TYPE_INVI_O_GO_DOWN_STAIR_RTL:
						isCollidewith_DWNRTL = true;
						break;
					case TYPE_INVI_O_GO_DOWN_STAIR_LTR:
						isCollidewith_DWNLTR = true;
						break;
					case TYPE_ITEM_DOUBLE_SHOT:
						numweaponcanthrow = 2;
						break;
					case TYPE_INVI_O_WATER:
						if (!isDead)
						{
							isDead = true;
							listeffect.push_back(new steam(x , coObjects->at(i)->GetBoundingBox().top, 1));
							listeffect.push_back(new steam(x, coObjects->at(i)->GetBoundingBox().top, 2));
							listeffect.push_back(new steam(x, coObjects->at(i)->GetBoundingBox().top, 3));
						}
						break;
					case  TYPE_INVI_O_RESPAWN:
						respawnx = coObjects->at(i)->x;
						respawny = coObjects->at(i)->y;
						break;
					}
					stair_collide = coObjects->at(i)->GetBoundingBox();
					break;
				case TAG_ENEMY:case TAG_WEAPON:
					if (untouchable == 0)
					{
						StartUntouchable();
						if (coObjects->at(i)->type == TYPE_ENEMY_BAT)
						{
							coObjects->at(i)->isHit();
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
	}

	if (checkkillboss) // dong tac danh 3 lan sau khi lum item crystal
	{
		check_auto_move = true;
		keyCode.clear();
		if (!attacking && count_attack_after_kill_boss < 3)
		{
			Weapon* weapon = WeaponsManager::CreateWeapon(TYPE_WEAPON_MORNINGSTAR);
			weapon->isReverse = isReverse;
			Weapons.push_back(weapon);
			ChangeState(STATE_ATTACK);
		}
	}
	if (usingholycross)  // hieu ung holycross
	{
		StartUsingHolyCross();
	}
	Update_State(); // de sau doan kiem tra AABB de kiem tra va cham voi diem len xuong cau thang

	inoutstair_handle(dt); // xu ly buoc dau tien len xuong cau thang


	for (int i = 0; i < Weapons.size(); i++)
	{
		if (Weapons[i]->isDead)
		{
			if (Weapons[i]->type != TYPE_WEAPON_MORNINGSTAR)
			{
				numcurrentweaponthrowing -= 1;
			}
			Weapons.erase(Weapons.begin() + i);
		}
		else
		{
			Weapons[i]->Update(dt, coObjects);
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

}
void CSimon::inoutstair_handle(DWORD dt)
{
	if ((((isCollidewith_UPLTR||isCollidewith_UPRTL) && keyCode[DIK_UP]&& !isOnStair) || ((isCollidewith_DWNRTL||isCollidewith_DWNLTR) && keyCode[DIK_DOWN] && !isOnStair)) && (State==STATE_STANDING||State==STATE_WALKING) && !falling)
	{
		isgoingtostair = true;
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
	if (isgoingtostair)
	{
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
					isgoingtostair = false;
					gotoright = false;
					gotoleft = false;
					if (isCollidewith_UPLTR || isCollidewith_UPRTL)
					{
						goup = true;
					}
					else if (isCollidewith_DWNRTL || isCollidewith_DWNLTR)
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
				if (!isOnStair) 
				{
					x = stair_collide.left + (stair_collide.right - stair_collide.left) / 2;
					isgoingtostair = false;
					gotoright = false;
					gotoleft = false;
					if (isCollidewith_UPLTR || isCollidewith_UPRTL)
					{
						goup = true;
					}
					else if (isCollidewith_DWNRTL || isCollidewith_DWNLTR)
					{
						godown = true;
					}
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
		vy = 999;
	}
	else if (State == STATE_WALK_ONSTAIR_DOWN && (isCollidewith_UPLTR||isCollidewith_UPRTL))
	{
		y = prevY + 16;
		ChangeState(STATE_STANDING);
		vy = 999;
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
		if (untouchable)
		{
			if (usinggoldpotion)
			{
				alpha = 255;
			}
			else
			{
				alpha = 127;
			}
		}
	}
	curAni->Render(x, y, alpha,r,g,b);
	for (Weapon* o : Weapons)
	{
		o->Render();
	}
}

void CSimon::OnKeyDown(int key)
{
	if (!upgrade_time && !isDead)
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
					if (keyCode[DIK_UP] && State != STATE_SITTING && numcurrentweaponthrowing < numweaponcanthrow && (secondweapon ==1 || secondweapon==2 || secondweapon==4) && heart >= 1)
					{
						heart -= 1;
						numcurrentweaponthrowing += 1;
						Weapon* weapon = WeaponsManager::CreateWeapon(secondweapon);
						weapon->isReverse = isReverse;
						Weapons.push_back(weapon);

						if (isWalkingOnStair)
						{
							vx = vy = 0;
						}
						ChangeState(STATE_ATTACK);
					}
					if (keyCode[DIK_UP] && secondweapon == 3 && heart >= 5 && !timeusingstopwatch)
					{
						heart -= 5;
						timeusingstopwatch = TIME_USE_STOP_WATCH;
					}
				}
			}
			break;
		case DIK_M:
			secondweapon = 1;
			heart += 5;
			morningstarlevel += 1;
			if (morningstarlevel > 3)
			{
				morningstarlevel = 1;
			}
			numweaponcanthrow = 2;
			break;
		case DIK_R:
			if (instages == 1)
			{
				x = 3200;
				y = 5;
				instages = 2;
				Camera::GetInstance()->inzone1 = false;
				Camera::GetInstance()->inzone2 = true;
				Camera::GetInstance()->movedownstair = false;
				Camera::GetInstance()->inzone3 = false;
				break;
			}
			if (instages == 2)
			{
				x = 4200;
				y = 5;
				instages = 3;
				Camera::GetInstance()->inzone1 = false;
				Camera::GetInstance()->inzone2 = false;
				Camera::GetInstance()->movedownstair = false;
				Camera::GetInstance()->inzone3 = true;
				break;
			}
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
		health -= 2;
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
		vy = -SIMON_JUMP_SPEED_Y/1.3f;
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
	case STATE_DEAD:
		timetorespawn = TIME_TO_RESPAWN;
		untouchable = 0;
		vx = 0;
		isDead = true;
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

		if (!keyCode[DIK_DOWN]&& delayforsitting<=0)
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
			if (delayforsitting)
			{
				ChangeState(STATE_SITTING);
			}
			else
				ChangeState(STATE_STANDING);
		}
		break;
	case STATE_ATTACK:case STATE_SIT_ATTACKING:case STATE_ATTACK_ONSTAIR_DOWN:case STATE_ATTACK_ONSTAIR_UP:

		if (curAni->CheckEndAni())
		{
			if (checkkillboss)
			{
				count_attack_after_kill_boss += 1;
			}
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
		if (keyCode[DIK_UP] || (keyCode[DIK_RIGHT] && stair_type==1) || (keyCode[DIK_LEFT] && stair_type == 2))
		{
			ChangeState(STATE_WALK_ONSTAIR_UP);
		}
		if (keyCode[DIK_DOWN] || (keyCode[DIK_RIGHT] && stair_type == 2) || (keyCode[DIK_LEFT] && stair_type == 1))
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
					x = prevX + 16;
				}
				if (prevY - y > 16)
				{
					y = prevY - 16;
				}
				prevX = x;
				prevY = y;
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
					x = prevX - 16;
				}
				if (prevY - y > 16)
				{
					y = prevY - 16;
				}
				prevX = x;
				prevY = y;
				isWalkingOnStair = false;
			}
		}
		if (!keyCode[DIK_UP] && !isWalkingOnStair  && ((!keyCode[DIK_LEFT] && stair_type == 2) || (!keyCode[DIK_RIGHT] && stair_type == 1)))
		{
			ChangeState(STATE_STAND_ONSTAIR_UP);
		}
		break;
	case STATE_STAND_ONSTAIR_DOWN:
		isWalkingOnStair = false;
		if (keyCode[DIK_UP] || (keyCode[DIK_RIGHT] && stair_type == 1) || (keyCode[DIK_LEFT] && stair_type == 2))
		{
			ChangeState(STATE_WALK_ONSTAIR_UP);
		}
		if (keyCode[DIK_DOWN] || (keyCode[DIK_RIGHT] && stair_type == 2) || (keyCode[DIK_LEFT] && stair_type == 1))
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
					x = prevX - 16;
				}
				if (y - prevY > 16)
				{
					y = prevY + 16;
				}
				prevX = x;
				prevY = y;
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
					x = prevX + 16;
				}
				if (y - prevY > 16)
				{
					y = prevY + 16;
				}
				prevX = x;
				prevY = y;
				isWalkingOnStair = false;
			}
		}
		if (!keyCode[DIK_DOWN] && !isWalkingOnStair && ((!keyCode[DIK_LEFT] && stair_type==1) || (!keyCode[DIK_RIGHT] && stair_type == 2)))
		{
			ChangeState(STATE_STAND_ONSTAIR_DOWN);
		}
		break;
	case STATE_INJURED:
		if (vy == 0)
		{
			if (health <= 0)
			{
				ChangeState(STATE_DEAD);
			}
			else
				ChangeState(STATE_STANDING);
		}
		break;
	}

}

void CSimon::StartUsingHolyCross()
{
	timeuseholycross += dt;
	if (timeuseholycross >= TIME_USE_HOLY_CROSS)
	{
		usingholycross = false;
		D3DCOLOR_BACKGROUND = BACKGROUND_COLOR;
		timeuseholycross = 0;
	}
	else
	{
		timetochangecolorwhileusingholycross += dt;
		if (timetochangecolorwhileusingholycross >= TIME_TO_CHANGE_COLOR_WHILE_USING_HOLY_CROSS)
		{
			timetochangecolorwhileusingholycross = 0;

			if (D3DCOLOR_BACKGROUND == BACKGROUND_COLOR)
			{
				D3DCOLOR_BACKGROUND = BACKGROUND_COLOR_WHILE_USING_HOLY_CROSS;
			}
			else
			{
				D3DCOLOR_BACKGROUND = BACKGROUND_COLOR;
			}
		}
	}
}

void CSimon::LoadAnimation()
{
	animations.clear();
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
	AddAnimation(tag, 14); // dead
}

void CSimon::ChangeTexture(int temp)
{
	switch (temp)
	{
	case 1:
		CTextures::GetInstance()->Add(TAG_SIMON, L"Res\\Image\\player.png", D3DCOLOR_XRGB(255, 0, 255));
		Sprites::GetInstance()->LoadResources(2);
		Animations::GetInstance()->LoadResources(2);
		LoadAnimation();
		Board::GetInstance()->LoadResources();
		break;
	case 2:
		CTextures::GetInstance()->Add(TAG_SIMON, L"Res\\Image\\player_2.png", D3DCOLOR_XRGB(255, 0, 255));
		Sprites::GetInstance()->LoadResources(2);
		Animations::GetInstance()->LoadResources(2);
		LoadAnimation();
		Board::GetInstance()->LoadResources();
		break;
	default:
		break;
	}
}
