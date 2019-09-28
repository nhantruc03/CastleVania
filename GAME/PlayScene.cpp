#include "PlayScene.h"



PlayScene::PlayScene()
{
	simon = CSimon::GetInstance();
}


PlayScene::~PlayScene()
{

}

void PlayScene::Update(float dt)
{

	UpdatePlayer(dt);
	this->UpdateObjects(dt);

}

void PlayScene::UpdatePlayer(float dt)
{
	simon->Update(dt);
	if (SIMON->attacking)
	{

		Weapon* weapon = WeaponFactory::CreateWeapon(0);
		weapon->isReverse = SIMON->isReverse;
		weapon->x = SIMON->x + (SIMON->isReverse ? -22 : 22);
		weapon->y = SIMON->y + 8;
		visibleObjects.insert(weapon);
	//	SIMON->attacking = false;
	}
}

void PlayScene::UpdateObjects(float dt)
{
	auto it = visibleObjects.begin();
	while (it != visibleObjects.end())
	{
		auto o = *it;
		switch (o->tag)
		{
		case 0:
		{
			auto w = WeaponFactory::ConvertToWeapon(o);

			if (w->isDead || (SIMON->state!= SIMON_STATE_ATTACK
					&& SIMON->state!= SIMON_STATE_SIT_ATTACKING))
			{
				it = visibleObjects.erase(it);
				delete w;
				continue;
			}

			w->Update(dt);
			break;
		}
		}
		++it;
		
	}

	this->UpdateVisibleObjects();
}

void PlayScene::UpdateVisibleObjects()
{
	auto it = visibleObjects.begin();
	while (it != visibleObjects.end())
	{
		if ((*it)->tag != 0)
		{
			it = visibleObjects.erase(it);
		}
		else ++it;
	}
}

void PlayScene::LoadResources()
{
	CTextures * textures = CTextures::GetInstance();

	//textures->Add(ID_TEX_SIMON, L"textures\\SIMON.png",D3DCOLOR_XRGB(176, 224, 248));
	textures->Add(ID_TEX_SIMON, L"player.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(1, L"morningstar.png", D3DCOLOR_XRGB(255, 0, 255));

	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 texSimon = textures->Get(ID_TEX_SIMON);



	sprites->Add(10011, 12, 2, 44, 64, texSimon); // idle
	// walking
	sprites->Add(10012, 78, 2, 102, 64, texSimon);
	sprites->Add(10013, 136, 2, 166, 64, texSimon);
	sprites->Add(10014, 196, 2, 220, 64, texSimon);



	sprites->Add(2, 240, 1, 300	, 47, texSimon); // jumping

	// attacking 
	sprites->Add(6, 300, 2, 360, 64, texSimon);
	sprites->Add(7, 360, 2, 420, 64, texSimon);
	sprites->Add(8, 420, 2, 480, 64, texSimon);

	// sit attacking
	//sprites->Add(9, 432-2, 67, 480+2, 113, texSimon);
	//sprites->Add(10, 11-8-2, 133, 43+8+2, 179, texSimon);
	//sprites->Add(11, 59-2, 133, 107+2, 179, texSimon);
	sprites->Add(9, 420, 67, 480, 113, texSimon);
	sprites->Add(10, 0, 133, 60, 179, texSimon);
	sprites->Add(11, 60, 133, 120, 179, texSimon);

	LPANIMATION ani;


	ani = new CAnimation(100);
	ani->Add(10011);
	animations->Add(401, ani);


	ani = new CAnimation(100);
	ani->Add(10011);
	ani->Add(10012);
	ani->Add(10013);
	ani->Add(10014);
	animations->Add(501, ani);


	ani = new CAnimation(100);
	ani->Add(2);
	animations->Add(504, ani);

	ani = new CAnimation(100);
	ani->Add(10011);
	animations->Add(505, ani);

	ani = new CAnimation(100);
	ani->Add(10011);
	ani->Add(6);
	ani->Add(7);
	ani->Add(8);
	animations->Add(506, ani);

	ani = new CAnimation(100);
	ani->Add(2);
	animations->Add(507, ani);

	ani = new CAnimation(100);
	ani->Add(2);
	ani->Add(9);
	ani->Add(10);
	ani->Add(11);
	animations->Add(508, ani);

	simon = CSimon::GetInstance();
	CSimon::AddAnimation(401);		// idle 
	CSimon::AddAnimation(501);		// walk 
	CSimon::AddAnimation(504);		// jump 
	CSimon::AddAnimation(505);		// fall 
	CSimon::AddAnimation(506);		// attacking
	CSimon::AddAnimation(507);		// sit
	CSimon::AddAnimation(508);		// sit attack
	simon->SetPosition(30.0f, 150-SIMON->height/2);

	simon->Respawn();
}

void PlayScene::Render()
{

	simon->Render();
	for (auto o : visibleObjects)
	{
		o->Render();
	}
}

void PlayScene::OnKeyDown(int key)
{
	keyCode[key] = true;
	simon->OnKeyDown(key);
	//if (key == DIK_RIGHT)
	//{
	//	simon->setreverse(true);
	//	simon->SetState(SIMON_STATE_WALKING);
	//}
	//else
	//	simon->SetState(SIMON_STATE_IDLE);
}

void PlayScene::OnKeyUp(int key)
{
	keyCode[key] = false;
	simon->OnKeyUp(key);

}
