#pragma once
#include"GameGlobal.h"
#include"Sprites.h"
#include<fstream>	
#include"Camera.h"
#include"GameObject.h"
#include"Brick.h"
class Map
{

	vector<LPGAMEOBJECT>objects;
	Camera * camera;
public:
	int templevel;
	int maplevel;
	int** MapMatrix;
	int columns;
	int rows;
	Map(int level);
	void Render();
	void Setcam(Camera* cam) { camera = cam; };

	vector<LPGAMEOBJECT> get_objectlist();

	~Map();
};

