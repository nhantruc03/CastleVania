#include<iostream>
#include<fstream>
#include<vector>
#include"HoldItemObject.h"
#include"Door.h"
#include"Panther.h"
#include"Special_brick.h"
#include"invisibleObject.h"
#include"CGameObject.h"
#include"Brick.h"
#define TAG_SIMON 0
#define TAG_WEAPON 1
#define TYPE_WEAPON_MORNINGSTAR 0
#define TYPE_WEAPON_DAGGER 1
#define TYPE_WEAPON_HOLY_WATER 2
#define TYPE_WEAPON_STOP_WATCH 3
#define TYPE_WEAPON_AXE 4
#define TYPE_ENEMY_BULLET 5
#define TAG_MAP1 2
#define TAG_HOLDER 3
#define TYPE_HOLDER_FIREPILLAR 0
#define TYPE_HOLDER_CANDLE 1
#define TAG_ITEM 4
#define TYPE_ITEM_BIG_HEART 0
#define TYPE_ITEM_WHIP 1
#define TYPE_ITEM_DAGGER 2
#define TYPE_ITEM_HEART 3
#define TYPE_ITEM_MONEY_1000 4
#define TYPE_ITEM_MONEY_700 5
#define TYPE_ITEM_MONEY_400 6
#define TYPE_ITEM_HOLY_WATER 7
#define TYPE_ITEM_HOLY_CROSS 8
#define TYPE_ITEM_STOP_WATCH 9
#define TYPE_ITEM_CHICKEN 10
#define TYPE_ITEM_AXE 11
#define TYPE_ITEM_DOUBLE_SHOT 12
#define TYPE_ITEM_GOLD_POTION 13
#define TYPE_ITEM_CRYSTAL 14
#define TAG_EFFECT 5
#define TYPE_EFFECT_BURN 0 // Burn gom 3 sprite 0 1 2 
#define TYPE_EFFECT_HIT 3
#define TYPE_EFFECT_400 4
#define TYPE_EFFECT_700 5
#define TYPE_EFFECT_BIG_BURN 6
#define TYPE_EFFECT_STEAM 6
#define TYPE_EFFECT_BROKENBRICK 7
#define TAG_MAP2 6
#define TAG_BRICK 7
#define TAG_ENEMY 8
#define TYPE_ENEMY_GHOST 0
#define TYPE_ENEMY_PANTHER 1
#define TYPE_ENEMY_BAT 2
#define TYPE_ENEMY_FISHMAN 3
#define TYPE_ENEMY_BOSS_1 4
#define TAG_DOOR 9
#define TAG_SPECIAL_BRICK 10
#define TYPE_SPECIAL_BRICK1 0
#define TYPE_SPECIAL_BRICK2	1
#define TAG_BOARD 11
#define TAG_FONT 12
#define BOARD_HEIGHT 80
#define TAG_INVISIBLE_OBJECT 999
#define TYPE_INVI_O_ENDRECT_MAP1	0
#define TYPE_INVI_O_GO_UP_STAIR_LTR 1
#define TYPE_INVI_O_GO_UP_STAIR_RTL -1
#define TYPE_INVI_O_GO_DOWN_STAIR_RTL 2
#define TYPE_INVI_O_GO_DOWN_STAIR_LTR -2
#define TYPE_INVI_O_GO_DOWN_BASEMENT 100
#define TYPE_INVI_O_GO_UP_BASEMENT -100
#define TYPE_INVI_O_WATER 3
#define TYPE_INVI_O_RESPAWN 4
using namespace std;

int main()
{
	for (int i = 1; i <= 2; i++)
	{
		int nextid = 0;
		CGameObject* tempobject = new CGameObject();
		std::ifstream iFile;
		char fileName[30];
		sprintf_s(fileName, "Res\\Text\\grid%d.txt", i);
		iFile.open(fileName);
		int id;
		if (iFile.fail())
		{

			vector<CGameObject*>list_temp;
			char fileobject[30];
			sprintf_s(fileobject, "Res\\Text\\objects%d.txt", i);
			iFile.open(fileobject);

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
					HoldObject->SetPosition(x, y + BOARD_HEIGHT);
					tempobject = HoldObject;
				}
				break;
				case 'i':
				{
					int type, x, y, width, height;
					iFile >> type >> x >> y;
					invisibleObject* invisibleO = new invisibleObject();;
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

				int top = (int)((tempobject->y - tempobject->height / 2) / 470);
				int bottom = (int)((tempobject->y + tempobject->height / 2) / 472);
				int left = (int)((tempobject->x - tempobject->width / 2) / 260);
				int right = (int)((tempobject->x + tempobject->width / 2) / 260);
				tempobject->topcell = top;
				tempobject->botcell = bottom;
				tempobject->leftcell = left;
				tempobject->rightcell = right;



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
					ofile << "h" << " " << o->id << " " << o->type << " " << dynamic_cast<HoldItemObject*>(o)->item << " " << o->x << " " << o->y;
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
					ofile << "p" << " " << o->id << " " << o->x << " " << o->y << " " << o->direct;
					break;
				}
				if (o->id != nextid - 1)
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
	return 0;
}