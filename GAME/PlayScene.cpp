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
	simon->SetPosition(1200.0f, 255.0f);
	simon->Respawn();
	camera = Camera::GetInstance();
	objects.clear();
	objects = map->get_BricksList();
	if (level == 2)
	{
		invisibleObject* lencauthang_LTR = new invisibleObject();
		lencauthang_LTR->type = 1;
		lencauthang_LTR->SetPosition(1248, 310);
		objects.push_back(lencauthang_LTR);

		invisibleObject* xuongcauthang_RTL = new invisibleObject();
		xuongcauthang_RTL->type = 2;
		xuongcauthang_RTL->SetPosition(1312+32*2, 121);
		objects.push_back(xuongcauthang_RTL);
	}
	switch (level)
	{
	case 1:
		endrect.left = 1376;
		endrect.right = 1408;
		endrect.top = 286;
		endrect.bottom = 288;
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
		camera->SetPosition(simon->x, 0);
		camera->Update(level);
		UpdateObjects(dt);
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

