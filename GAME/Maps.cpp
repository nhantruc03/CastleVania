#include "Maps.h"



Maps* Maps::_instance = NULL;

void Maps::LoadResources()
{
	for (int i = 1; i <= 2; ++i)
	{
		_maps.push_back(new Map(i));
	}
}

Map * Maps::GetMap(int level)
{
	return _maps[level - 1];
}

Maps* Maps::GetInstance()
{
	if (_instance == NULL)
		_instance = new Maps();
	return _instance;
}
