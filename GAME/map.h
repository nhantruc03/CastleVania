#pragma once
#include"GameGlobal.h"
#include"SpritesManager.h"
#include<fstream>	
#include"Camera.h"
class Map
{
	
	Camera * camera;
public:
	int** MapMatrix;
	int columns;
	int rows;
	Map();
	void Render();
	void Setcam(Camera* cam) { camera = cam; };


	~Map();
};

