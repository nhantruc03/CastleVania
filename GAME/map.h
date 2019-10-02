#pragma once
#include"GameGlobal.h"
#include"SpritesManager.h"
#include<fstream>	
#include"Camera.h"
class map
{
	int columns;
	int rows;
	int** MapMatrix;
	Camera * camera;
public:
	map();
	void Render();
	void Setcam(Camera* cam) { camera = cam; };


	~map();
};

