#pragma once
#include"Animation.h"
class Animations
{
	static Animations* __instance;

	//unordered_map<int, LPANIMATION> animations;
	unordered_map<int, vector<LPANIMATION>> animations;

public:
	void Add(int tag, LPANIMATION ani);
	LPANIMATION Get(int tag, int index);
	void LoadResources(int level);
	static Animations* GetInstance();
};

