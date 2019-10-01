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
	this->UpdateObjects(dt);

}

void PlayScene::UpdatePlayer(float dt)
{
	simon->Update(dt);
	if (SIMON->attacking)
	{

		Weapon* weapon = WeaponFactory::CreateWeapon(ID_WEAPON_MORNINGSTAR);
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

			if (w->isDead || (SIMON->state != SIMON_STATE_ATTACK
				&& SIMON->state != SIMON_STATE_SIT_ATTACKING))
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
	CTextures::GetInstance()->LoadResources();
	SpritesManager::GetInstance()->LoadResources();
	map1 = new map();
	//	CAnimations * animations = CAnimations::GetInstance();

	simon = CSimon::GetInstance();
	simon->SetPosition(30.0f, 150 - SIMON->height / 2);

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
