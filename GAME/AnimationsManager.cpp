#include "AnimationsManager.h"


AnimationsManager * AnimationsManager::__instance = NULL;

AnimationsManager * AnimationsManager::GetInstance()
{
	if (__instance == NULL) __instance = new AnimationsManager();
	return __instance;
}

void AnimationsManager::Add(int tag, LPANIMATION ani)
{
	animations[tag].push_back(ani);
}

LPANIMATION AnimationsManager::Get(int tag, int index)
{
	return animations[tag][index];
}

void AnimationsManager::LoadResources()
{
	LPANIMATION ani;
	//				PLAYER
	//		STANDING
	ani = new CAnimation(100);
	ani->Add(TAG_SIMON, 0);
	Add(TAG_SIMON, ani);
	//		WALKING
	ani = new CAnimation(100);
	ani->Add(TAG_SIMON, 0);
	ani->Add(TAG_SIMON, 1);
	ani->Add(TAG_SIMON, 2);
	ani->Add(TAG_SIMON, 3);
	Add(TAG_SIMON, ani);
	//		JUMPING
	ani = new CAnimation(100);
	ani->Add(TAG_SIMON, 4);
	Add(TAG_SIMON, ani);
	//		FALLING
	ani = new CAnimation(100);
	ani->Add(TAG_SIMON, 0);
	Add(TAG_SIMON, ani);
	//		ATTACKING
	ani = new CAnimation(100);
	ani->Add(TAG_SIMON, 0);
	ani->Add(TAG_SIMON, 5);
	ani->Add(TAG_SIMON, 6);
	ani->Add(TAG_SIMON, 7);
	Add(TAG_SIMON, ani);
	//		SITTING
	ani = new CAnimation(100);
	ani->Add(TAG_SIMON, 4);
	Add(TAG_SIMON, ani);
	//		SITTING ATTACKING
	ani = new CAnimation(100);
	ani->Add(TAG_SIMON, 4);
	ani->Add(TAG_SIMON, 8);
	ani->Add(TAG_SIMON, 9);
	ani->Add(TAG_SIMON, 10);
	Add(TAG_SIMON, ani);
	//				WEAPON
	//		MORNINGSTAR LV1
	ani = new CAnimation(100);
	ani->Add(TAG_WEAPON, 0);
	ani->Add(TAG_WEAPON, 1);
	ani->Add(TAG_WEAPON, 2);
	Add(TAG_WEAPON, ani);
	//		MORNINGSTAR LV2
	ani = new CAnimation(100);
	ani->Add(TAG_WEAPON, 3);
	ani->Add(TAG_WEAPON, 4);
	ani->Add(TAG_WEAPON, 5);
	Add(TAG_WEAPON, ani);
	//		MORNINGSTAR LV3
	ani = new CAnimation(100);
	ani->Add(TAG_WEAPON, 6);
	ani->Add(TAG_WEAPON, 7);
	ani->Add(TAG_WEAPON, 8);
	Add(TAG_WEAPON, ani);
	//		DAGGER
	ani = new CAnimation(120);
	ani->Add(TAG_WEAPON, 9);
	Add(TAG_WEAPON, ani);

	//				HOLDITEMOBJECT
	//		FIRE PILLAR
	ani = new CAnimation(100);
	ani->Add(TAG_HOLDER, 0);
	ani->Add(TAG_HOLDER, 1);
	Add(TAG_HOLDER, ani);
}