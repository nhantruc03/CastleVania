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
#include<fstream>
#include<string>
#define ZONE_GHOST1 1
#define ZONE_GHOST2 2
#define ZONE_GHOST3 3
#define ZONE_PANTHER 4
#define ZONE_BAT 5
#define ZONE_FISHMAN1 6
#define ZONE_FISHMAN2 7
#define ZONE_FISHMAN3 8
#define ZONE_FISHMAN4 9
#define ZONE_FULLMAP 10
#define ZONE_STAGE1 11
#define ZONE_STAGE2 12
#define ZONE_STAGE3 13
#define ZONE_BOSS 14

using namespace std;
class PlayScene : public Scene
{
private:
	CSimon* simon;
public:

	Board* board;

	float timetospawnCrystal;
	bool checkBossDead;

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

	void Update(DWORD dt);

	void createeffectsteam(float x, float y);

	void UpdatePlayer(DWORD dt);
	void UpdateObjects(DWORD dt);
	void LoadResources(int level);
	void Render();
	void OnKeyDown(int key);
	void OnKeyUp(int key);
	void RandomSpawnItem(float x, float y);
	void EnemyHandle(DWORD dt);
	void DoorHandle();
	void getzone(int level);

	void getValue();

};
