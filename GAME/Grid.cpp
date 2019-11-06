#include "Grid.h"
#include"HoldItemObject.h"
#include"invisibleObject.h"
#include"Brick.h"
#include"Special_brick.h"
#include"Door.h"
#include<fstream>
#include"Item.h"
Grid::Grid(int level)
{
	nextid = 200;
	maplevel = level;
	camera = Camera::GetInstance();
}


Grid::~Grid()
{
}

void Grid::Loadresources()
{
	for (int i = 0; i < GRID_CELL_MAX_ROW; i++)
		for (int j = 0; j < GRID_CELL_MAX_COLUMN; j++)
		{
			cells[i][j].clear();
		}

	CGameObject* tempobject=new CGameObject();
	std::ifstream iFile;
	char fileName[30];
	sprintf_s(fileName, "Res\\Text\\grid%d.txt",maplevel);
	iFile.open(fileName);
	int id;
	while (!iFile.eof())
	{
		char objects_type;
		iFile >> objects_type;
		iFile >> id;
		switch (objects_type)
		{
		case 'h':
		{
			int holder_id, item_id, x, y;
			iFile >> holder_id >> item_id >> x >> y;
			HoldItemObject * HoldObject = new HoldItemObject(holder_id, item_id);
			HoldObject->SetPosition(x, y);
			tempobject = HoldObject;
		}
		break;
		case 'i':
		{
			int type, x, y, width, height;
			iFile >> type >> x >> y;
			invisibleObject* invisibleO = new invisibleObject();
			invisibleO->type = type;
			invisibleO->SetPosition(x, y);
			tempobject = invisibleO;
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
			tempobject = brick;
		}
			break;
		case 's':
		{
			int sb_id, item_id, x, y;
			iFile >> sb_id >> item_id >> x >> y;
			Special_brick * sb = new Special_brick(sb_id, item_id);
			sb->SetPosition(x, y);
			tempobject = sb;
		}
		break;
		case 'd':
		{
			int door_type, x, y;
			iFile >> door_type >> x >> y;
			Door * door = new Door(door_type);
			door->SetPosition(x, y);
			tempobject = door;
		}
		break;
		}
		tempobject->id = id;
		int top = (int)((tempobject->y - tempobject->height / 2) / GRID_CELL_HEIGHT);
		int bottom = (int)((tempobject->y + tempobject->height) / GRID_CELL_HEIGHT);
		int left = (int)((tempobject->x - tempobject->width / 2) / GRID_CELL_WIDTH);
		int right = (int)((tempobject->x + tempobject->width) / GRID_CELL_WIDTH);

		for (int i = top; i <= bottom; i++)
			for (int j = left; j <= right; j++)
				cells[i][j].push_back(tempobject);
		nextid = id;
		
	}
}

void Grid::GetListObject(vector<CGameObject*>& ListObj)
{
	ListObj.clear();

	unordered_map<int, CGameObject*> mapObject;

	int bottom = (int)((camera->GetBound().bottom) / GRID_CELL_HEIGHT);
	int top = (int)((camera->GetBound().top) / GRID_CELL_HEIGHT);

	int left = (int)(camera->GetBound().left / GRID_CELL_WIDTH);
	int right = (int)(camera->GetBound().right / GRID_CELL_WIDTH);

	for (int i = top; i <= bottom; i++)
		for (int j = left; j <= right; j++)
			for (UINT k = 0; k < cells[i][j].size(); k++)
			{
				if (cells[i][j].at(k)->isDead==false)
				{
					if (mapObject.find(cells[i][j].at(k)->id) == mapObject.end())
						mapObject[cells[i][j].at(k)->id] = cells[i][j].at(k);
				}
				else
				{
					if (cells[i][j].at(k)->tag == TAG_HOLDER && dynamic_cast<HoldItemObject*>(cells[i][j].at(k))->check_spawnitem == false)
					{
						dynamic_cast<HoldItemObject*>(cells[i][j].at(k))->check_spawnitem = true;
						Item* item = new Item(dynamic_cast<HoldItemObject*>(cells[i][j].at(k))->item);
						item->SetPosition(dynamic_cast<HoldItemObject*>(cells[i][j].at(k))->x, dynamic_cast<HoldItemObject*>(cells[i][j].at(k))->y);
						item->id = ++nextid;
						insert(item);
					}
					else if (cells[i][j].at(k)->tag == TAG_SPECIAL_BRICK && dynamic_cast<Special_brick*>(cells[i][j].at(k))->check_spawnitem == false && dynamic_cast<Special_brick*>(cells[i][j].at(k))->item != -1)
					{
						dynamic_cast<Special_brick*>(cells[i][j].at(k))->check_spawnitem = true;
						Item* item = new Item(dynamic_cast<Special_brick*>(cells[i][j].at(k))->item);
						item->SetPosition(dynamic_cast<Special_brick*>(cells[i][j].at(k))->x, dynamic_cast<Special_brick*>(cells[i][j].at(k))->y-5);
						item->id = ++nextid;
						insert(item);
					}
					cells[i][j].erase(cells[i][j].begin() + k);
				}
			}

	for (auto& x : mapObject)
	{
		ListObj.push_back(x.second);
	}
}

void Grid::insert(CGameObject *object)
{
	int top = (int)((object->y - object->height / 2) / GRID_CELL_HEIGHT);
	int bottom = (int)((object->y + object->height) / GRID_CELL_HEIGHT);
	int left = (int)((object->x - object->width / 2) / GRID_CELL_WIDTH);
	int right = (int)((object->x + object->width) / GRID_CELL_WIDTH);

	for (int i = top; i <= bottom; i++)
		for (int j = left; j <= right; j++)
			cells[i][j].push_back(object);
}

void Grid::update()
{
}
