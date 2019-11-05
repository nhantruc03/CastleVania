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


vector<LPGAMEOBJECT> Map::get_objectlist()
{
	objects.clear();

	std::ifstream iFile;
	char fileName[30];
	sprintf_s(fileName, "Res\\Text\\objects%d.txt", templevel);
	iFile.open(fileName);
	while (!iFile.eof())
	{
		char objects_type;
		iFile >> objects_type;
		switch (objects_type)
		{
		case 'h':
		{
			int holder_id, item_id, x, y;
			iFile >> holder_id >> item_id >> x >> y;
			HoldItemObject * HoldObject = new HoldItemObject(holder_id, item_id);
			HoldObject->SetPosition(x, y);
			objects.push_back(HoldObject);
		}
		break;
		case 'i':
		{
			int type, x, y, width, height;
			iFile >> type >> x >> y;
			invisibleObject* invisibleO = new invisibleObject();
			invisibleO->type = type;
			invisibleO->SetPosition(x, y);
			objects.push_back(invisibleO);
		}
		break;
		case 'b':
		{
			float x, y, width, height;
			iFile >> x >> y >> width >> height;
			CBrick* brick = new CBrick();
			brick->SetPosition(x, y);
			brick->width = width;
			brick->height = height;
			objects.push_back(brick); }
		break;
		case 's':
		{
			int sb_id, item_id, x, y;
			iFile >> sb_id >> item_id >> x >> y;
			Special_brick * sb = new Special_brick(sb_id, item_id);
			sb->SetPosition(x, y);
			objects.push_back(sb);
		}
		break;
		case 'd':
		{
			int door_type, x, y;
			iFile >> door_type >> x >> y;
			Door * door = new Door(door_type);
			door->SetPosition(x, y);
			objects.push_back(door);
		}
		break;
		}
	}
	return objects;
}

Map::~Map()
{

}
