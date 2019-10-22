#include "Map.h"
#include"HoldItemObject.h"
#include<fstream>

Map::Map(int level)
{
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
			Sprites::GetInstance()->Get(maplevel, MapMatrix[i][j] -1)->Draw((j * 32) + 16, (i * 32) + 16);
		}
	}
}


vector<LPGAMEOBJECT> Map::get_BricksList()
{
	objects.clear();
	if (maplevel == TAG_MAP1)
	{
		std::ifstream iFile;
		char fileName[30];
		sprintf_s(fileName, "Res\\Text\\objects.txt");
		iFile.open(fileName);
		while (!iFile.eof())
		{

			int holder_id, item_id, x, y;
			iFile >> holder_id >> item_id >> x >> y;
			HoldItemObject * HoldObject = new HoldItemObject(holder_id, item_id);
			HoldObject->SetPosition(x, y);
			objects.push_back(HoldObject);

		}
		iFile.close();
		/*for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				if (MapMatrix[i][j] == 49)
				{

					CBrick *brick = new CBrick();
					brick->SetPosition((j * 32) + 16, (i * 32) + 16);
					objects.push_back(brick);

				}
			}
		}*/
		CBrick* brick = new CBrick();
		brick->SetPosition(768, 304);
		brick->width = 1536;
		brick->height = 32;
		objects.push_back(brick);
	}
	else
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				if (MapMatrix[i][j] == 15)
				{

					CBrick *brick = new CBrick();
					brick->SetPosition((j * 32) + 16, (i * 32) + 16);
					objects.push_back(brick);

				}
			}
		}
	}

	return objects;
}

Map::~Map()
{

}
