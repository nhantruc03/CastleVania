#pragma once
#include "Scene.h"
#include<unordered_set>
#include "Simon.h"
#include"map.h"
#include"Brick.h"
#include"Door.h"
#include"Grid.h"
#include"Enemy.h"
#include"invisibleObject.h"
#include"listeffect_global.h"
#include"Weapon.h"
#include"Board.h"
using namespace std;
class PlayScene : public Scene
{
private:
	CSimon* simon;
public:

	Board* board;

	float timetospawnCrystal;
	bool checkBossDead;

	bool test = false;
	vector<Weapon*>list_enemy_weapon;
	vector<Enemy*>listenemy;
	vector<Enemy*>listenemy_tronggrid;
	vector<LPGAMEOBJECT>objects;


	Enemy* boss;

	Grid *grid;

	bool cancreateghost;
	float timetocreateghost;
	int countghost;	

	bool cancreatepanther;
	bool outofareacreatepanther;
	int countpanther;

	bool cancreatebat;
	float timetocreatebat;
	int countbat;

	bool cancreatefishman;
	float timetocreatefishman;
	int countfishman;

	RECT downstair;
	RECT upstair;
	RECT downstair2;
	RECT upstair2;

	bool isgoingthroughdoor;
	bool isgoingthroughdoor2;
	Door* door1;
	Door* door2;
	

	bool isgoingthroughendrect;
	invisibleObject* endrectmap1;

	PlayScene(int level);
	~PlayScene();
	int level;
	Map *map;
	bool gotoleft;
	bool gotoright;

	void Update(DWORD dt);

	void createeffectsteam(float x, float y);

	void UpdatePlayer(DWORD dt);
	void UpdateObjects(DWORD dt);
	void LoadResources(int level);
	void Render();									// Tải Scene lên màn hình
	void OnKeyDown(int key);						// Xử lí Scene khi nhấn phím
	void OnKeyUp(int key);							// Xử lí Scene khi thả phím
	void RandomSpawnItem(float x, float y);
};
