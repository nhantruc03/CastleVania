#include "Board.h"
#include<string>
#include"Simon.h"
Board*Board::_instance = NULL;
Board * Board::GetInstance()
{
	if (_instance == NULL)
		_instance = new Board();
	return _instance;
}

Board::Board()
{
	timetoplusscore = 0;
	font = new Font();
	LoadResources();
	x = SCREEN_WIDTH/2;
	y = 40;
}

string Board::FillNumber(string s, UINT MaxNumber)
{
	while (s.size() < MaxNumber)
		s = "0" + s;
	return s;
}

void Board::update(CGameObject * boss,float dt)
{
	if (boss != NULL)
	{
		boss_health = boss->health;
	}
	else
		boss_health = 16;

	// icon second weapon
	switch (SIMON->secondweapon)
	{
	case TYPE_WEAPON_DAGGER:
		icon_weapon = Sprites::GetInstance()->Get(TAG_BOARD, 4);
		break;
	case TYPE_WEAPON_HOLY_WATER:
		icon_weapon = Sprites::GetInstance()->Get(TAG_BOARD, 5);
		break;
	case TYPE_WEAPON_STOP_WATCH:
		icon_weapon = Sprites::GetInstance()->Get(TAG_BOARD, 8);
		break;
	case TYPE_WEAPON_AXE:
		icon_weapon = Sprites::GetInstance()->Get(TAG_BOARD, 6);
		break;
	default:
		break;
	}

	// icon double shot
	switch (SIMON->numweaponcanthrow)
	{
	case 2:
		power = Sprites::GetInstance()->Get(TAG_BOARD, 7);
		break;
	default:
		break;
	}

	if (SIMON->checkkillboss && !SIMON->attacking && SIMON->count_attack_after_kill_boss == 3)
	{
		timetoplusscore += dt;
		if (timetoplusscore >= 50)
		{
			timetoplusscore = 0;
			if (globle_time > 0)
			{
				globle_time -= 2000;
				SIMON->score += 20;
				if (globle_time < 0)
				{
					globle_time = 0;
				}
			}
			else
			{
				if (SIMON->heart > 0)
				{
					SIMON->heart -= 1;
					SIMON->score += 100;
				}
			}
		}
	}

}

void Board::render()
{
	sprite->Draw(x, y);
	if (icon_weapon != NULL)
	{
		icon_weapon->Draw(x + 67, y + 10);
	}
	if (power != NULL)
	{
		power->Draw(x + 190, y + 20);
	}

	font->Draw(x - 150, y-20, FillNumber(to_string(SIMON->score), 6));

	font->Draw(x+40 , y -20, FillNumber(to_string((int)globle_time/1000), 4));

	font->Draw(x + 210, y -19, FillNumber(to_string(SIMON->instages), 2));

	font->Draw(x +140, y , FillNumber(to_string(SIMON->heart), 2)); // Số lượng tim nhặt dc
	font->Draw(x + 140, y + 20, FillNumber(to_string(SIMON->lives), 2)); // số mạng sông

	Health_draw();
	
}

void Board::Health_draw()
{
	int i, j;
	sprite_health = Sprites::GetInstance()->Get(TAG_BOARD, 1); // sprite mau cua simon
	for (i = 0; i < SIMON->health; i++)
	{
		sprite_health->Draw(x - 150 + i * 11, y);
	}
	sprite_health = Sprites::GetInstance()->Get(TAG_BOARD, 2); // sprite mat mau
	for (j=i;j<16;j++)
	{
		sprite_health->Draw(x - 150 + j * 11, y);
	}

	sprite_health = Sprites::GetInstance()->Get(TAG_BOARD, 3); // prite mau con Boss
	for (i = 0; i < boss_health; i++)
	{
		sprite_health->Draw(x - 150 + i * 11, y+20);
	}
	sprite_health = Sprites::GetInstance()->Get(TAG_BOARD, 2);
	for (j = i; j < 16; j++)
	{
		sprite_health->Draw(x - 150 + j * 11, y+20);
	}
}

void Board::LoadResources()
{
	sprite = Sprites::GetInstance()->Get(TAG_BOARD, 0); // khung den cua score board
	Sprites::GetInstance()->Add(TAG_BOARD, Sprites::GetInstance()->Get(TAG_ITEM, TYPE_ITEM_DAGGER)); //4
	Sprites::GetInstance()->Add(TAG_BOARD, Sprites::GetInstance()->Get(TAG_ITEM, TYPE_ITEM_HOLY_WATER));//5
	Sprites::GetInstance()->Add(TAG_BOARD, Sprites::GetInstance()->Get(TAG_ITEM, TYPE_ITEM_AXE));//6
	Sprites::GetInstance()->Add(TAG_BOARD, Sprites::GetInstance()->Get(TAG_ITEM, TYPE_ITEM_DOUBLE_SHOT));//7
	Sprites::GetInstance()->Add(TAG_BOARD, Sprites::GetInstance()->Get(TAG_ITEM, TYPE_ITEM_STOP_WATCH));//8
}



