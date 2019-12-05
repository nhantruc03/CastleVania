#include "Map.h"
#include"HoldItemObject.h"
#include<fstream>
#include"invisibleObject.h"
#include"Special_brick.h"
#include"Door.h"
Map::Map(int level)
{
	templevel = level;
	rows = columns = 0;
	std::ifstream iFile;
	char fileName[30];
	sprintf_s(fileName, "Res\\Text\\map%d.txt",level);
	iFile.open(fileName);
	iFile >> rows;
	iFile >> columns;


	// ma tran 2 chieu de luu vi tri cua tileset
	MapMatrix = new int*[rows];
	for (int i = 0; i < rows; i++)
	{
		MapMatrix[i] = new int[columns];
		for (int j = 0; j < columns; j++)
		{
			iFile >> MapMatrix[i][j];
		}
	}
	iFile.close();
	switch (level)
	{
	case 1:
		maplevel = TAG_MAP1;
		break;
	case 2:
		maplevel = TAG_MAP2;
		break;
	}

	camera = Camera::GetInstance();
}

void Map::Render()
{
	int firstcolumn = camera->GetBound().left / 32;
	if (firstcolumn < 0)
	{
		firstcolumn = 0;
	}
	int lastcolumn = camera->GetBound().right / 32;
	if (lastcolumn+1 <= columns)
	{
		lastcolumn += 1;
	}
	int firstrow = (camera->GetBound().top - BOARD_HEIGHT) / 32;
	int lastrow;
	if (templevel == 1)
	{
		lastrow = 10;
	}
	else
	{
		lastrow = 11;
		if (camera->movedownstair)
		{
			lastrow = 23;
		}
	}
	for (int i = firstrow; i < lastrow; i++)
	{
		for (int j = firstcolumn; j < lastcolumn; j++)
		{
			Sprites::GetInstance()->Get(maplevel, MapMatrix[i][j] -1)->Draw((j * 32) + 16, (i * 32) + 16+BOARD_HEIGHT);
		}
	}
}

Map::~Map()
{

}
