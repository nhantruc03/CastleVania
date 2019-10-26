#include "PlayScene.h"
#include"HoldItemObject.h"
#include"Item.h"
#include<fstream>
#include"Maps.h"
#include"invisibleObject.h"
PlayScene::PlayScene(int level)
{
	keyCode.clear();
	this->level = level;
	map = Maps::GetInstance()->GetMap(this->level);
	simon = CSimon::GetInstance();
	simon->SetPosition(1500, 5.0f);
	simon->Respawn();
	camera = Camera::GetInstance();
	objects.clear();
	objects = map->get_BricksList();
	switch (level)
	{
	case 1:
		endrect.left = 1376;
		endrect.right = 1408;
		endrect.top = 286;
		endrect.bottom = 288;
		break;
	case 2:
		downstair.left = 3200;
		downstair.right = 3300;
		downstair.top = 320 ;
		downstair.bottom = 321;

		downstair2.left = 3800;
		downstair2.right = 3900;
		downstair2.top = 320;
		downstair2.bottom = 321;

		upstair.left = 3200;
		upstair.right = 3300;
		upstair.top = 384;
		upstair.bottom = 385;

		upstair2.left = 3800;
		upstair2.right = 3900;
		upstair2.top = 384;
		upstair2.bottom = 385;


		break;
	}
	gotoleft = false;
	gotoright = false;
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
		camera->SetPosition(simon->x, camera->GetPosition().y);
		camera->Update(level);
		UpdateObjects(dt);
		if (level == 1)
		{
			if (simon->vx < 0 && simon->x < 16) simon->x= 16;
			if (simon->vx > 0 && simon->x > 1520)simon->x = 1520;
			if (simon->IsContain(endrect.left, endrect.top, endrect.right, endrect.bottom) && level == 1)
			{
				simon->check_auto_move = true;
				if (simon->x >= endrect.right)
				{

					gotoleft = true;
				}
				if (simon->x <= endrect.left)
				{
					gotoright = true;
					gotoleft = false;
				}
			}
			if (gotoleft)
			{
				simon->ChangeState(STATE_WALKING);
				simon->isReverse = false;
				simon->vx = -0.05f;
			}
			if (gotoright)
			{
				simon->ChangeState(STATE_WALKING);
				simon->isReverse = true;
				simon->vx = 0.05f;
				if (simon->x >= endrect.right)
				{
					simon->check_auto_move = false;
					level += 1;
					gotoleft = gotoright = false;
					SceneManager::GetInstance()->ReplaceScene(new PlayScene(level));
				}
			}
		}
		else
		{
			if (simon->vx < 0 && simon->x < 16) simon->x = 16;
			if (camera->movedownstair)
			{
				if (simon->vx < 0 && simon->x < 3088) simon->x = 3088;
				if (simon->vx > 0 && simon->x > 4080) simon->x = 4080;
			}
			if ((simon->IsContain(downstair.left, downstair.top, downstair.right, downstair.bottom) || simon->IsContain(downstair2.left, downstair2.top, downstair2.right, downstair2.bottom)) && (simon->y > downstair.top || simon->y > downstair2.top) && simon->State == STATE_WALK_ONSTAIR_DOWN)
			{
				camera->movedownstair = true;
				camera->SetPosition(simon->x, -384);
				simon->prevX = simon->x;
				simon->prevY = simon->y + 64;
				simon->SetPosition(simon->x, simon->y + 64);
			}
			else if ((simon->IsContain(upstair.left, upstair.top, upstair.right, upstair.bottom) || simon->IsContain(upstair2.left, upstair2.top, upstair2.right, upstair2.bottom)) && (simon->y < upstair.bottom || simon->y < upstair2.bottom) && simon->State == STATE_WALK_ONSTAIR_UP)
			{
				camera->movedownstair = false;
				camera->SetPosition(simon->x, 0);
				simon->prevX = simon->x;
				simon->prevY = simon->y - 64;
				simon->SetPosition(simon->x, simon->y - 64);
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
		LPGAMEOBJECT o = *it;
		RECT temp = o->GetBoundingBox();
		if (camera->IsContain(temp))
		{
			switch (o->tag)
			{
			case TAG_HOLDER:
			{
				HoldItemObject* h=(HoldItemObject*) o;
				
				if (h->isDead==true)
				{

					it = objects.erase(it);
					Item* testitem = new Item(h->item);
					testitem->SetPosition(h->x, h->y);
					
					objects.push_back(testitem);
					
					delete h;
					continue;
				}
				else
				{
					h->Update(dt, &objects);
				}
				break;
			}
			case TAG_ITEM:
			{
				Item*i = (Item*) o;
				if (i->isDead)
				{
					it = objects.erase(it);
					delete i;
					continue;
				}
				else
				{
					i->Update(dt, &objects);
				}
				break; 
			}
			default:
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
	if (!simon->check_auto_move)
	{
		keyCode[key] = true;
		simon->OnKeyDown(key);
	}
}

void PlayScene::OnKeyUp(int key)
{
	if (!simon->check_auto_move)
	{
		keyCode[key] = false;
		simon->OnKeyUp(key);
	}

}

