#include "PlayScene.h"
#include"FirePillar.h"
#include"ItemsManager.h"

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
	vector<LPGAMEOBJECT>::iterator it = objects.begin();
	while (it != objects.end())
	{
		CGameObject *o = *it;
		switch (o->tag)
		{
		case TAG_HOLDER:
		{
			HoldItemObject*h = (FirePillar*)o;
			if (h->isDead)
			{
				Item * testitem = ItemsManager::CreateItem(h->item);
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
		
		++it;
	}
}

void PlayScene::LoadResources()
{
	CTextures::GetInstance()->LoadResources();
	SpritesManager::GetInstance()->LoadResources();
	AnimationsManager::GetInstance()->LoadResources();
	map1 = new Map();
	simon = CSimon::GetInstance();
	simon->SetPosition(30.0f, 255.0f);
	camera = Camera::GetInstance();
	simon->Respawn();
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
	FirePillar* test = new FirePillar();
	test->SetPosition(192, 256);
	test->item = 0;
	objects.push_back(test);
	test = new FirePillar();
	test->SetPosition(448, 256);
	test->item = 1;
	objects.push_back(test);
	test = new FirePillar();
	test->SetPosition(704, 256);
	test->item = 1;
	objects.push_back(test);
	test = new FirePillar();
	test->SetPosition(976, 256);
	test->item = 0;
	objects.push_back(test);
	test = new FirePillar();
	test->SetPosition(1216, 256);
	test->item = 2;
	objects.push_back(test);

	
}

void PlayScene::Render()
{
	
	map1->Render();

	simon->Render();
	for (auto o : objects)
	{
		o->Render();
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

