#include "PlayScene.h"



PlayScene::PlayScene()
{
	
}


PlayScene::~PlayScene()
{

}

void PlayScene::Update(float dt)
{
	
	UpdatePlayer(dt);
	camera->SetPosition(simon->x, 0);
	camera->Update();
	this->UpdateObjects(dt);
	

}

void PlayScene::UpdatePlayer(float dt)
{
	simon->Update(dt);
	if (simon->attacking)
	{

		Weapon* weapon = WeaponFactory::CreateWeapon(ID_WEAPON_MORNINGSTAR);
		if (simon->UsingMorningStar==false)
		{
			weapon->isReverse = simon->isReverse;
			visibleObjects.insert(weapon);
			simon->UsingMorningStar = true;
		}
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
		case TAG_WEAPON:
		{
			auto w = WeaponFactory::ConvertToWeapon(o);

			if ( simon->state != SIMON_STATE_ATTACK && simon->state != SIMON_STATE_SIT_ATTACKING)
			{
				it= visibleObjects.erase(it);
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
		if ((*it)->tag != TAG_WEAPON)
		{
			it = visibleObjects.erase(it);
		}
		else ++it;
	}
}

void PlayScene::LoadResources()
{
	CTextures::GetInstance()->LoadResources();
	SpritesManager::GetInstance()->LoadResources();
	map1 = new map();
	simon = CSimon::GetInstance();
	simon->SetPosition(30.0f, 150 - simon->height / 2);
	camera = Camera::GetInstance();
	simon->Respawn();
}

void PlayScene::Render()
{
	map1->Render();
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
