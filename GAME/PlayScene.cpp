#include "PlayScene.h"
#include"HoldItemObject.h"
#include"Item.h"
#include<fstream>
PlayScene::PlayScene()
{
	LoadResources();
}


PlayScene::~PlayScene()
{

}

void PlayScene::Update(DWORD dt)
{
	
	UpdatePlayer(dt);
	camera->SetPosition(simon->x, 0);
	camera->Update();
	UpdateObjects(dt);
	

}

void PlayScene::UpdatePlayer(DWORD dt)
{
	simon->Update(dt,&objects);
}

void PlayScene::UpdateObjects(DWORD dt)
{
	vector<LPGAMEOBJECT>::iterator it = objects.begin(); // iterator: con tro chi den 1 phan tu ben trong container, khong can biet thu tu phan tu ben trong mang
	while (it != objects.end())
	{

		CGameObject *o = *it;
		RECT temp = o->GetBoundingBox();
		if (camera->IsContain(temp))
		{
			switch (o->tag)
			{
			case TAG_HOLDER:
			{
				HoldItemObject*h = (HoldItemObject*)o;
				if (h->isDead)
				{
					Item * testitem = new Item(h->item);
					testitem->SetPosition(h->x, h->y);
					objects.push_back(testitem);
					it = objects.erase(it);
					delete h;
					continue;
				}
				h->Update(dt, &objects);
				break;
			}
			case TAG_ITEM:
				Item*i = (Item*)o;
				if (i->isDead)
				{
					it = objects.erase(it);
					delete i;
					continue;
				}
				i->Update(dt, &objects);
				break;
			}
		}
		++it;
	}
}

void PlayScene::LoadResources()
{
	CTextures::GetInstance()->LoadResources();
	Sprites::GetInstance()->LoadResources();
	Animations::GetInstance()->LoadResources();
	map1 = new Map();
	simon = CSimon::GetInstance();
	simon->SetPosition(30.0f, 255.0f);
	simon->Respawn();

	camera = Camera::GetInstance();
	
	for (int i = 0; i < map1->rows; i++)
	{
		for (int j = 0; j < map1->columns; j++)
		{
			if (map1->MapMatrix[i][j] == 49)
			{

				CBrick *brick = new CBrick();
				brick->SetPosition((j * 32) + 16, (i * 32) + 16);
				objects.push_back(brick);

			}
		}
	}
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
}

void PlayScene::Render()
{
	
	map1->Render();
	simon->Render();
	for (CGameObject* o : objects)
	{
		RECT temp = o->GetBoundingBox();
		if (camera->IsContain(temp))
		{
			o->Render();
		}
	}
}

void PlayScene::OnKeyDown(int key)
{
	keyCode[key] = true;
	simon->OnKeyDown(key);
}

void PlayScene::OnKeyUp(int key)
{
	keyCode[key] = false;
	simon->OnKeyUp(key);

}

