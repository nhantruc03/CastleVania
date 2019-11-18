#include "Grid.h"
#include"HoldItemObject.h"
#include"invisibleObject.h"
#include"Brick.h"
#include"Special_brick.h"
#include"Door.h"
#include<fstream>
#include"Item.h"
#include"Simon.h"
#include"Panther.h"
Grid::Grid(int level)
{
	nextid = 0;
	srand(time(NULL));
	maplevel = level;
	camera = Camera::GetInstance();
	countpanther = 3;
}


Grid::~Grid()
{
}

void Grid::Loadresources()
{
	countpanther = 3;
	for (int i = 0; i < GRID_CELL_MAX_ROW; i++)
		for (int j = 0; j < GRID_CELL_MAX_COLUMN; j++)
		{
			cells[i][j].clear();
		}

	CGameObject* tempobject = new CGameObject();
	std::ifstream iFile;
	char fileName[30];
	sprintf_s(fileName, "Res\\Text\\grid%d.txt", maplevel);
	iFile.open(fileName);
	int id;
	if (!iFile.fail())
	{
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
				invisibleObject* invisibleO= new invisibleObject();;
				if (type == TYPE_INVI_O_WATER)
				{
					iFile >> width >> height;
					invisibleO = new invisibleObject(width,height);
				}
				else
					invisibleO = new invisibleObject();
				
				invisibleO->type = type;
				invisibleO->SetPosition(x, y );
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
				door->SetPosition(x, y );
				tempobject = door;
			}
			break;
			case 'p':
			{
				int x, y, direction;
				iFile >> x >> y >> direction;
				Panther* panther = new Panther(x, y , direction);
				tempobject = panther;
			}
			break;
			}
			tempobject->id = id;
			int top, bottom, left, right;
			iFile >> top >> bottom >> left >> right;
			tempobject->topcell = top;
			tempobject->botcell = bottom;
			tempobject->leftcell = left;
			tempobject->rightcell = right;
			for (int i = top; i <= bottom; i++)
				for (int j = left; j <= right; j++)
					cells[i][j].push_back(tempobject);
			nextid = id+1;

		}
		iFile.close();
	}
	else
	{

		vector<CGameObject*>list_temp;
		char fileobject[30];
		sprintf_s(fileobject, "Res\\Text\\objects%d.txt", maplevel);
		iFile.open(fileobject);

		while (!iFile.eof())
		{
			char objects_type;
			iFile >> objects_type;
			//iFile >> id;
			switch (objects_type)
			{
			case 'h':
			{
				int holder_id, item_id, x, y;
				iFile >> holder_id >> item_id >> x >> y;
				HoldItemObject * HoldObject = new HoldItemObject(holder_id, item_id);
				HoldObject->SetPosition(x, y+BOARD_HEIGHT);
				tempobject = HoldObject;
			}
			break;
			case 'i':
			{
				int type, x, y, width, height;
				iFile >> type >> x >> y;
				invisibleObject* invisibleO= new invisibleObject();;
				if (type == TYPE_INVI_O_WATER)
				{
					iFile >> width >> height;
					invisibleO = new invisibleObject(width, height);
				}
				else
					invisibleO = new invisibleObject();
				invisibleO->type = type;
				invisibleO->SetPosition(x, y + BOARD_HEIGHT);
				tempobject = invisibleO;
			}
			break;
			case 'b':
			{
				float x, y, width, height;
				iFile >> x >> y >> width >> height;
				CBrick* brick = new CBrick();
				brick->SetPosition(x, y + BOARD_HEIGHT);
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
				sb->SetPosition(x, y + BOARD_HEIGHT);
				tempobject = sb;
			}
			break;
			case 'd':
			{
				int door_type, x, y;
				iFile >> door_type >> x >> y;
				Door * door = new Door(door_type);
				door->SetPosition(x, y + BOARD_HEIGHT);
				tempobject = door;
			}
			break;
			case 'p':
			{
				int x, y, direction;
				iFile >> x >> y >> direction;
				Panther* panther = new Panther(x, y + BOARD_HEIGHT, direction);
				tempobject = panther;
			}
			break;
			}
			tempobject->id = nextid++;

			int top = (int)((tempobject->y - tempobject->height / 2) / GRID_CELL_HEIGHT);
			int bottom = (int)((tempobject->y + tempobject->height / 2) / GRID_CELL_HEIGHT);
			int left = (int)((tempobject->x - tempobject->width / 2) / GRID_CELL_WIDTH);
			int right = (int)((tempobject->x + tempobject->width / 2) / GRID_CELL_WIDTH);
			tempobject->topcell = top;
			tempobject->botcell = bottom;
			tempobject->leftcell = left;
			tempobject->rightcell = right;

			for (int i = top; i <= bottom; i++)
				for (int j = left; j <= right; j++)
					cells[i][j].push_back(tempobject);

			list_temp.push_back(tempobject);
		}
		iFile.close();
		std::ofstream ofile;
		ofile.open(fileName);

		for (CGameObject* o : list_temp)
		{
			switch (o->tag)
			{
			case TAG_HOLDER:
				ofile << "h" << " " << o->id << " " << o->type << " " << dynamic_cast<HoldItemObject*>(o)->item << " " << o->x << " " << o->y ;
				break;
			case TAG_INVISIBLE_OBJECT:
				if (o->type != TYPE_INVI_O_WATER)
				{
					ofile << "i" << " " << o->id << " " << o->type << " " << o->x << " " << o->y;
				}
				else
				{
					ofile << "i" << " " << o->id << " " << o->type << " " << o->x << " " << o->y << " " << o->width << " " << o->height;
				}
				break;
			case TAG_BRICK:
				ofile << "b" << " " << o->id << " " << o->x << " " << o->y << " " << o->width << " " << o->height;
				break;
			case TAG_SPECIAL_BRICK:
				ofile << "s" << " " << o->id << " " << o->type << " " << dynamic_cast<Special_brick*>(o)->item << " " << o->x << " " << o->y;
				break;
			case TAG_DOOR:
				ofile << "d" << " " << o->id << " " << o->type << " " << o->x << " " << o->y;
				break;
			case TAG_ENEMY:
				ofile << "p" << " " << o->id << " " << o->x << " " << o->y << " " << dynamic_cast<Enemy*>(o)->direct;
				break;
			}
			if (o->id != nextid-1)
			{
				ofile << " " << o->topcell << " " << o->botcell << " " << o->leftcell << " " << o->rightcell << "\n";
			}
			else
			{
				ofile << " " << o->topcell << " " << o->botcell << " " << o->leftcell << " " << o->rightcell;
			}
		}
		ofile.close();

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
				if (cells[i][j].at(k)->isDead == false)
				{
					if (cells[i][j].at(k)->tag != TAG_ENEMY)
					{
						if (mapObject.find(cells[i][j].at(k)->id) == mapObject.end())
							mapObject[cells[i][j].at(k)->id] = cells[i][j].at(k);
					}
				}
				else
				{
					// insert item khi holder hoac special brick break
					if (cells[i][j].at(k)->tag == TAG_HOLDER && dynamic_cast<HoldItemObject*>(cells[i][j].at(k))->check_spawnitem == false)
					{
						dynamic_cast<HoldItemObject*>(cells[i][j].at(k))->check_spawnitem = true;
						int temp_id= dynamic_cast<HoldItemObject*>(cells[i][j].at(k))->item;
						if (SIMON->morningstarlevel < 3)
						{
							if (temp_id == TYPE_ITEM_HEART)
							{
								int random = rand() % 2;
								if (random == 0)
								{
									temp_id = TYPE_ITEM_WHIP;
								}
							}
						}
						Item* item = new Item(temp_id);
						item->SetPosition(dynamic_cast<HoldItemObject*>(cells[i][j].at(k))->x, dynamic_cast<HoldItemObject*>(cells[i][j].at(k))->y);
						insert(item);
					}
					else if (cells[i][j].at(k)->tag == TAG_SPECIAL_BRICK && dynamic_cast<Special_brick*>(cells[i][j].at(k))->check_spawnitem == false && dynamic_cast<Special_brick*>(cells[i][j].at(k))->item != -1)
					{
						dynamic_cast<Special_brick*>(cells[i][j].at(k))->check_spawnitem = true; // moi item chi duoc spawn 1 lan
						Item* item = new Item(dynamic_cast<Special_brick*>(cells[i][j].at(k))->item);
						item->SetPosition(dynamic_cast<Special_brick*>(cells[i][j].at(k))->x, dynamic_cast<Special_brick*>(cells[i][j].at(k))->y - 5);
						insert(item);
					}
				}
			}

	for (auto& x : mapObject)
	{
		ListObj.push_back(x.second);
	}
}

