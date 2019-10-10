#pragma once
#include"GameGlobal.h"
#include"SpritesManager.h"
#include<fstream>	
#include"Camera.h"
class map
{
	
	Camera * camera;
public:
	int** MapMatrix;
	int columns;
	int rows;
	map();
	void Render();
	void Setcam(Camera* cam) { camera = cam; };


	~map();
};

