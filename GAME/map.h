#pragma once
#include"GameGlobal.h"
#include"SpritesManager.h"
#include<fstream>	
class map
{
	int columns;
	int rows;
	int** MapMatrix;
public:
	map();
	void Render();

	~map();
};

