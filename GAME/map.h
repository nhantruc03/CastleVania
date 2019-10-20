#pragma once
#include"GameGlobal.h"
#include"Sprites.h"
#include<fstream>	
#include"Camera.h"
#include"GameObject.h"
#include"Brick.h"
class Map
{

	vector<LPGAMEOBJECT>bricks;
	Camera * camera;
public:
	int** MapMatrix;
	int columns;
	int rows;
	Map();
	void Render();
	void Setcam(Camera* cam) { camera = cam; };

	vector<LPGAMEOBJECT> get_BricksList();

	~Map();
};

