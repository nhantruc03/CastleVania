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
	mainmenu_bat = new IntroObjects(180, 300, 0, 0, TYPE_INTRO_MENUBAT);
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
			if (a->type == TEMP_SIMON)
			{
				if (a->x <= LOCATION_TO_FACE_TO_DOOR)
				{
					a->x = LOCATION_TO_FACE_TO_DOOR;
					a->vx = 0;
					dynamic_cast<IntroObjects*>(a)->animation = Animations::GetInstance()->Get(TAG_SIMON, ANI_FACETODOOR);
					run_time = true;
				}
			}
		}
	}
	else if (inmainmenu)
	{
		dynamic_cast<IntroObjects*>(mainmenu_bat)->animation->Update();
		if (dynamic_cast<IntroObjects*>(mainmenu_bat)->animation->currentFrame==14) // last frame
		{
			dynamic_cast<IntroObjects*>(mainmenu_bat)->animation = Animations::GetInstance()->Get(TAG_MAIN_MENU_BAT, Ani_MAINMENU_BAT_STAND);
		}

	}
	if (run_time)
	{
		time_delay_changescene += dt;
		if (time_delay_changescene >= TIME_DELAY_CHANGE_SCENE)
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
	
	background->Draw(-11, 235);
	if (inmainmenu)
	{
		if (time_to_show_text >= TIME_TO_SHOW_TEXT)
		{
			font->Draw(160, 290, "PUSH START KEY");
			if (time_to_show_text >= TIME_TO_HIDE_TEXT)
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
	if (inmainmenu)
	{
		if (key != DIK_A)
		{
			background = Sprites::GetInstance()->Get(TAG_BACKGROUND, 1);
			inmainmenu = false;
			objects.push_back(new IntroObjects(300, 146, -0.03f, 0, TYPE_INTRO_HELI));
			objects.push_back(new IntroObjects(150, 129, -0.01f, 0, TYPE_INTRO_BAT));
			objects.push_back(new IntroObjects(0, 200, 0.01f, -0.01f, TYPE_INTRO_BAT));
			objects.push_back(new IntroObjects(300, 380, -0.07f, 0, TYPE_INTRO_SIMON));
		}
	}
}