void Grid::GetListPanther(vector<Enemy*>& ListObj)
{
	ListObj.clear();

	unordered_map<int, Enemy*> mapPanthers;

	int bottom = (int)((camera->GetBound().bottom) / GRID_CELL_HEIGHT);
	int top = (int)((camera->GetBound().top) / GRID_CELL_HEIGHT);

	int left = (int)(camera->GetBound().left / GRID_CELL_WIDTH);
	int right = (int)(camera->GetBound().right / GRID_CELL_WIDTH);

	for (int i = top; i <= bottom; i++)
		for (int j = left; j <= right; j++)
			for (UINT k = 0; k < cells[i][j].size(); k++)
			{
				if (cells[i][j].at(k)->isDead == false)
				{
					if (cells[i][j].at(k)->tag == TAG_ENEMY)
					{
						if (mapPanthers.find(cells[i][j].at(k)->id) == mapPanthers.end())
							mapPanthers[cells[i][j].at(k)->id] = (Enemy*)cells[i][j].at(k);
					}
				}
				else
				{
					if (cells[i][j].at(k)->tag == TAG_ENEMY && dynamic_cast<Panther*>(cells[i][j].at(k))->check_dead_once == false)
					{
						dynamic_cast<Panther*>(cells[i][j].at(k))->check_dead_once = true;
						countpanther -= 1;
					}
				}
			}

	for (auto& x : mapPanthers)
	{
		ListObj.push_back(x.second);
	}
}

