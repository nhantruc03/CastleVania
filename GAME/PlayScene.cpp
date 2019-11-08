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
PlayScene::PlayScene(int level)
{
	LoadResources();
	srand(time(NULL));
	keyCode.clear();
	isgoingthroughdoor = false;
	isgoingthroughendrect = false;
	this->level = level;

	map = Maps::GetInstance()->GetMap(this->level);

	simon = CSimon::GetInstance();
	simon->SetPosition(30, 250);//287.0f);
	simon->Respawn();

	camera = Camera::GetInstance();

	//camera->inzone1 = false;

	objects.clear();

	grid = new Grid(level);
	grid->Loadresources();

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
			cancreatebat = true;
			cancreateghost = true;
			cancreatefishman = true;
			cancreatepanther = true;
			simon->usingholycross = false;
		}
		for (Enemy* e : listenemy)
		{
			objects.push_back(e);
		}
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
							if (simon->State==STATE_WALK_ONSTAIR_DOWN && simon->y>objects[i]->y)
							{
								camera->movedownstair = true;
								camera->SetPosition(simon->x, -384);

								simon->prevX = simon->prevX;
								simon->prevY = simon->prevY + 64;

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
						listenemy.push_back(new Panther(1444.0f, 175.0f, direction));
						listenemy.push_back(new Panther(1792.0f, 110.0f, direction));
						listenemy.push_back(new Panther(1920.0f, 175.0f, direction));
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
						if (simon->x > 3360.0f && simon->x<3520)
						{
							if (countfishman < 2)
							{
								Fishman* fishman = new Fishman(3264, 672, 1);
								listenemy.push_back(fishman);
								countfishman++;
							}
							if (countfishman < 2)
							{
								Fishman* fishman = new Fishman(3520, 672, -1);
								listenemy.push_back(fishman);
								countfishman++;
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
							}
							if (countfishman < 2)
							{
								Fishman* fishman = new Fishman(3392, 672, -1);
								listenemy.push_back(fishman);
								countfishman++;
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
							}

							if (countfishman < 2)
							{
								Fishman* fishman = new Fishman(3648, 672, simon->x < 3648?-1: 1);
								listenemy.push_back(fishman);
								countfishman++;
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
							}
							if (countfishman < 2)
							{
								Fishman* fishman = new Fishman(3904, 672, simon->x < 3904 ? -1 : 1);
								listenemy.push_back(fishman);
								countfishman++;
							}
							timetocreatefishman = 3000;
						}
					
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
			else
			{
				if (simon->IsContain(door1->GetBoundingBox().left, door1->GetBoundingBox().top, door1->GetBoundingBox().right, door1->GetBoundingBox().bottom) && door1->isclosed() )
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
		}

		
		
	}

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
			if (e->type == TYPE_ENEMY_PANTHER)
			{
				if (camera->IsContain(e->GetBoundingBox()))
				{
					e->Update(dt, &objects);
				}
			}
			else if (e->type == TYPE_ENEMY_FISHMAN && dynamic_cast<Fishman*>(e)->attacking == true && dynamic_cast<Fishman*>(e)->canspawnbullet == true)
			{

				dynamic_cast<Fishman*>(e)->canspawnbullet = false;
				Enemy_bullet * bullet = new Enemy_bullet(e->x, e->y - 20, e->direct);
				listenemy.push_back(bullet);
			}
			else
				e->Update(dt, &objects);
		}
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
		o->Render();

	}
	for (Enemy* e : listenemy)
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

