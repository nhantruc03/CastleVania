#include "Phantom_bat.h"
#include"Camera.h"
#include"Simon.h"
Phantom_bat::Phantom_bat()
{
	ready = false;
	//gostraigt = false;
	this->tag = TAG_ENEMY;
	this->type = TYPE_ENEMY_BOSS_1;
	this->x = 5343;
	this->y = 32 + BOARD_HEIGHT;
	this->direct = 0;
	isSleeping = true;
	this->isDead = false;
	this->ishit = false;

	AddAnimation(tag, 8); // animation sleeping
	AddAnimation(tag, 9); // animation moving

	this->vx =	0;
	this->vy = 0;
	this->width = 96;
	this->height = 48;
	this->health = 16;

	timewait = 0;
	animation = animations[0];
	attackstraigt = false;
	attackcurve = false;
	attacking = false;
	srand(time(NULL));
	canshoot = false;
}

void Phantom_bat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Enemy::Update(dt, coObjects);
	if (!SIMON->timeusingstopwatch)
	{
		if (timewait > 0)
		{
			timewait -= dt;
		}
		if (SIMON->x > 5386 && isSleeping)
		{
			isSleeping = false;
			animation = animations[1];
			ChangeState(STATE_GO_POS_2);
		}
		if (!isSleeping)
		{
			// khi di ra khoi khung man hinh
			if (GetBoundingBox().right > Camera::GetInstance()->GetBound().right || GetBoundingBox().left < Camera::GetInstance()->GetBound().left || GetBoundingBox().top < Camera::GetInstance()->GetBound().top || GetBoundingBox().bottom > Camera::GetInstance()->GetBound().bottom - 32)
			{
				int ran = rand() % 4;
				if (ran == 0)
				{
					ChangeState(STATE_GO_POS_1);
				}
				else if (ran == 1)
				{
					if (SIMON->x >= 5392) // giua khung man hinh zone boss
					{
						ChangeState(STATE_GO_POS_2);
					}
					else
					{
						ChangeState(STATE_GO_POS_5);
					}
				}
				else if (ran == 2)
				{
					ChangeState(STATE_GO_POS_3);
				}
				else if (ran == 3)
				{
					ChangeState(STATE_GO_POS_4);
				}

			}

			if (attackstraigt == true)
			{
				vy -= 0.00001f*dt; // cho Vy tru` mot it de giong nhu dang bay
			}
			if (attackcurve == true && timewait <= 0)
			{
				vy -= 0.0003f *dt; // gia lap luc hut nhu cua SIMON khi nhay, nhung nguoc lai
			}
		}
		Update_State();
		CGameObject::Update(dt, coObjects);
		x += dx;
		y += dy;
	}
}
void Phantom_bat::ChangeState(int newState)
{
	if (state != STATE_IDLE)
	{
		prevState = state;
	}
	state = newState;
	switch (state)
	{
	case STATE_BODY_ATTACK_1: // attack kieu truc dien
		attackstraigt = true;
		targetX = SIMON->x;
		targetY = SIMON->y;
		timewait = 1500;
		break;
	case STATE_BODY_ATTACK_2: // attack kieu bay cau vong
		attackcurve = true;
		if (prevState == STATE_GO_POS_2)
		{
			targetX = TAGGETX_POS5; // chon toa do x cua POS 5 lam target
		}
		else if (prevState == STATE_GO_POS_5)
		{
			targetX = TAGGETX_POS2; // chon toa do x cua POS 2 lam target
		}
		timewait = 1500;
		break;
	case STATE_SHOOT:
		prevX = x;
		prevY = y;
		if (!canshoot)
		{
			targetX = SIMON->x;
			targetY = SIMON->y;
			bulletvx = (targetX - prevX) / 1000;
			bulletvy = (targetY - prevY) / 1000;
			canshoot = true;
		}
		ChangeState(STATE_IDLE);
		break;
	case STATE_GO_POS_1:
		attackstraigt = false;
		attackcurve = false;
		prevX = x;
		prevY = y;
		targetX = TAGGETX_POS1;
		targetY = TARGETY_POS1 +BOARD_HEIGHT;
		break;
	case STATE_GO_POS_2:
		attackstraigt = false;
		attackcurve = false;
		prevX = x;
		prevY = y;
		targetX = TAGGETX_POS2;
		targetY = TARGETY_POS2 + BOARD_HEIGHT;
		break;
	case STATE_GO_POS_3:
		attackstraigt = false;
		attackcurve = false;
		prevX = x;
		prevY = y;
		targetX = TAGGETX_POS3;
		targetY = TARGETY_POS3 + BOARD_HEIGHT;
		break;
	case STATE_GO_POS_4:
		attackstraigt = false;
		attackcurve = false;
		prevX = x;
		prevY = y;
		targetX = TAGGETX_POS4;
		targetY = TARGETY_POS4 + BOARD_HEIGHT;
		break;
	case STATE_GO_POS_5:
		attackstraigt = false;
		attackcurve = false;
		prevX = x;
		prevY = y;
		targetX = TAGGETX_POS5;
		targetY = TARGETY_POS5 + BOARD_HEIGHT;
		break;
	case STATE_IDLE:
		attacking = false;
		attackcurve = false;
		attackstraigt = false;
		prevX = x;
		prevY = y;
		vx = vy = 0;
		timewait = 1500;
		break;
	default:
		break;
	}
}
void Phantom_bat::Update_State()
{
	switch (state)
	{
	case STATE_BODY_ATTACK_1:
		if (timewait <= 0 && !attacking)
		{
			attacking = true;
			timewait = 0;
			vx = (targetX - prevX) / (1000); // cho đi 1 giay
			vy = (targetY - prevY) / (1000);
		}
		break;
	case STATE_BODY_ATTACK_2:
		if (timewait <= 0 && !attacking)
		{
			attacking = true;
			timewait = 0;
			vx = (targetX - prevX) / (1500); // cho đi 1.5 giay
			vy = 0.25f;
		}
		break;
	case STATE_GO_POS_1: case STATE_GO_POS_2: case STATE_GO_POS_3: case STATE_GO_POS_4:case STATE_GO_POS_5:
		vx = (targetX - prevX) / (2000); // cho đi 2 giay
		vy = (targetY - prevY) / (2000);
		if (targetX < prevX)
		{
			if (x<=targetX)
			{
				x = targetX;
				ChangeState(STATE_IDLE);
			}
		}
		else
		{
			if (x >= targetX)
			{
				x = targetX;
				ChangeState(STATE_IDLE);
			}
		}
		break;
	case STATE_IDLE:
		if (timewait <= 0)
		{
			int ran = rand() % 8;
			if (ran == 0)
			{
				ChangeState(STATE_GO_POS_1);
			}
			else if (ran == 1)
			{
				if (SIMON->x >= 5392) // giua khung hinh zone boss
				{
					ChangeState(STATE_GO_POS_2);
				}
				else
				{
					ChangeState(STATE_GO_POS_5);
				}
			}
			else if (ran == 2)
			{
				ChangeState(STATE_GO_POS_3);
			}
			else if (ran == 3)
			{
				ChangeState(STATE_GO_POS_4);
			}
			else
			{
			
				int ran2 = rand() % 3;
				if (ran2 == 0)
				{
					ChangeState(STATE_SHOOT);
				}
				else
				{
					if (prevState == STATE_GO_POS_2 || prevState == STATE_GO_POS_5)
					{
						ChangeState(STATE_BODY_ATTACK_2);
					}
					else
						ChangeState(STATE_BODY_ATTACK_1);
				}
			}
		}
		break;
	default:
		break;
	}
}
Phantom_bat::~Phantom_bat()
{
}
