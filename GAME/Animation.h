#pragma once
//#include"Sprites.h"
#include"SpritesManager.h"
class CAnimationFrame
{
	LPSPRITE sprite;
	DWORD time;

public:
	CAnimationFrame(LPSPRITE sprite, int time) { this->sprite = sprite; this->time = time; }
	DWORD GetTime() { return time; }
	LPSPRITE GetSprite() { return sprite; }
};

typedef CAnimationFrame *LPANIMATION_FRAME;

class CAnimation
{
	bool endanimation;
	DWORD lastFrameTime;
	int defaultTime;
public:

	vector<LPANIMATION_FRAME> frames;
	int currentFrame;
	CAnimation(int defaultTime) { this->defaultTime = defaultTime; lastFrameTime = -1; currentFrame = -1; endanimation = false; }
	void Add(int tag, int index, DWORD time = 0);
	void Render(float x, float y);
	bool CheckEndAni() { return endanimation; }
	void SetEndAniFalse() { endanimation = false; }
	bool isreverse;
};

typedef CAnimation *LPANIMATION;

class CAnimations
{
	static CAnimations * __instance;

	unordered_map<int, LPANIMATION> animations;

public:
	void Add(int id, LPANIMATION ani);
	LPANIMATION Get(int id);

	static CAnimations * GetInstance();
};
