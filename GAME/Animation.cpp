#include "Animation.h"


void CAnimation::Add(int tag, int index, DWORD time)
{
	int t = time;
	if (time == 0) t = this->defaultTime;

	LPSPRITE sprite = Sprites::GetInstance()->Get(tag, index);
	LPANIMATION_FRAME frame = new CAnimationFrame(sprite, t);
	frames.push_back(frame);
}

void CAnimation::Render(float x, float y,int alpha,int r,int g,int b)
{
	if (currentFrame!=-1)
	{

		frames[currentFrame]->GetSprite()->isreverse = this->isreverse;
		frames[currentFrame]->GetSprite()->Draw(x, y,alpha,r,g,b);
	}
}

void CAnimation::Update()
{
	DWORD now = GetTickCount();
	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames[currentFrame]->GetTime();
		if (now - lastFrameTime > t)
		{
			currentFrame++;
			lastFrameTime = now;
			if (currentFrame == frames.size())
			{
				currentFrame = 0;
				endanimation = true;

			}
			//DebugOut(L"now: %d, lastFrameTime: %d, t: %d\n", now, lastFrameTime, t);
		}

	}
}