void Grid::insert(CGameObject *object)
{
	int top = (int)((object->y - object->height / 2) / GRID_CELL_HEIGHT);
	int bottom = (int)((object->y + object->height / 2) / GRID_CELL_HEIGHT);
	int left = (int)((object->x - object->width / 2) / GRID_CELL_WIDTH);
	int right = (int)((object->x + object->width / 2) / GRID_CELL_WIDTH);
	object->id = nextid++;
	for (int i = top; i <= bottom; i++)
		for (int j = left; j <= right; j++)
			cells[i][j].push_back(object);
}

void Grid::movepanther(Enemy * object, float x, float y)
{
	if (!camera->IsContain(object->GetBoundingBox()))
		return;
	Panther* temppanther = (Panther*)object;

	for (int i = 0; i < GRID_CELL_MAX_ROW; i++)
	{
		for (int j = 0; j < GRID_CELL_MAX_COLUMN; j++)
		{
			for (UINT k = 0; k < cells[i][j].size(); k++)
			{
				if (cells[i][j].at(k)->tag == TAG_ENEMY && cells[i][j].at(k)->id==temppanther->id)
				{
					cells[i][j].erase(cells[i][j].begin() + k); // xoa het tat ca cac grid cu chua panther
				}
			}
		}
	}

	int top = (int)((temppanther->y - temppanther->height / 2) / GRID_CELL_HEIGHT);
	int bottom = (int)((temppanther->y + temppanther->height / 2) / GRID_CELL_HEIGHT);
	int left = (int)((temppanther->x - temppanther->width / 2) / GRID_CELL_WIDTH);
	int right = (int)((temppanther->x + temppanther->width / 2) / GRID_CELL_WIDTH);
	for (int i = top; i <= bottom; i++)
		for (int j = left; j <= right; j++)
			cells[i][j].push_back(temppanther); // cap nhat lai grid moi cho panther

}

void Grid::respawnpanther()
{
	unordered_map<int, Enemy*> mapPanthers; // can luu lai panther truoc khi xoa de co so lieu de respawn
	for (int i = 0; i < GRID_CELL_MAX_ROW; i++)
	{
		for (int j = 0; j < GRID_CELL_MAX_COLUMN; j++)
		{
			for (UINT k = 0; k < cells[i][j].size(); k++)
			{
				if (cells[i][j].at(k)->tag == TAG_ENEMY)
				{
					if (mapPanthers.find(cells[i][j].at(k)->id) == mapPanthers.end())
					{
						mapPanthers[cells[i][j].at(k)->id] = (Enemy*)cells[i][j].at(k);
					}
					cells[i][j].erase(cells[i][j].begin() + k);
				}
			}
		}
	}
	int direction = abs(1106 - SIMON->x) < abs(2240 - SIMON->x) ? -1 : 1; // panther xoay mat vao simon
	for (auto& x : mapPanthers)
	{
		Panther* panther = new Panther(x.second->spawnx, x.second->spawny, direction);
		panther->id = x.second->id;
		insert(panther);

	}
	countpanther = 3;
}