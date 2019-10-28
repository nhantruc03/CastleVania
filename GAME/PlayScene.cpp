#include "PlayScene.h"
#include"HoldItemObject.h"
#include"Item.h"
#include<fstream>
#include"Maps.h"
#include"invisibleObject.h"
#include"Ghost.h"
#include"Panther.h"
#include"Door.h"
PlayScene::PlayScene(int level)
{
	keyCode.clear();
	isgoingthroughdoor = false;
	this->level = level;
	map = Maps::GetInstance()->GetMap(this->level);
	simon = CSimon::GetInstance();
	simon->SetPosition(1000, 250.0f);//287.0f);
	simon->Respawn();
	camera = Camera::GetInstance();
	objects.clear();
	objects = map->get_BricksList();
	timetocreateghost = 0;
	cancreateghost = true;
	countghost = 0;

	cancreatepanther = true;
	countpanther = 0;
	outofareacreatepanther = true;

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

		door1 = new Door(0);
		door1->SetPosition(3088, 80);
		objects.push_back(door1);
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
		if (!isgoingthroughdoor)
		{
			camera->SetPosition(simon->x, camera->GetPosition().y);
		}
		camera->Update(level);
		UpdateObjects(dt);
		if (level == 1)
		{
			// gioi han 2 bien cua map 1
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
			// gioi han bien trai cua map 2
			if (simon->vx < 0 && simon->x < 16) simon->x = 16;

			if (camera->movedownstair)
			{
				// gioi han 2 bien duoi ham
				if (simon->vx < 0 && simon->x < 3088) simon->x = 3088;
				if (simon->vx > 0 && simon->x > 4080) simon->x = 4080;
			}
			// di xuong ham
			if ((simon->IsContain(downstair.left, downstair.top, downstair.right, downstair.bottom) || simon->IsContain(downstair2.left, downstair2.top, downstair2.right, downstair2.bottom)) && (simon->y > downstair.top || simon->y > downstair2.top) && simon->State == STATE_WALK_ONSTAIR_DOWN)
			{
				camera->movedownstair = true;
				camera->SetPosition(simon->x, -384);
				simon->prevX = simon->x;
				simon->prevY = simon->y + 64;
				simon->SetPosition(simon->x, simon->y + 64);
			}
			// di len ham
			else if ((simon->IsContain(upstair.left, upstair.top, upstair.right, upstair.bottom) || simon->IsContain(upstair2.left, upstair2.top, upstair2.right, upstair2.bottom)) && (simon->y < upstair.bottom || simon->y < upstair2.bottom) && simon->State == STATE_WALK_ONSTAIR_UP)
			{
				if (simon->IsContain(upstair.left, upstair.top, upstair.right, upstair.bottom))
				{
					camera->inzone2 = true;
				}
				camera->movedownstair = false;
				camera->SetPosition(simon->x, 0);
				simon->prevX = simon->x;
				simon->prevY = simon->y - 64;
				simon->SetPosition(simon->x, simon->y - 64);
			}
		}

		// tao enemy ghost
		if (timetocreateghost > 0)
		{
			timetocreateghost -= dt;
		}
		if ((simon->x >= 0.0f&& simon->x <= 832.0f) || (simon->x > 2208 && simon->x < 2784))
		{
			if (cancreateghost)
			{
				if (timetocreateghost <= 0)
				{
					if (simon->vx >= 0)
					{
						Ghost* ghost = new Ghost(camera->GetPosition().x + camera->camWidht / 2 , 287.0f, -1);
						objects.push_back(ghost);
					}
					else
					{
						Ghost* ghost = new Ghost(camera->GetPosition().x - camera->camWidht / 2 , 287.0f, 1);
						objects.push_back(ghost);
					}
					countghost++;
					timetocreateghost = 500;
					if (countghost == 3)
					{
						cancreateghost = false;
					}
				}
			}

		}

		// tao enemy panther
		if (1216 < simon->x && simon->x< 2240)
		{
			if (cancreatepanther && !outofareacreatepanther)
			{
				outofareacreatepanther = true;
				if (countpanther == 0) 
				{
					int direction = abs(1106 - simon->x) < abs(2240- simon->x) ? -1 : 1; // panther xoay mat vao simon
					objects.push_back(new Panther(1444.0f, 175.0f, direction, direction == -1 ? 50.0f : 20.0f));
					objects.push_back(new Panther(1792.0f, 110.0f, direction, direction == -1 ? 278.0f : 240.0f));
					objects.push_back(new Panther(1920.0f, 175.0f, direction, direction == -1 ? 50.0f : 120.0f));
					countpanther += 3;
				}
				cancreatepanther = false;
			}
		}
		else
		{
			if (countpanther == 0)
			{
				outofareacreatepanther = false;
			}
		}
		
		// di qua cua 1
		RECT tempdoor = door1->GetBoundingBox();
		if (simon->IsContain(tempdoor.left, tempdoor.top, tempdoor.right, tempdoor.bottom)  && door1->isclosed() )
		{
			keyCode.clear();
			isgoingthroughdoor = true;
			simon->vx = 0;
			door1->open();
			simon->check_auto_move = true;
		}
		if (isgoingthroughdoor)
		{
			if (door1->isopened())
			{
				gotoright = true;
			}
			if (gotoright)
			{
				simon->ChangeState(STATE_WALKING);
				simon->isReverse = true;
				simon->vx = 0.05f;
				if (simon->x - door1->x >= 64)
				{
					simon->ChangeState(STATE_STANDING);
					gotoright = false;
					door1->close();
				}
			}
			if (door1->isclosed() && simon->check_auto_move == true)
			{
				camera->SetPosition(camera->camPosition.x += 2, camera->camPosition.y);
				if (camera->camPosition.x - camera->camWidht / 2 >= 3088)
				{
					camera->inzone2 = true;
					simon->check_auto_move = false;
					isgoingthroughdoor = false;
				}
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
		/*if (camera->IsContain(temp))
		{*/
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
			case TAG_ENEMY:
			{
				Enemy* e = (Enemy*)o;
				if (e->isDead)
				{
					it = objects.erase(it);
					if (e->type == TYPE_ENEMY_GHOST)
					{
						countghost--;
						if (countghost == 0)
						{
							timetocreateghost = 2500;
							cancreateghost = true;
						}
					}
					if (e->type == 1)
					{
						countpanther--;
						if (countpanther == 0)
						{
							cancreatepanther = true;
						}
					}

					delete e;
					continue;
				}
				else
				{
					e->Update(dt, &objects);
				}
			}
			case 9:
			{
				o->Update(dt,&objects);
			}
			default:
				break;
			}
		/*}*/
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

