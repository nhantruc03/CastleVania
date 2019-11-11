#pragma once
#include"GameGlobal.h"
#include"GameObject.h"

#include"Panther.h"
#define GRID_CELL_WIDTH (SCREEN_WIDTH/2.0f)
#define GRID_CELL_HEIGHT (SCREEN_HEIGHT)
#define GRID_CELL_MAX_ROW 4 // số dòng tối đa;
#define GRID_CELL_MAX_COLUMN 23 // số cột tối đa

class Grid
{
public:
	int countpanther;
	int nextid;
	int lastid;
	int maplevel;
	Camera* camera;
	vector<CGameObject*> cells[GRID_CELL_MAX_ROW][GRID_CELL_MAX_COLUMN];
	vector<LPGAMEOBJECT>objects;
	//vector<LPGAMEOBJECT>panthers;
	Grid(int level);
	~Grid();
	void Loadresources();
	void GetListObject(vector<CGameObject*>& ListObj);
	void GetListPanther(vector<Enemy*>& ListObj);
	void insert(CGameObject* object);
	void movepanther(Enemy* object, float x, float y);
	void respawnpanther();
	//void removepanther(CGameObject* object);
};

