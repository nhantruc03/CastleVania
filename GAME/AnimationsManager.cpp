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
	// idle
	ani = new CAnimation(100);
	ani->Add(TAG_SIMON, 0);
	Add(TAG_SIMON, ani);
	// walk
	ani = new CAnimation(100);
	ani->Add(TAG_SIMON, 0);
	ani->Add(TAG_SIMON, 1);
	ani->Add(TAG_SIMON, 2);
	ani->Add(TAG_SIMON, 3);
	Add(TAG_SIMON, ani);
	// jump
	ani = new CAnimation(100);
	ani->Add(TAG_SIMON, 4);
	Add(TAG_SIMON, ani);
	// fall
	ani = new CAnimation(100);
	ani->Add(TAG_SIMON, 0);
	Add(TAG_SIMON, ani);
	// attack
	ani = new CAnimation(150);
	ani->Add(TAG_SIMON, 0);
	ani->Add(TAG_SIMON, 5);
	ani->Add(TAG_SIMON, 6);
	ani->Add(TAG_SIMON, 7);
	Add(TAG_SIMON, ani);
	// sit
	ani = new CAnimation(100);
	ani->Add(TAG_SIMON, 4);
	Add(TAG_SIMON, ani);
	// attack sit
	ani = new CAnimation(150);
	ani->Add(TAG_SIMON, 4);
	ani->Add(TAG_SIMON, 8);
	ani->Add(TAG_SIMON, 9);
	ani->Add(TAG_SIMON, 10);
	Add(TAG_SIMON, ani);

}
