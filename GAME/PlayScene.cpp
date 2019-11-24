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
#include"Phantom_bat.h"
PlayScene::PlayScene(int level)
{
	grid = new Grid(level);

	LoadResources(level);

	checkBossDead = false;
	timetospawnCrystal = 0;
	srand(time(NULL));

	keyCode.clear();

	isgoingthroughdoor = false;
	isgoingthroughdoor2 = false;
	isgoingthroughendrect = false;

	this->level = level;

	map = Maps::GetInstance()->GetMap(this->level);

	simon = CSimon::GetInstance();
	simon->Respawn();

	camera = Camera::GetInstance();

	objects.clear();

	timetocreateghost = 0;
	cancreateghost = true;
	countghost = 0;

	cancreatepanther = false;
	countpanther = 0;

	timetocreatebat = 0;
	cancreatebat = true;
	countbat = 0;

	timetocreatefishman = 0;
	cancreatefishman = true;
	countfishman = 0;

	//door1=door2=NULL;


	board = new Board();
}


PlayScene::~PlayScene()
{

}

void PlayScene::Update(DWORD dt)
{
	board->update(boss,dt);
	if (simon->upgrade_time>0)
	{
		simon->upgrade_time -= dt;
	}
	else if(simon->upgrade_time<=0)
	{
		// xu ly khi het thoi gian 
		if (!SIMON->checkkillboss)
		{
			if (globle_time > 0)
			{
				globle_time -= dt;
			}
			if (globle_time <= 0 && !simon->isDead)
			{
				simon->ChangeState(STATE_DEAD);
			}
		}

		// xu ly giet tat ca enemy con song
		if (simon->usingholycross || isgoingthroughdoor)
		{
			for (int i = 0; i < listenemy.size(); i++)
			{
				if (listenemy[i]->type != TYPE_ENEMY_BOSS_1)
				{
					listenemy[i]->isDead = true;
				}
			}

			for (int i = 0; i < listenemy_tronggrid.size(); i++)
			{
				listenemy_tronggrid[i]->isDead = true;
			}
		}

		// xu ly hoi sinh SIMON
		if (simon->isDead && simon->timetorespawn<=0 && simon->lives>=1)
		{
			for (int i = 0; i < listenemy.size(); i++)
			{
				if (listenemy[i]->type != TYPE_ENEMY_BOSS_1) // neu xet BOSS.isdead=true thi se spawn crystal
				{
					listenemy[i]->isDead = true;
				}
				else
				{
					listenemy.erase(listenemy.begin() + i); // xoa boss hien tai khoi list enemy
				}
			}
			for (int i = 0; i < listenemy_tronggrid.size(); i++)
			{
				listenemy_tronggrid[i]->isDead = true;
			}
			grid->Loadresources();
			door1 = door2 = NULL;
			boss = NULL;
			simon->Respawn();
		}

		// them cac objects sinh ra o playscene vao list objects chinh de update SIMON ,...
		for (Enemy* e : listenemy)
		{
			objects.push_back(e);
		}
		for (Weapon*w : list_enemy_weapon)
		{
			objects.push_back(w);
		}
		for (Enemy*e : listenemy_tronggrid)
		{
			objects.push_back(e);
		}

		UpdatePlayer(dt);

		// Khi di qua cua thi camera khong tu dong di theo SIMON nua
		if (!isgoingthroughdoor && !isgoingthroughdoor2)
		{
			camera->SetPosition(simon->x, camera->GetPosition().y);
		}


		camera->Update(level);
		UpdateObjects(dt);

		// update theo tung level cua playscene
		if (level == 1)
		{
			// gioi han 2 bien cua map 1
			if (simon->vx < 0 && simon->x < 16) simon->x= 16;
			if (simon->vx > 0 && simon->x > 1520)simon->x = 1520;


			// xu ly vao cham voi cua vao castle
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
				// va cham voi invisible object, va phai dang dung
				if (simon->IsContain(endrectmap1->GetBoundingBox().left, endrectmap1->GetBoundingBox().top, endrectmap1->GetBoundingBox().right, endrectmap1->GetBoundingBox().bottom) && !simon->jumping)
				{
					isgoingthroughendrect = true;
					simon->check_auto_move = true;
					if (simon->x >= endrectmap1->GetBoundingBox().left && !simon->jumping)
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
							simon->lives += 1;  // khi spawn se bi tru di 1
							SceneManager::GetInstance()->ReplaceScene(new PlayScene(level));
						}
					}
				}
			}
		}
		else // khi level = 2
		{
			// gioi han bien trai cua map 2
			if (simon->vx < 0 && simon->x < 16) simon->x = 16;
			if (camera->inzone2 || camera->movedownstair)
			{
				if (simon->vx < 0 && simon->x < 3088) simon->x = 3088;
			}
			if (camera->inzoneBoss)
			{
				if (simon->vx < 0 && simon->x < 5152) simon->x = 5152;
			}

			// xu ly di len xuong ham
			for (int i = 0; i < objects.size(); i++)
			{
				if (simon->IsContain(objects[i]->GetBoundingBox().left, objects[i]->GetBoundingBox().top, objects[i]->GetBoundingBox().right, objects[i]->GetBoundingBox().bottom))
				{
					if (dynamic_cast<invisibleObject*>(objects[i]))
					{
						switch (objects[i]->type)
						{
							// di xuong ham
						case TYPE_INVI_O_GO_DOWN_BASEMENT:
							if (simon->State == STATE_WALK_ONSTAIR_DOWN && simon->y > objects[i]->y)
							{
								camera->movedownstair = true;

								camera->SetPosition(simon->x, SCREEN_HEIGHT-6); // chuyen camera xuong ham

								//cap nhat lai vi tri truoc do tren cau thang cua SIMON cho khop khi di chuyen xuong ham
								simon->prevX = simon->prevX;
								simon->prevY = simon->prevY + 64;
								simon->SetPosition(simon->x, simon->y + 64);
							}
							break;

							// di len ham
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

			// XU LY TAO GHOST ////////////////////////////////////

			// neu xu dung stopwatch thi khong dem thoi gian, khong spawn enemy
			if (simon->timeusingstopwatch <= 0)
			{
				
				if (timetocreateghost > 0)
				{
					timetocreateghost -= dt;
				}
				if ((simon->x >= 0.0f && simon->x <= 832.0f) || (simon->x > 2208 && simon->x < 2784)) // nhung khung vi tri de spawn ghost
				{
					if (cancreateghost)
					{
						if (timetocreateghost <= 0)
						{
							if (simon->vx >= 0)
							{
								Ghost* ghost = new Ghost(camera->GetPosition().x + camera->camWidht / 2, 287.0f+BOARD_HEIGHT, -1);
								listenemy.push_back(ghost);
							}
							else
							{
								Ghost* ghost = new Ghost(camera->GetPosition().x - camera->camWidht / 2, 287.0f + BOARD_HEIGHT, 1);
								listenemy.push_back(ghost);
							}
							countghost++;
							timetocreateghost = 700;
							if (countghost == 3)
							{
								cancreateghost = false;
							}
						}
					}

				}

				// neu dang di qua cua thi khong spawn
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
										Ghost* ghost = new Ghost(camera->GetPosition().x + camera->camWidht / 2, 150 + BOARD_HEIGHT, -1);
										listenemy.push_back(ghost);
									}
									else
									{
										if (simon->vx > 0)
										{
											Ghost* ghost = new Ghost(camera->GetPosition().x + camera->camWidht / 2, 287.0f + BOARD_HEIGHT, -1);
											listenemy.push_back(ghost);
										}
										else
										{
											Ghost* ghost = new Ghost(camera->GetPosition().x - camera->camWidht / 2, 287.0f + BOARD_HEIGHT, 1);
											listenemy.push_back(ghost);
										}
									}
								}
								else
								{
									if (simon->vx > 0)
									{
										Ghost* ghost = new Ghost(camera->GetPosition().x + camera->camWidht / 2, 287.0f + BOARD_HEIGHT, -1);
										listenemy.push_back(ghost);
									}
									else
									{
										Ghost* ghost = new Ghost(camera->GetPosition().x - camera->camWidht / 2, 287.0f + BOARD_HEIGHT, 1);
										listenemy.push_back(ghost);
									}
								}
								countghost++;
								timetocreateghost = 700;
								if (countghost == 3)
								{
									cancreateghost = false;
								}
							}
						}

					}
				}

				// XU LY TAO PANTHER ////////////////////////////////////

				if (1216 < simon->x && simon->x < 2240)
				{
					// respawn panther
					if (cancreatepanther)
					{
						cancreatepanther = false;
						grid->respawnpanther();
					}
				}
				else // khi di ra khoi vung spawn panther thi moi co the xet tiep
				{
					// khi 1 panther chet thi bien count trong grid -1, co 3 panther, khi ca 3 chet thi moi duoc respawn panther
					if (grid->countpanther == 0)
					{
						cancreatepanther = true;
					}
				}


				// XU LY TAO BAT ////////////////////////////////////
				if (!isgoingthroughdoor && !isgoingthroughdoor2)
				{
					if (timetocreatebat > 0)
					{
						timetocreatebat -= dt;
					}
					if (simon->x >= 3072 && simon->y < 352 + BOARD_HEIGHT && simon->x <= 4111 && !(simon->x>3900&&simon->y<128 + BOARD_HEIGHT))
					{
						if (cancreatebat)
						{
							if (timetocreatebat <= 0)
							{
								if (simon->y < 160 + BOARD_HEIGHT)
								{
									Bat* bat = new Bat(camera->GetPosition().x + camera->camWidht / 2, 112.0f + BOARD_HEIGHT, -1);
									listenemy.push_back(bat);
								}
								else
								{
									int random = rand() % 3;
									if (random == 0)
									{
										Bat* bat = new Bat(camera->GetPosition().x + camera->camWidht / 2, 208.0f + BOARD_HEIGHT, -1);
										listenemy.push_back(bat);
									}
									else if (random == 1)
									{
										Bat* bat = new Bat(camera->GetPosition().x + camera->camWidht / 2, 304.0f + BOARD_HEIGHT, -1);
										listenemy.push_back(bat);
									}
									else if (random == 2)
									{
										Bat* bat = new Bat(camera->GetPosition().x - camera->camWidht / 2, 304.0f + BOARD_HEIGHT, 1);
										listenemy.push_back(bat);
									}

								}
								countbat++;
								timetocreatebat = 4000;
								if (countbat == 2)
								{
									cancreatebat = false;
								}
							}
						}
					}
				}

				// XU LY TAO FISHMAN ////////////////////////////////////
				if (timetocreatefishman > 0)
				{
					timetocreatefishman -= dt;
				}
				if (camera->movedownstair)
				{
					if (cancreatefishman && !simon->isOnStair)
					{
						if (timetocreatefishman <= 0)
						{
							if (simon->x > 3360.0f && simon->x < 3520)
							{
								if (countfishman < 2)
								{
									Fishman* fishman = new Fishman(3264, 672 + BOARD_HEIGHT, 1);
									listenemy.push_back(fishman);
									countfishman++;
									createeffectsteam(fishman->x, fishman->y);

								}
								if (countfishman < 2)
								{
									Fishman* fishman = new Fishman(3520, 672 + BOARD_HEIGHT, -1);
									listenemy.push_back(fishman);
									countfishman++;
									createeffectsteam(fishman->x, fishman->y);
								}
								timetocreatefishman = 3000;
							}
							if (simon->vx <= 0 && simon->x < 3260 && simon->x > 3072)
							{
								if (countfishman < 2)
								{
									Fishman* fishman = new Fishman(3136, 672 + BOARD_HEIGHT, 1);
									listenemy.push_back(fishman);
									countfishman++;
									createeffectsteam(fishman->x, fishman->y);

								}
								if (countfishman < 2)
								{
									Fishman* fishman = new Fishman(3392, 672 + BOARD_HEIGHT, -1);
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
									Fishman* fishman = new Fishman(3520, 672 + BOARD_HEIGHT, 1);
									listenemy.push_back(fishman);
									countfishman++;
									createeffectsteam(fishman->x, fishman->y);
								}

								if (countfishman < 2)
								{
									Fishman* fishman = new Fishman(3648, 672 + BOARD_HEIGHT, simon->x < 3648 ? -1 : 1);
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
									Fishman* fishman = new Fishman(3776, 672 + BOARD_HEIGHT, simon->x < 3776 ? -1 : 1);
									listenemy.push_back(fishman);
									countfishman++;
									createeffectsteam(fishman->x, fishman->y);
								}
								if (countfishman < 2)
								{
									Fishman* fishman = new Fishman(3904, 672 + BOARD_HEIGHT, simon->x < 3904 ? -1 : 1);
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

			// XU LY TAO BOSS ////////////////////////////////////
			if (simon->x > 5152 && boss == NULL)
			{
				boss = new Phantom_bat();
				listenemy.push_back(boss);
			}

			// xu ly di qua cua 1
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
							simon->instages = 2;
							door1->isDead = true;
							door1 = NULL;
						}
					}
				}
			}


			// xu ly di qua cua 2
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
							simon->instages = 3;
							door2->isDead = true;
							door2 = NULL;
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
	grid->GetListObject(objects); // moi lan update, clear list vao lay ra lai tu trong grid

	// xu ly khi boss chet
	if (checkBossDead)
	{
		timetospawnCrystal += dt;
	}
	if (timetospawnCrystal >= 1000 && checkBossDead)
	{
		Item* item = new Item(TYPE_ITEM_CRYSTAL);
		item->SetPosition(5343, 120+BOARD_HEIGHT);
		grid->insert(item);
		checkBossDead = false;
	}

	// update list objects lay ra tu grid
	for (CGameObject* o : objects)
	{
		o->Update(dt, &objects);
	}


	// update list enemy
	for (int i = 0; i < listenemy.size(); i++)
	{
		Enemy* e = listenemy[i];
		if (e->isDead)
		{
			listenemy.erase(listenemy.begin()+i);
			if (e->type == TYPE_ENEMY_BOSS_1)
			{
				checkBossDead = true;
				
			}
			if (e->type == TYPE_ENEMY_GHOST)
			{
				countghost--;
				if (countghost == 0)
				{
					timetocreateghost = 3000;
					cancreateghost = true;
				}
			}
			if (e->type == TYPE_ENEMY_BAT)
			{
				countbat--;
				if (countbat == 0)
				{
					timetocreatebat = 3000;
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
			// Neu enemy la FISHMAN hoac BOSS thi co them xu ly spawn ENEMY_BULLET
			if (e->type == TYPE_ENEMY_FISHMAN && dynamic_cast<Fishman*>(e)->attacking == true && dynamic_cast<Fishman*>(e)->canspawnbullet == true)
			{
				dynamic_cast<Fishman*>(e)->canspawnbullet = false;
				Enemy_bullet * bullet = new Enemy_bullet(e->x, e->y - 20, e->direct);
				list_enemy_weapon.push_back(bullet);
			}
			else if (e->type == TYPE_ENEMY_BOSS_1 && dynamic_cast<Phantom_bat*>(e)->canshoot == true)
			{
				dynamic_cast<Phantom_bat*>(e)->canshoot = false;
				Enemy_bullet * bullet = new Enemy_bullet(e->x, e->y, 1
					,dynamic_cast<Phantom_bat*>(e)->bulletvx, dynamic_cast<Phantom_bat*>(e)->bulletvy);
				list_enemy_weapon.push_back(bullet);

			}
			else
				e->Update(dt, &objects);
		}
	}

	// PANTHER trong grid nen xu ly rieng
	grid->GetListPanther(listenemy_tronggrid);
	for (Enemy* e : listenemy_tronggrid)
	{
		e->Update(dt, &objects);
		grid->movepanther(e,e->x,e->y);
	}


	// update list enemy bullet
	for (int i = 0; i < list_enemy_weapon.size(); i++)
	{
		if (list_enemy_weapon[i]->isDead)
		{
			list_enemy_weapon.erase(list_enemy_weapon.begin() + i);
		}
		else
		{
			list_enemy_weapon[i]->Update(dt, &objects);
		}
	}

	// update list effect
	for (int i = 0; i < listeffect.size(); i++)
	{
		if (listeffect[i]->isDead)
		{
			if (dynamic_cast<burn*>(listeffect[i]) && dynamic_cast<burn*>(listeffect[i])->model==0) // small burn
			{
				RandomSpawnItem(listeffect[i]->x, listeffect[i]->y);
			}
			listeffect.erase(listeffect.begin() + i);
		}
		else
		{
			listeffect[i]->Update(dt);
		}
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
	if (!isgoingthroughdoor && !isgoingthroughdoor2)
	{
		for (CGameObject* o : objects)
		{
			o->Render();
		}
	}
	else
	{
		for (CGameObject* o : objects)
		{
			if (o->tag == TAG_DOOR)
			{
				o->Render();
			}
		}
	}
	for (Enemy* e : listenemy)
	{
		e->Render();
	}
	for (Enemy*e : listenemy_tronggrid)
	{
		e->Render();
	}
	for (Weapon* w : list_enemy_weapon)
	{
		w->Render();
	}
	for (Effect*e : listeffect)
	{
		e->Render();
	}
	simon->Render();
	board->render();
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

void PlayScene::RandomSpawnItem(float x, float y)
{
	int rand1 = rand() % 5;
	if (rand1 <1) // ti le rot ra item khi giet enemy la 20%
	{
		int itemid;
		int rand2 = rand() % 20;
		if (rand2 <=6)
		{
			if (SIMON->morningstarlevel < 3)
			{
				itemid = TYPE_ITEM_WHIP;
			}
			else
				itemid = TYPE_ITEM_HEART;
		}
		else if (rand2 > 6 && rand2 <= 8)
		{
			itemid = TYPE_ITEM_MONEY_400;
		}
		else if (rand2 > 8 && rand2 <= 10)
		{
			itemid = TYPE_ITEM_DAGGER;
		}
		else if (rand2 > 10 && rand2 <= 12)
		{
			itemid = TYPE_ITEM_HOLY_WATER;
		}
		else if (rand2 > 12 && rand2 <= 14)
		{
			itemid = TYPE_ITEM_HOLY_CROSS;
		}
		else if (rand2 > 14 && rand2 <= 16)
		{
			itemid = TYPE_ITEM_STOP_WATCH;
		}
		else if (rand2 > 16 && rand2 <= 18)
		{

			itemid = TYPE_ITEM_AXE;
		}
		else if (rand2 > 18 && rand2 < 20)
		{
			itemid =TYPE_ITEM_DOUBLE_SHOT;
		}
		Item*item = new Item(itemid);
		item->SetPosition(x, y);
		grid->insert(item);
	}
	else
	{
		return;
	}
}

