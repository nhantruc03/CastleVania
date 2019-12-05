#include "IntroScene.h"
#include"GameGlobal.h"
#include"SceneManager.h"
#include"PlayScene.h"
IntroScene::IntroScene()
{
	
	LoadResources(0);
	board = new Board();
	font = new Font();
	background = Sprites::GetInstance()->Get(TAG_BACKGROUND, 0);
	time_to_show_text = 0;
	inmainmenu = true;
	run_time = false;
	time_delay_changescene;
	mainmenu_bat = new IntroObjects(180, 300, 0, 0, 0, 3);
}


IntroScene::~IntroScene()
{
}

void IntroScene::Update(DWORD dt)
{
	time_to_show_text += dt;
	

	if (!inmainmenu)
	{
		board->update(NULL, dt);
		for (CGameObject* a : objects)
		{
			a->Update(dt);
			if (a->type == 2)
			{
				if (a->x <= 0)
				{
					a->x = 0;
					a->vx = 0;
					dynamic_cast<IntroObjects*>(a)->animation = Animations::GetInstance()->Get(TAG_SIMON, 15);
					run_time = true;
				}
			}
		}
	}
	else if (inmainmenu)
	{
		dynamic_cast<IntroObjects*>(mainmenu_bat)->animation->Update();
		if (dynamic_cast<IntroObjects*>(mainmenu_bat)->animation->currentFrame == 14)
		{
			dynamic_cast<IntroObjects*>(mainmenu_bat)->animation = Animations::GetInstance()->Get(TAG_MAIN_MENU_BAT, 1);
		}

	}
	if (run_time)
	{
		time_delay_changescene += dt;
		if (time_delay_changescene >= 3000)
		{
			SceneManager::GetInstance()->ReplaceScene(new PlayScene(1));
		}
	}
}

void IntroScene::LoadResources(int level)
{
	CTextures::GetInstance()->LoadResources(level);
	Sprites::GetInstance()->LoadResources(level);
	Animations::GetInstance()->LoadResources(level);
}

void IntroScene::Render()
{
	
	background->Draw(0, 235);
	if (inmainmenu)
	{
		if (time_to_show_text >= 400)
		{
			font->Draw(160, 290, "PUSH START KEY");
			if (time_to_show_text >= 600)
			{
				time_to_show_text = 0;
			}
		}
		mainmenu_bat->Render();
	}
	else
	{
		for (CGameObject* a : objects)
		{
			a->Render();
		}
		board->render();
	}
}

void IntroScene::OnKeyDown(int key)
{
	if (key != DIK_A)
	{
		background = Sprites::GetInstance()->Get(14, 0);
		inmainmenu = false;
		objects.push_back(new IntroObjects(300, 146, 0.03f, 0, -1, 0));
		objects.push_back(new IntroObjects(150,129, 0.01f, 0, -1, 1));
		objects.push_back(new IntroObjects(0, 200, 0.01f, -0.01f, 1, 1));
		temp_simon = new IntroObjects(300, 380, 0.07f, 0, -1, 2);
		objects.push_back(temp_simon);
	}
}