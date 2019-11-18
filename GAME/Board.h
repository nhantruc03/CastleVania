#pragma once
#include"Sprites.h"
#include"Camera.h"
#include"Font.h"
#include"GameObject.h"
class Board
{
	static Board * _instance;
public:
	float timetoplusscore;
	static Board* GetInstance();
	int boss_health;
	Font* font;
	float x, y;
	LPSPRITE sprite_health;
	LPSPRITE sprite;
	LPSPRITE icon_weapon;
	LPSPRITE power;
	Board();
	string FillNumber(string s, UINT MaxNumber);
	void update(CGameObject* boss,float dt);
	void render();
	void Health_draw();
	void LoadResources();
	
};

