#pragma once
#include"Sprites.h"
#include"Camera.h"
#include"Font.h"
#include"GameObject.h"
#define ICON_X 327
#define ICON_Y 50

#define POWER_X 450
#define POWER_Y 60

#define SCORE_X 110
#define SCORE_Y 20

#define TIME_X 300
#define TIME_Y 20

#define STAGE_X 470
#define STAGE_Y 21

#define HEARTH_X 400
#define HEARTH_Y 40

#define LIVES_X 400
#define LIVES_Y 60
#define HEALTH_WIDTH 11
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

