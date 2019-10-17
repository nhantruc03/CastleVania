#include "AnimationsManager.h"
#include<fstream>

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
	std::ifstream iFile;
	char fileName[30];
	sprintf_s(fileName, "Res\\Text\\animations.txt");
	iFile.open(fileName);
	int DelayTime, numFrames, Tag;
	while (!iFile.eof())
	{
		iFile >> Tag;
		iFile >> numFrames;
		iFile >> DelayTime;
		ani = new CAnimation(DelayTime);
		for (int i = 0; i < numFrames; i++)
		{
			int index;
			iFile >> index;
			ani->Add(Tag, index);
		}
		Add(Tag, ani);
	}
	iFile.close();
}