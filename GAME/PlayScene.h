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
using namespace std;
class PlayScene : public Scene
{
private:
	CSimon* simon;
	

public:
	vector<Enemy*>listenemy;
	vector<LPGAMEOBJECT>objects;
	Grid *grid;

	bool cancreateghost;
	DWORD timetocreateghost;
	int countghost;	

	bool cancreatepanther;
	bool outofareacreatepanther;
	int countpanther;

	bool cancreatebat;
	DWORD timetocreatebat;
	int countbat;

	bool cancreatefishman;
	DWORD timetocreatefishman;
	int countfishman;

	RECT downstair;
	RECT upstair;
	RECT downstair2;
	RECT upstair2;

	bool isgoingthroughdoor;
	Door* door1;
	RECT DOOR1;

	bool isgoingthroughendrect;
	invisibleObject* endrectmap1;

	PlayScene(int level);
	~PlayScene();
	int level;
	Map *map;
	bool gotoleft;
	bool gotoright;

	void Update(DWORD dt);

	void UpdatePlayer(DWORD dt);
	void UpdateObjects(DWORD dt);
	void LoadResources();
	void Render();									// Tải Scene lên màn hình
	void OnKeyDown(int key);						// Xử lí Scene khi nhấn phím
	void OnKeyUp(int key);							// Xử lí Scene khi thả phím
};
