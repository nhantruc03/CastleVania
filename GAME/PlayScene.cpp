#include "PlayScene.h"
#include"HoldItemObject.h"
#include"Item.h"
#include<fstream>
#include"Maps.h"
#include"invisibleObject.h"
#include"Ghost.h"
#include"Panther.h"
#include"Door.h"
#include"Bat.h"
#include"Fishman.h"
#include"Special_brick.h"
PlayScene::PlayScene(int level)
{
	LoadResources();
	srand(time(NULL));
	keyCode.clear();
	isgoingthroughdoor = false;
	this->level = level;
	map = Maps::GetInstance()->GetMap(this->level);
	simon = CSimon::GetInstance();
	simon->SetPosition(100, 250.0f);//287.0f);
	simon->Respawn();
	camera = Camera::GetInstance();
	objects.clear();
	objects = map->get_objectlist();


	timetocreateghost = 0;
	cancreateghost = true;
	countghost = 0;

	cancreatepanther = true;
	countpanther = 0;
	outofareacreatepanther = true;

	timetocreatebat = 0;
	cancreatebat = true;
	countbat = 0;

	timetocreatefishman = 0;
	cancreatefishman = true;
	countfishman = 0;

	switch (level)
	{
	case 1:
		for (int i = 0; i < objects.size(); i++)
		{
			if (objects[i]->tag == TAG_INVISIBLE_OBJECT && objects[i]->type == 0)
			{
				endrect = objects[i]->GetBoundingBox();
			}
		}
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
	if (simon->upgrade_time || simon->timeusingholycross)
	{
		if (simon->upgrade_time)
		{
			simon->upgrade_time -= dt;
		}
		else if(simon->timeusingholycross)
		{
			simon->timeusingholycross -= dt;
			if (simon->timeusingholycross <= TIME_USING_HOLY_CROSS/2)
			{
				for (int i = 0; i < objects.size(); i++)
				{
					if (objects[i]->tag == TAG_ENEMY)
					{
						objects[i]->isDead = true;
					}
				}
			}
		}
	}
	else if(!simon->upgrade_time && !simon->timeusingholycross)
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
				//simon->vx = 0;
				simon->check_auto_move = true;
				if (simon->x >= endrect.right && !simon->jumping)
				{

					gotoleft = true;
				}
				if (simon->x <= endrect.left && !simon->jumping)
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
			}
			// di xuong ham
			for (int i = 0; i < objects.size(); i++)
			{
				if (simon->IsContain(objects[i]->GetBoundingBox().left, objects[i]->GetBoundingBox().top, objects[i]->GetBoundingBox().right, objects[i]->GetBoundingBox().bottom))
				{
					if (dynamic_cast<invisibleObject*>(objects[i]))
					{
						switch (objects[i]->type)
						{
						case TYPE_INVI_O_GO_DOWN_BASEMENT:
							if (simon->State==STATE_WALK_ONSTAIR_DOWN && simon->y>objects[i]->y)
							{
								camera->movedownstair = true;
								camera->SetPosition(simon->x, -384);

								simon->prevX = simon->prevX+16;
								simon->prevY = simon->prevY + 80;

								simon->SetPosition(simon->x, simon->y+64);
							}
							break;
						case TYPE_INVI_O_GO_UP_BASEMENT:
							if (simon->State==STATE_WALK_ONSTAIR_UP && simon->y<objects[i]->y)
							{
								camera->inzone2 = true;
								camera->movedownstair = false;
								camera->SetPosition(simon->x, 0);
								simon->prevX = simon->prevX - 16;
								simon->prevY = simon->prevY - 80;
								simon->SetPosition(simon->x, simon->y - 64);
							}
							break;
						default:
							break;
						}
					}
				}
				
			}
			//if ((simon->IsContain(downstair.left, downstair.top, downstair.right, downstair.bottom) || simon->IsContain(downstair2.left, downstair2.top, downstair2.right, downstair2.bottom)) && (simon->y > downstair.top || simon->y > downstair2.top) && simon->State == STATE_WALK_ONSTAIR_DOWN)
			//{
			//	camera->movedownstair = true;
			//	camera->SetPosition(simon->x, -384);
			//	simon->prevX = simon->x;
			//	simon->prevY = simon->y + 64;
			//	simon->SetPosition(simon->x, simon->y + 64);
			//}
			//// di len ham
			//else if ((simon->IsContain(upstair.left, upstair.top, upstair.right, upstair.bottom) || simon->IsContain(upstair2.left, upstair2.top, upstair2.right, upstair2.bottom)) && (simon->y < upstair.bottom || simon->y < upstair2.bottom) && simon->State == STATE_WALK_ONSTAIR_UP)
			//{
			//	if (simon->IsContain(upstair.left, upstair.top, upstair.right, upstair.bottom))
			//	{
			//		camera->inzone2 = true;
			//	}
			//	camera->movedownstair = false;
			//	camera->SetPosition(simon->x, 0);
			//	simon->prevX = simon->x;
			//	simon->prevY = simon->y - 64;
			//	simon->SetPosition(simon->x, simon->y - 64);
			//}

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
							Ghost* ghost = new Ghost(camera->GetPosition().x + camera->camWidht / 2, 287.0f, -1);
							objects.push_back(ghost);
						}
						else
						{
							Ghost* ghost = new Ghost(camera->GetPosition().x - camera->camWidht / 2, 287.0f, 1);
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
			if (1216 < simon->x && simon->x < 2240)
			{
				if (cancreatepanther && !outofareacreatepanther)
				{
					outofareacreatepanther = true;
					if (countpanther == 0)
					{
						int direction = abs(1106 - simon->x) < abs(2240 - simon->x) ? -1 : 1; // panther xoay mat vao simon
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

			// tao enemy bat
			if (!isgoingthroughdoor)
			{
				if (timetocreatebat > 0)
				{
					timetocreatebat -= dt;
				}
				if (simon->x >= 3072 && simon->y<352)
				{
					if (cancreatebat)
					{
						if (timetocreatebat <= 0)
						{
							if (simon->y < 160)
							{
								Bat* bat = new Bat(camera->GetPosition().x + camera->camWidht / 2, 112.0f, -1);
								objects.push_back(bat);
							}
							else
							{
								int random = rand() % 3;
								if (random == 0)
								{
									Bat* bat = new Bat(camera->GetPosition().x + camera->camWidht / 2, 208.0f, -1);
									objects.push_back(bat);
								}
								else if (random == 1)
								{
									Bat* bat = new Bat(camera->GetPosition().x + camera->camWidht / 2, 304.0f, -1);
									objects.push_back(bat);
								}
								else if (random == 2)
								{
									Bat* bat = new Bat(camera->GetPosition().x - camera->camWidht / 2, 304.0f, 1);
									objects.push_back(bat);
								}

							}
							countbat++;
							timetocreatebat = 3000;
							if (countbat == 2)
							{
								cancreatebat = false;
							}
						}
					}
				}
			}

			// tao enemy fishman
			if (timetocreatefishman > 0)
			{
				timetocreatefishman -= dt;
			}
			if (camera->movedownstair)
			{
				if (cancreatefishman)
				{
					if (timetocreatefishman <= 0)
					{
						if (simon->x > 3360.0f && simon->x<3520)
						{
							if (countfishman < 2)
							{
								Fishman* fishman = new Fishman(3264, 672, 1);
								objects.push_back(fishman);
								countfishman++;
							}
							if (countfishman < 2)
							{
								Fishman* fishman = new Fishman(3520, 672, -1);
								objects.push_back(fishman);
								countfishman++;
							}							
						}
						if (simon->vx <= 0 && simon->x < 3264 && simon->x > 3072)
						{
							if (countfishman < 2)
							{
								Fishman* fishman = new Fishman(3136, 672, 1);
								objects.push_back(fishman);
								countfishman++;
							}
							if (countfishman < 2)
							{
								Fishman* fishman = new Fishman(3392, 672, -1);
								objects.push_back(fishman);
								countfishman++;
							}							
						}
						if (simon->x > 3520 && simon->x < 3712)
						{
							if (countfishman < 2)
							{
								Fishman* fishman = new Fishman(3520, 672, 1);
								objects.push_back(fishman);
								countfishman++;
							}
							if (countfishman < 2)
							{
								Fishman* fishman = new Fishman(3648, 672, 1);
								objects.push_back(fishman);
								countfishman++;
							}
						}
						if (simon->x > 3712)
						{
							if (countfishman < 2)
							{
								Fishman* fishman = new Fishman(3776, 672, 1);
								objects.push_back(fishman);
								countfishman++;
							}
							if (countfishman < 2)
							{
								Fishman* fishman = new Fishman(3904, 672, 1);
								objects.push_back(fishman);
								countfishman++;
							}
						}
						timetocreatefishman = 3000;
					}
				}

			}
			// di qua cua 1
			if (door1 == NULL)
			{
				for (int i = 0; i < objects.size(); i++)
				{
					if (dynamic_cast<Door*>(objects[i])&& dynamic_cast<Door*>(objects[i])->type==0)
					{
						door1 = (Door*)objects[i];
					}
				}
			}
			if (simon->IsContain(door1->GetBoundingBox().left, door1->GetBoundingBox().top, door1->GetBoundingBox().right, door1->GetBoundingBox().bottom) && door1->isclosed())
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
					simon->gotoright = true;
				}
				if (simon->gotoright)
				{
					simon->ChangeState(STATE_WALKING);
					simon->isReverse = true;
					simon->vx = 0.05f;
					if (simon->x - door1->x >= 64)
					{
						simon->ChangeState(STATE_STANDING);
						simon->gotoright = false;
						door1->close();
					}
				}
				if (door1->isclosed() && simon->check_auto_move == true)
				{
					camera->SetPosition(camera->camPosition.x += 2, camera->camPosition.y);
					if (camera->camPosition.x - camera->camWidht / 2 >= 3072)
					{
						camera->inzone2 = true;
						simon->check_auto_move = false;
						isgoingthroughdoor = false;
					}
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
			switch (o->tag)
			{
			case TAG_HOLDER:
			{
				HoldItemObject* h=(HoldItemObject*) o;
				
				if (h->isDead==true)
				{

					it = objects.erase(it);
					Item* item = new Item(h->item);
					item->SetPosition(h->x, h->y);
					
					objects.push_back(item);
					
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
							timetocreateghost = 3000;
							cancreateghost = true;
						}
					}
					if (e->type == TYPE_ENEMY_PANTHER)
					{
						countpanther--;
						if (countpanther == 0)
						{
							cancreatepanther = true;
						}
					}
					if (e->type == TYPE_ENEMY_BAT)
					{
						countbat--;
						if (countbat == 0)
						{
							timetocreatebat = 1000;
							cancreatebat = true;
						}
					}
					if (e->type == TYPE_ENEMY_FISHMAN)
					{
						countfishman--;
						if (countfishman == 0)
						{
							timetocreatefishman = 3000;
						}
					}

					delete e;
					continue;
				}
				else
				{
					e->Update(dt, &objects);
				}
				break;
			}
			case TAG_DOOR:
			{
				o->Update(dt,&objects);
				break;
			}
			case TAG_SPECIAL_BRICK:
			{
				Special_brick* sb = (Special_brick*)o;
				if (sb->isDead)
				{
					it = objects.erase(it);
					if (sb->item != -1)
					{
						Item* item = new Item(sb->item);
						item->SetPosition(sb->x, sb->y-5);

						objects.push_back(item);
					}
					

					delete sb;
					continue;
				}
				else
				{
					sb->Update(dt, &objects);
				}
				break;
			}
			default:
				break;
			}
		++it;
	}
}

void PlayScene::LoadResources()
{
	CTextures::GetInstance()->LoadResources();
	Sprites::GetInstance()->LoadResources();
	Animations::GetInstance()->LoadResources();
	Maps::GetInstance()->LoadResources();
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

