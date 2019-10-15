#include "Map.h"


Map::Map()
{
	rows = columns = 0;
	std::ifstream iFile;
	char fileName[30];
	sprintf_s(fileName, "Res\\Text\\map1.txt");
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

	camera = Camera::GetInstance();
}

void Map::Render()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			RECT tileset;
			tileset.left = j * 32;
			tileset.right = tileset.left + 32;
			tileset.top = i * 32;
			tileset.bottom = tileset.top + 32;
			// kiem tra xem vi tri cua tileset co dang nam trong camera khong ?
			if (camera->IsContain(tileset) == false)
			{
				continue;
			}
			SpritesManager::GetInstance()->Get(TAG_MAP1, MapMatrix[i][j] -1)->Draw((j * 32) + 16, (i * 32) + 16);
		}
	}
}


Map::~Map()
{

}
