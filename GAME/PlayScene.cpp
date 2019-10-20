#include "PlayScene.h"
#include"HoldItemObject.h"
#include"Item.h"
#include<fstream>
#include"Maps.h"
PlayScene::PlayScene(int level)
{
	this->level = level;
	map = Maps::GetInstance()->GetMap(this->level);
	simon = CSimon::GetInstance();
	simon->SetPosition(30.0f, 255.0f);
	simon->Respawn();
	camera = Camera::GetInstance();
	objects.clear();
	objects = map->get_BricksList();
}


PlayScene::~PlayScene()
{

}

void PlayScene::Update(DWORD dt)
{
	if (simon->upgrade_time)
	{
		simon->upgrade_time -= dt;
	}
	else
	{
		UpdatePlayer(dt);
		camera->SetPosition(simon->x, 0);
		camera->Update(level);
		UpdateObjects(dt);
		if (simon->x > 1300 && simon->x <= 1410 && level == 1)
		{
			simon->ChangeState(STATE_WALKING);
			keyCode[DIK_RIGHT] = true;
			simon->vx = 0.05f;
			if (simon->x > 1400)
			{
				keyCode[DIK_RIGHT] = false;
				level += 1;
				SceneManager::GetInstance()->ReplaceScene(new PlayScene(level));
			}
		}
	}

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
					it = objects.erase(it);

					objects.push_back(testitem);
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
	
	
}

void PlayScene::Render()
{
	map->Render();
	for (CGameObject* o : objects)
	{
		RECT temp = o->GetBoundingBox();
		if (camera->IsContain(temp))
		{
			o->Render();
		}
	}
	simon->Render();
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

