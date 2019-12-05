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
	getValue();
	getzone(level);
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
	
	
	simon->ResetRespawn();
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

	board = new Board();
}

void PlayScene::Update(DWORD dt)
{
	board->update(boss,dt);

	// Khi simon update thi tat ca dung lai
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

		// kiem tra cac gioi han cua camera
		camera->Update(level);

		UpdateObjects(dt);

		// update theo tung level cua playscene
		if (simon->outside)
		{
			// gioi han 2 bien cua map 1
			if (simon->vx < 0 && simon->x < ZONE_FULL_MAP_LEFT + 16) simon->x= ZONE_FULL_MAP_LEFT + 16;
			if (simon->vx > 0 && simon->x > ZONE_FULL_MAP_RIGHT -32 )simon->x = ZONE_FULL_MAP_RIGHT -32;


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
							simon->outside = false;
							delete endrectmap1;
							SceneManager::GetInstance()->ReplaceScene(new PlayScene(level));
						}
					}
				}
			}
		}
		else // khi level = 2
		{
			// gioi han bien trai cua map 2
			if (simon->vx < 0 && simon->x < ZONE_FULL_MAP_LEFT+ 16) simon->x = ZONE_FULL_MAP_LEFT+ 16;
			if (camera->inzone2 || camera->movedownstair)
			{
				if (simon->vx < 0 && simon->x < ZONE_STAGE2_LEFT + 16) simon->x = ZONE_STAGE2_LEFT + 16;
			}
			if (camera->inzoneBoss)
			{
				if (simon->vx < 0 && simon->x < ZONE_BOSS_LEFT + 16) simon->x = ZONE_BOSS_LEFT + 16;
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

			// Xu ly tao enemy
			EnemyHandle(dt);

			// xu ly di qua cua
			DoorHandle();
		}
	}
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
	if (timetospawnCrystal >= TIMETOSPAWNCRYSTAL && checkBossDead)
	{
		Item* item = new Item(TYPE_ITEM_CRYSTAL);
		item->SetPosition(CRYSTAL_SPAWN_X, CRYSTAL_SPAWN_Y +BOARD_HEIGHT);
		grid->insert(item);
		checkBossDead = false;
	}

	// update list objects lay ra tu grid
	for (CGameObject* o : objects)
	{
		if (o->tag == TAG_DOOR && o->type == 0 && camera->inzone2)
		{
			o->isDead = true;
		}
		else if (o->tag == TAG_DOOR && o->type == 1 && camera->inzone3)
		{
			o->isDead = true;
		}
		else
		{
			o->Update(dt, &objects);
		}
		
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

void PlayScene::EnemyHandle(DWORD dt)
{
	// XU LY TAO GHOST ////////////////////////////////////

			// neu xu dung stopwatch thi khong dem thoi gian, khong spawn enemy
	if (simon->timeusingstopwatch <= 0)
	{
		if (timetocreateghost > 0)
		{
			timetocreateghost -= dt;
		}
		if ((simon->x >= ZONE_GHOST_1_LEFT && simon->x <= ZONE_GHOST_1_RIGHT) || (simon->x > ZONE_GHOST_2_LEFT && simon->x < ZONE_GHOST_2_RIGHT)) // nhung khung vi tri de spawn ghost
		{
			if (cancreateghost)
			{
				if (timetocreateghost <= 0)
				{
					if (simon->vx >= 0)
					{
						Ghost* ghost = new Ghost(camera->GetPosition().x + camera->camWidht / 2, GHOST_POSY + BOARD_HEIGHT, -1);
						listenemy.push_back(ghost);
					}
					else
					{
						Ghost* ghost = new Ghost(camera->GetPosition().x - camera->camWidht / 2, GHOST_POSY + BOARD_HEIGHT, 1);
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
			if ((simon->x >= ZONE_GHOST_3_LEFT && simon->x <= ZONE_GHOST_3_RIGHT))
			{
				if (cancreateghost)
				{
					if (timetocreateghost <= 0)
					{
						if (simon->x < POSX_TOCREATESPECIALGHOST)
						{
							int random = rand() % 2;
							if (random == 0)
							{
								Ghost* ghost = new Ghost(camera->GetPosition().x + camera->camWidht / 2, SPECIAL_GHOST_POSY + BOARD_HEIGHT, -1);
								listenemy.push_back(ghost);
							}
							else
							{
								if (simon->vx > 0)
								{
									Ghost* ghost = new Ghost(camera->GetPosition().x + camera->camWidht / 2, GHOST_POSY + BOARD_HEIGHT, -1);
									listenemy.push_back(ghost);
								}
								else
								{
									Ghost* ghost = new Ghost(camera->GetPosition().x - camera->camWidht / 2, GHOST_POSY + BOARD_HEIGHT, 1);
									listenemy.push_back(ghost);
								}
							}
						}
						else
						{
							if (simon->vx > 0)
							{
								Ghost* ghost = new Ghost(camera->GetPosition().x + camera->camWidht / 2, GHOST_POSY + BOARD_HEIGHT, -1);
								listenemy.push_back(ghost);
							}
							else
							{
								Ghost* ghost = new Ghost(camera->GetPosition().x - camera->camWidht / 2, GHOST_POSY + BOARD_HEIGHT, 1);
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
		if (ZONE_PANTHER_1_LEFT < simon->x && simon->x < ZONE_PANTHER_1_RIGHT)
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
			if (simon->x >= ZONE_BAT_1_LEFT && simon->y < POSY_TOCREATEBAT + BOARD_HEIGHT && simon->x <= ZONE_BAT_1_RIGHT && !(simon->x > POSX_TONOTCREATEBAT && simon->y < POSY_TONOTCREATEBAT + BOARD_HEIGHT))
			{
				if (cancreatebat)
				{
					if (timetocreatebat <= 0)
					{
						if (simon->y < 160 + BOARD_HEIGHT)
						{
							Bat* bat = new Bat(camera->GetPosition().x + camera->camWidht / 2, BAT1_POSY + BOARD_HEIGHT, -1);
							listenemy.push_back(bat);
						}
						else
						{
							int random = rand() % 3;
							if (random == 0)
							{
								Bat* bat = new Bat(camera->GetPosition().x + camera->camWidht / 2, BAT2_POSY + BOARD_HEIGHT, -1);
								listenemy.push_back(bat);
							}
							else if (random == 1)
							{
								Bat* bat = new Bat(camera->GetPosition().x + camera->camWidht / 2, BAT3_POSY + BOARD_HEIGHT, -1);
								listenemy.push_back(bat);
							}
							else if (random == 2)
							{
								Bat* bat = new Bat(camera->GetPosition().x - camera->camWidht / 2, BAT3_POSY + BOARD_HEIGHT, 1);
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
					if (simon->x > ZONE_FISHMAN_1_LEFT && simon->x < ZONE_FISHMAN_1_RIGHT)
					{
						if (countfishman < 2)
						{
							Fishman* fishman = new Fishman(FISHMAN1_POSX, FISHMAN_POSY + BOARD_HEIGHT, 1);
							listenemy.push_back(fishman);
							countfishman++;
							createeffectsteam(fishman->x, fishman->y);
						}
						if (countfishman < 2)
						{
							Fishman* fishman = new Fishman(FISHMAN2_POSX, FISHMAN_POSY + BOARD_HEIGHT, -1);
							listenemy.push_back(fishman);
							countfishman++;
							createeffectsteam(fishman->x, fishman->y);
						}
						timetocreatefishman = 3000;
					}
					if (simon->vx <= 0 && simon->x < ZONE_FISHMAN_2_RIGHT && simon->x > ZONE_FISHMAN_2_LEFT)
					{
						if (countfishman < 2)
						{
							Fishman* fishman = new Fishman(FISHMAN3_POSX, FISHMAN_POSY + BOARD_HEIGHT, 1);
							listenemy.push_back(fishman);
							countfishman++;
							createeffectsteam(fishman->x, fishman->y);

						}
						if (countfishman < 2)
						{
							Fishman* fishman = new Fishman(FISHMAN4_POSX, FISHMAN_POSY + BOARD_HEIGHT, -1);
							listenemy.push_back(fishman);
							countfishman++;
							createeffectsteam(fishman->x, fishman->y);
						}
						timetocreatefishman = 3000;
					}
					if (simon->x > ZONE_FISHMAN_3_LEFT && simon->x < ZONE_FISHMAN_3_RIGHT)
					{
						if (countfishman < 2)
						{
							Fishman* fishman = new Fishman(FISHMAN5_POSX, FISHMAN_POSY + BOARD_HEIGHT, 1);
							listenemy.push_back(fishman);
							countfishman++;
							createeffectsteam(fishman->x, fishman->y);
						}

						if (countfishman < 2)
						{
							Fishman* fishman = new Fishman(FISHMAN6_POSX, FISHMAN_POSY + BOARD_HEIGHT, simon->x < FISHMAN6_POSX ? -1 : 1);
							listenemy.push_back(fishman);
							countfishman++;
							createeffectsteam(fishman->x, fishman->y);
						}
						timetocreatefishman = 3000;
					}
					if (simon->x > ZONE_FISHMAN_4_LEFT)
					{
						if (countfishman < 2)
						{
							Fishman* fishman = new Fishman(FISHMAN7_POSX, FISHMAN_POSY + BOARD_HEIGHT, simon->x < FISHMAN7_POSX ? -1 : 1);
							listenemy.push_back(fishman);
							countfishman++;
							createeffectsteam(fishman->x, fishman->y);
						}
						if (countfishman < 2)
						{
							Fishman* fishman = new Fishman(FISHMAN8_POSX, FISHMAN_POSY + BOARD_HEIGHT, simon->x < FISHMAN8_POSX ? -1 : 1);
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
	if (simon->x > ZONE_BOSS_LEFT && boss == NULL)
	{
		boss = new Phantom_bat();
		listenemy.push_back(boss);
	}	
}

void PlayScene::DoorHandle()
{
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
				if (camera->camPosition.x - camera->camWidht / 2 >= ZONE_STAGE2_LEFT)
				{
					camera->inzone2 = true;
					simon->check_auto_move = false;
					isgoingthroughdoor = false;
					simon->instages = 2;
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
				if (camera->camPosition.x - camera->camWidht / 2 >= ZONE_STAGE3_LEFT)
				{
					camera->inzone3 = true;
					simon->check_auto_move = false;
					isgoingthroughdoor2 = false;
					simon->instages = 3;
					door2 = NULL;
				}
			}
		}
	}
}

void PlayScene::getzone(int level)
{
	std::ifstream iFile;
	char fileName[30];
	sprintf_s(fileName, "Res\\Text\\zone%d.txt", level);
	iFile.open(fileName);
	while (!iFile.eof())
	{
		int type;
		int x, y;
		iFile >> type >> x >> y;
		switch (type)
		{
		case ZONE_GHOST1:
			ZONE_GHOST_1_LEFT = x;
			ZONE_GHOST_1_RIGHT = y;
			break;
		case ZONE_GHOST2:
			ZONE_GHOST_2_LEFT = x;
			ZONE_GHOST_2_RIGHT = y;
			break;
		case ZONE_GHOST3:
			ZONE_GHOST_3_LEFT = x;
			ZONE_GHOST_3_RIGHT = y;
			break;
		case ZONE_PANTHER:
			ZONE_PANTHER_1_LEFT = x;
			ZONE_PANTHER_1_RIGHT = y;
			break;
		case ZONE_BAT:
			ZONE_BAT_1_LEFT = x;
			ZONE_BAT_1_RIGHT = y;
			break;
		case ZONE_FISHMAN1:
			ZONE_FISHMAN_1_LEFT = x;
			ZONE_FISHMAN_1_RIGHT = y;
			break;
		case ZONE_FISHMAN2:
			ZONE_FISHMAN_2_LEFT = x;
			ZONE_FISHMAN_2_RIGHT = y;
			break;
		case ZONE_FISHMAN3:
			ZONE_FISHMAN_3_LEFT = x;
			ZONE_FISHMAN_3_RIGHT = y;
			break;
		case ZONE_FISHMAN4:
			ZONE_FISHMAN_4_LEFT = x;
			ZONE_FISHMAN_4_RIGHT = y;
			break;
		case ZONE_FULLMAP:
			ZONE_FULL_MAP_LEFT = x;
			ZONE_FULL_MAP_RIGHT = y;
			break;
		case ZONE_STAGE1:
			ZONE_STAGE1_LEFT = x;
			ZONE_STAGE1_RIGHT = y;
			break;
		case ZONE_STAGE2:
			ZONE_STAGE2_LEFT = x;
			ZONE_STAGE2_RIGHT = y;
			break;
		case ZONE_STAGE3:
			ZONE_STAGE3_LEFT = x;
			ZONE_STAGE3_RIGHT = y;
			break;
		case ZONE_BOSS:
			ZONE_BOSS_LEFT = x;
			ZONE_BOSS_RIGHT = y;
			break;
		}
	}
	iFile.close();
}

void PlayScene::getValue()
{
	std::ifstream iFile;
	char fileName[30];
	sprintf_s(fileName, "Res\\Text\\value.txt", level);
	iFile.open(fileName);
	while (!iFile.eof())
	{
		string type;
		int value;
		iFile >> type >> value;
		if (type == "globaltime")
		{
			GLOBAL_TIME = value;
		}
		else if (type == "timeuseholycross")
		{
			TIME_USE_HOLY_CROSS = value;
		}
		else if (type == "upgradetime")
		{
			UPGRADE_TIME = value;
		}
		else if (type == "timetorespawn")
		{
			TIME_TO_RESPAWN = value;
		}
		else if (type == "timeusestopwatch")
		{
			TIME_USE_STOP_WATCH = value;
		}
		else if (type == "untouchabletime")
		{
			UNTOUCHABLETIME = value;
		}
		else if (type == "timetospawncrystal")
		{
			TIMETOSPAWNCRYSTAL = value;
		}
		else if (type == "crystal_spawn_x")
		{
			CRYSTAL_SPAWN_X = value;
		}
		else if (type == "crystal_spawn_y")
		{
			CRYSTAL_SPAWN_Y = value;
		}
		else if (type == "fishman_y")
		{
			FISHMAN_POSY = value;
		}
		else if (type == "fishman1_x")
		{
			FISHMAN1_POSX = value;
		}
		else if (type == "fishman2_x")
		{
			FISHMAN2_POSX = value;
		}
		else if (type == "fishman3_x")
		{
			FISHMAN3_POSX = value;
		}
		else if (type == "fishman4_x")
		{
			FISHMAN4_POSX = value;
		}
		else if (type == "fishman5_x")
		{
			FISHMAN5_POSX = value;
		}
		else if (type == "fishman6_x")
		{
			FISHMAN6_POSX = value;
		}
		else if (type == "fishman7_x")
		{
			FISHMAN7_POSX = value;
		}
		else if (type == "fishman8_x")
		{
			FISHMAN8_POSX = value;
		}
		else if (type == "ghost_y")
		{
			GHOST_POSY = value;
		}
		else if (type == "special_ghost_y")
		{
			SPECIAL_GHOST_POSY = value;
		}
		else if (type == "posx_tocreatespecialghost")
		{
			POSX_TOCREATESPECIALGHOST = value;
		}
		else if (type == "posy_tocreatebat")
		{
			POSY_TOCREATEBAT = value;
		}
		else if (type == "posy_tonotcreatebat")
		{
			POSY_TONOTCREATEBAT = value;
		}
		else if (type == "posx_tonocreatebat")
		{
			POSX_TONOTCREATEBAT = value;
		}
		else if (type == "bat1_y")
		{
			BAT1_POSY = value;
		}
		else if (type == "bat2_y")
		{
			BAT2_POSY = value;
		}
		else if (type == "bat3_y")
		{
			BAT3_POSY = value;
		}
		else if (type == "distance_toactive_panther")
		{
			DISTANCE_TOACTIVE_PANTHER = value;
		}
		else if (type == "posx_activeboss")
		{
			POSX_ACTIVE_BOSS = value;
		}
	}
	iFile.close();
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
	if (rand1 < 1) // ti le rot ra item khi giet enemy la 20%
	{
		int itemid;
		int rand2 = rand() % 20;
		if (rand2 <= 6)
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
			itemid = TYPE_ITEM_DOUBLE_SHOT;
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

void PlayScene::createeffectsteam(float x, float y)
{
	listeffect.push_back(new steam(x, y, 1));
	listeffect.push_back(new steam(x, y, 2));
	listeffect.push_back(new steam(x, y, 3));
}

PlayScene::~PlayScene()
{

}
