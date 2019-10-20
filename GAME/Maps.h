#pragma once
#include"Map.h"
class Maps
{
private:
	std::vector<Map*> _maps;
	static Maps* _instance;

public:
	void LoadResources();
	Map* GetMap(int level);
	static Maps* GetInstance();
};

