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
#include"Enemy_bullet.h"
#include"Special_brick.h"
#include"steam.h"
PlayScene::PlayScene(int level)
{
	grid = new Grid(level);
	LoadResources(level);

	srand(time(NULL));

	keyCode.clear();
	isgoingthroughdoor = false;
	isgoingthroughdoor2 = false;
	isgoingthroughendrect = false;
	this->level = level;

	map = Maps::GetInstance()->GetMap(this->level);

	simon = CSimon::GetInstance();
	simon->SetPosition(3000, 5);//287.0f);
	simon->Respawn();

	camera = Camera::GetInstance();

	/*camera->inzone1 = false;
	camera->inzone2 = true;*/
	objects.clear();

	timetocreateghost = 0;
	cancreateghost = true;
	countghost = 0;

	cancreatepanther = false;
	countpanther = 0;
	outofareacreatepanther = true;

	timetocreatebat = 0;
	cancreatebat = true;
	countbat = 0;

	timetocreatefishman = 0;
	cancreatefishman = true;
	countfishman = 0;

	gotoleft = false;
	gotoright = false;
}


PlayScene::~PlayScene()
{

}

void PlayScene::Update(DWORD dt)
{
	if (simon->upgrade_time>0)
	{
		simon->upgrade_time -= dt;
	}
	else if(simon->upgrade_time<=0)
	{
		if (simon->usingholycross || isgoingthroughdoor)
		{
			listenemy.clear();
			countghost = 0;
			countpanther = 0;
			countfishman = 0;
			countbat = 0;
			cancreatebat = true;
			cancreateghost = true;
			cancreatefishman = true;
			cancreatepanther = true;
		//	simon->usingholycross = false;
		}
		for (Enemy* e : listenemy)
		{
			objects.push_back(e);
		}
		for (Enemy*e : listenemy_tronggrid)
		{
				objects.push_back(e);
		}
		UpdatePlayer(dt);
		if (!isgoingthroughdoor && !isgoingthroughdoor2)
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
			if (endrectmap1 == NULL)
			{
				for (int i = 0; i < objects.size(); i++)
				{
					if (objects[i]->tag == TAG_INVISIBLE_OBJECT && objects[i]->type == TYPE_INVI_O_ENDRECT_MAP1)
					{
						endrectmap1 = (invisibleObject*)objects[i];
					}
				}
			}
			else
			{
				if (simon->IsContain(endrectmap1->GetBoundingBox().left, endrectmap1->GetBoundingBox().top, endrectmap1->GetBoundingBox().right, endrectmap1->GetBoundingBox().bottom))
				{
					isgoingthroughendrect = true;
					simon->check_auto_move = true;
					if (simon->x >= endrectmap1->GetBoundingBox().right && !simon->jumping)
					{

						simon->gotoleft = true;
					}
					if (simon->x <= endrectmap1->GetBoundingBox().left && !simon->jumping)
					{
						simon->gotoright = true;
						simon->gotoleft = false;
					}
				}
				if (isgoingthroughendrect)
				{
					if (simon->gotoleft)
					{
						simon->ChangeState(STATE_WALKING);
						simon->isReverse = false;
						simon->vx = -0.05f;
					}
					if (simon->gotoright)
					{
						simon->ChangeState(STATE_WALKING);
						simon->isReverse = true;
						simon->vx = 0.05f;
						if (simon->x >= endrectmap1->GetBoundingBox().right)
						{
							simon->check_auto_move = false;
							level += 1;
							simon->gotoleft = simon->gotoright = false;
							delete endrectmap1;
							SceneManager::GetInstance()->ReplaceScene(new PlayScene(level));
						}
					}
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
							if (simon->State == STATE_WALK_ONSTAIR_DOWN && simon->y > objects[i]->y)
							{
								camera->movedownstair = true;
								camera->SetPosition(simon->x, -384);

								simon->prevX = simon->prevX;
								simon->prevY = simon->prevY + 64;

								simon->SetPosition(simon->x, simon->y + 64);
							}
							break;
						case TYPE_INVI_O_GO_UP_BASEMENT:
							if (simon->State == STATE_WALK_ONSTAIR_UP && simon->y < objects[i]->y)
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

			if (simon->timeusingstopwatch <= 0)
			{
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
								listenemy.push_back(ghost);
							}
							else
							{
								Ghost* ghost = new Ghost(camera->GetPosition().x - camera->camWidht / 2, 287.0f, 1);
								listenemy.push_back(ghost);
							}
							countghost++;
							timetocreateghost = 600;
							if (countghost == 3)
							{
								cancreateghost = false;
							}
						}
					}

				}
				if (!isgoingthroughdoor2)
				{
					if (timetocreateghost > 0)
					{
						timetocreateghost -= dt;
					}
					if ((simon->x >= 4096.0f&& simon->x <= 5088.0f))
					{
						if (cancreateghost)
						{
							if (timetocreateghost <= 0)
							{
								if (simon->x < 4480)
								{
									int random = rand() % 2;
									if (random == 0)
									{
										Ghost* ghost = new Ghost(camera->GetPosition().x + camera->camWidht / 2, 150, -1);
										listenemy.push_back(ghost);
									}
									else
									{
										if (simon->vx > 0)
										{
											Ghost* ghost = new Ghost(camera->GetPosition().x + camera->camWidht / 2, 287.0f, -1);
											listenemy.push_back(ghost);
										}
										else
										{
											Ghost* ghost = new Ghost(camera->GetPosition().x - camera->camWidht / 2, 287.0f, 1);
											listenemy.push_back(ghost);
										}
									}
								}
								else
								{
									if (simon->vx > 0)
									{
										Ghost* ghost = new Ghost(camera->GetPosition().x + camera->camWidht / 2, 287.0f, -1);
										listenemy.push_back(ghost);
									}
									else
									{
										Ghost* ghost = new Ghost(camera->GetPosition().x - camera->camWidht / 2, 287.0f, 1);
										listenemy.push_back(ghost);
									}
								}
								countghost++;
								timetocreateghost = 600;
								if (countghost == 3)
								{
									cancreateghost = false;
								}
							}
						}

					}
				}

				// tao enemy panther
				//if (1216 < simon->x && simon->x < 2240)
				//{
				//	if (cancreatepanther && !outofareacreatepanther)
				//	{
				//		outofareacreatepanther = true;
				//		if (countpanther == 0)
				//		{
				//			int direction = abs(1106 - simon->x) < abs(2240 - simon->x) ? -1 : 1; // panther xoay mat vao simon
				//			//listenemy.push_back(new Panther(1444.0f, 175.0f, direction));
				//			//listenemy.push_back(new Panther(1792.0f, 110.0f, direction));
				//			//listenemy.push_back(new Panther(1920.0f, 175.0f, direction));
				//		//	grid->insert(new Panther(1444.0f, 175.0f, direction));
				//			//grid->insert(new Panther(1792.0f, 110.0f, direction));
				//		//	grid->insert(new Panther(1920.0f, 175.0f, direction));
				//			countpanther += 3;
				//		}
				//		cancreatepanther = false;
				//	}
				//}
				//else
				//{
				//	if (countpanther == 0)
				//	{
				//		outofareacreatepanther = false;
				//	}
				//}
				/*vector<Enemy*>listenemy_tronggrid;
				listenemy_tronggrid.clear();
				grid->GetListPanther(listenemy_tronggrid);
				if (listenemy_tronggrid.begin()!=listenemy_tronggrid.end() && test==false)
				{
					for (CGameObject* e : listenemy_tronggrid)
					{
						listenemy.push_back((Enemy*)e);
						test = true;
					}
				}*/
				if (1216 < simon->x && simon->x < 2240)
				{
					if (cancreatepanther)
					{
						cancreatepanther = false;
						grid->respawnpanther();
					}
				}
				else
				{
					if (grid->countpanther == 0)
					{
						cancreatepanther = true;
					}
				}


				// tao enemy bat
				if (!isgoingthroughdoor && !isgoingthroughdoor2)
				{
					if (timetocreatebat > 0)
					{
						timetocreatebat -= dt;
					}
					if (simon->x >= 3072 && simon->y < 352 && simon->x <= 4111 && !(simon->x>3900&&simon->y<128))
					{
						if (cancreatebat)
						{
							if (timetocreatebat <= 0)
							{
								if (simon->y < 160)
								{
									Bat* bat = new Bat(camera->GetPosition().x + camera->camWidht / 2, 112.0f, -1);
									listenemy.push_back(bat);
								}
								else
								{
									int random = rand() % 3;
									if (random == 0)
									{
										Bat* bat = new Bat(camera->GetPosition().x + camera->camWidht / 2, 208.0f, -1);
										listenemy.push_back(bat);
									}
									else if (random == 1)
									{
										Bat* bat = new Bat(camera->GetPosition().x + camera->camWidht / 2, 304.0f, -1);
										listenemy.push_back(bat);
									}
									else if (random == 2)
									{
										Bat* bat = new Bat(camera->GetPosition().x - camera->camWidht / 2, 304.0f, 1);
										listenemy.push_back(bat);
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
							if (simon->x > 3360.0f && simon->x < 3520)
							{
								if (countfishman < 2)
								{
									Fishman* fishman = new Fishman(3264, 672, 1);
									listenemy.push_back(fishman);
									countfishman++;
									createeffectsteam(fishman->x, fishman->y);

								}
								if (countfishman < 2)
								{
									Fishman* fishman = new Fishman(3520, 672, -1);
									listenemy.push_back(fishman);
									countfishman++;
									createeffectsteam(fishman->x, fishman->y);
								}
								timetocreatefishman = 3000;
							}
							if (simon->vx <= 0 && simon->x < 3264 && simon->x > 3072)
							{
								if (countfishman < 2)
								{
									Fishman* fishman = new Fishman(3136, 672, 1);
									listenemy.push_back(fishman);
									countfishman++;
									createeffectsteam(fishman->x, fishman->y);

								}
								if (countfishman < 2)
								{
									Fishman* fishman = new Fishman(3392, 672, -1);
									listenemy.push_back(fishman);
									countfishman++;
									createeffectsteam(fishman->x, fishman->y);
								}
								timetocreatefishman = 3000;
							}
							if (simon->x > 3520 && simon->x < 3712)
							{
								if (countfishman < 2)
								{
									Fishman* fishman = new Fishman(3520, 672, 1);
									listenemy.push_back(fishman);
									countfishman++;
									createeffectsteam(fishman->x, fishman->y);
								}

								if (countfishman < 2)
								{
									Fishman* fishman = new Fishman(3648, 672, simon->x < 3648 ? -1 : 1);
									listenemy.push_back(fishman);
									countfishman++;
									createeffectsteam(fishman->x, fishman->y);
								}
								timetocreatefishman = 3000;
							}
							if (simon->x > 3712)
							{
								if (countfishman < 2)
								{
									Fishman* fishman = new Fishman(3776, 672, simon->x < 3776 ? -1 : 1);
									listenemy.push_back(fishman);
									countfishman++;
									createeffectsteam(fishman->x, fishman->y);
								}
								if (countfishman < 2)
								{
									Fishman* fishman = new Fishman(3904, 672, simon->x < 3904 ? -1 : 1);
									listenemy.push_back(fishman);
									countfishman++;
									createeffectsteam(fishman->x, fishman->y);
								}
								timetocreatefishman = 3000;
							}

						}
					}

				}
			}
			// di qua cua 1
			if (camera->inzone1)
			{
				if (door1 == NULL)
				{
					for (int i = 0; i < objects.size(); i++)
					{
						if (dynamic_cast<Door*>(objects[i]) && dynamic_cast<Door*>(objects[i])->type == 0)
						{
							door1 = (Door*)objects[i];
						}
					}
				}
			}
			if (door1 != NULL)
			{
				if (simon->IsContain(door1->GetBoundingBox().left, door1->GetBoundingBox().top, door1->GetBoundingBox().right, door1->GetBoundingBox().bottom) && door1->isclosed())
				{
					keyCode.clear();
					isgoingthroughdoor = true;
					simon->vx = 0;
					camera->inzone1 = false;

					simon->check_auto_move = true;
					if (camera->camPosition.x >= simon->x)
					{
						camera->camPosition.x = simon->x;

						door1->open();
					}

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

			if (camera->inzone2)
			{
				if (door2 == NULL)
				{
					for (int i = 0; i < objects.size(); i++)
					{
						if (dynamic_cast<Door*>(objects[i]) && dynamic_cast<Door*>(objects[i])->type == 1)
						{
							door2 = (Door*)objects[i];
						}
					}
				}
			}
			if (door2 != NULL)
			{
				if (simon->IsContain(door2->GetBoundingBox().left, door2->GetBoundingBox().top, door2->GetBoundingBox().right, door2->GetBoundingBox().bottom) && door2->isclosed())
				{
					keyCode.clear();
					isgoingthroughdoor2 = true;
					simon->vx = 0;
					camera->inzone2 = false;

					simon->check_auto_move = true;
					if (camera->camPosition.x >= simon->x)
					{
						camera->camPosition.x = simon->x;

						door2->open();
					}

				}
				if (isgoingthroughdoor2)
				{
					if (door2->isopened())
					{
						simon->gotoright = true;
					}
					if (simon->gotoright)
					{
						simon->ChangeState(STATE_WALKING);
						simon->isReverse = true;
						simon->vx = 0.05f;
						if (simon->x - door2->x >= 64)
						{
							simon->ChangeState(STATE_STANDING);
							simon->gotoright = false;
							door2->close();
						}
					}
					if (door2->isclosed() && simon->check_auto_move == true)
					{
						camera->SetPosition(camera->camPosition.x += 2, camera->camPosition.y);
						if (camera->camPosition.x - camera->camWidht / 2 >= 4096)
						{
							camera->inzone3 = true;
							simon->check_auto_move = false;
							isgoingthroughdoor2 = false;
						}
					}
				}
			}
		}

		
		
	}

}

void PlayScene::createeffectsteam(float x, float y)
{
	listeffect.push_back(new steam(x, y, 1));
	listeffect.push_back(new steam(x, y, 2));
	listeffect.push_back(new steam(x, y, 3));
}

void PlayScene::UpdatePlayer(DWORD dt)
{
	simon->Update(dt,&objects);
}

void PlayScene::UpdateObjects(DWORD dt)
{
	grid->GetListObject(objects);

	for (CGameObject* o : objects)
	{
		o->Update(dt, &objects);
	}

	for (int i = 0; i < listenemy.size(); i++)
	{
		Enemy* e = listenemy[i];
		if (e->isDead)
		{
			listenemy.erase(listenemy.begin()+i);
			if (e->type == TYPE_ENEMY_GHOST)
			{
				countghost--;
				if (countghost == 0)
				{
					timetocreateghost = 3000;
					cancreateghost = true;
				}
			}
			/*if (e->type == TYPE_ENEMY_PANTHER)
			{
				countpanther--;
				if (countpanther == 0)
				{
					cancreatepanther = true;
				}
			}*/
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
			/*if (e->type == TYPE_ENEMY_PANTHER)
			{
				if (camera->IsContain(e->GetBoundingBox()))
				{
					e->Update(dt, &objects);
					grid->movepanther((Panther*)e, e->x, e->y);
				}
			}*/
			if (e->type == TYPE_ENEMY_FISHMAN && dynamic_cast<Fishman*>(e)->attacking == true && dynamic_cast<Fishman*>(e)->canspawnbullet == true)
			{

				dynamic_cast<Fishman*>(e)->canspawnbullet = false;
				Enemy_bullet * bullet = new Enemy_bullet(e->x, e->y - 20, e->direct);
				listenemy.push_back(bullet);
			}
			else
				e->Update(dt, &objects);
		}
	}
	grid->GetListPanther(listenemy_tronggrid);
	for (Enemy* e : listenemy_tronggrid)
	{
		e->Update(dt, &objects);
		grid->movepanther(e,e->x,e->y);
	}

	for (int i = 0; i < listeffect.size(); i++)
	{
		if (listeffect[i]->isDead)
		{
			listeffect.erase(listeffect.begin() + i);
		}
	}

	for (Effect* e: listeffect)
	{
		e->Update(dt);
	}
}

void PlayScene::LoadResources(int level)
{
	CTextures::GetInstance()->LoadResources(level);
	Sprites::GetInstance()->LoadResources(level);
	Animations::GetInstance()->LoadResources(level);
	Maps::GetInstance()->LoadResources();
	grid->Loadresources();
}

void PlayScene::Render()
{
	map->Render();
	for (CGameObject* o : objects)
	{
		o->Render();

	}
	for (Enemy* e : listenemy)
	{
		e->Render();
	}
	for (Enemy*e : listenemy_tronggrid)
	{
		e->Render();
	}
	for (Effect*e : listeffect)
	{
		e->Render();
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

