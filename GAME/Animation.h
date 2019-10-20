#pragma once
//#include"Sprites.h"
#include"Sprites.h"
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
	void Render(float x, float y,int alpha=255,int r=255,int g=255,int b=255);
	bool CheckEndAni() { return endanimation; }
	void SetEndAniFalse() { endanimation = false; }
	bool isreverse;
	void Update();
};

typedef CAnimation *LPANIMATION;

