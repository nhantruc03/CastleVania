#include "Sprites.h"
#include "Game.h"
#include "debug.h"
#include "Simon.h"
CSprite::CSprite(int id, int l, int t, int r, int b, LPDIRECT3DTEXTURE9 tex)
{
	//this->left = l;
	//this->top = t;
	//this->right = r;
	//this->bottom = b;
	//this->texture = tex;
	rect.left = l;
	rect.right = r;
	rect.top = t;
	rect.bottom = b;
	texture = tex;
	center = D3DXVECTOR3((r - l) / 2, (b - t) / 2, 0);
}

CSprites * CSprites::__instance = NULL;

CSprites *CSprites::GetInstance()
{
	if (__instance == NULL) __instance = new CSprites();
	return __instance;
}

void CSprite::Draw(float x, float y)
{
	/*RECT srect;
	srect.left = left;
	srect.top = top;
	srect.right = right;
	srect.bottom = bottom;
	auto center = D3DXVECTOR3((right - left) / 2, (bottom - top) / 2, 0);
	CGame * game = CGame::GetInstance();
	game->Draw(x, y, texture, srect, isreverse, center);*/
	D3DXVECTOR3 p(x, y, 0);
	auto pRotationCenter = D3DXVECTOR2(center.x, center.y);
	auto pScalingCenter = D3DXVECTOR2(x, y);
	auto pTranslation = D3DXVECTOR2(0, 0);
	auto pScaling = D3DXVECTOR2(isreverse ? -1 : 1, 1);
	//spriteHandler->Draw(texture, &rect, NULL, &p, D3DCOLOR_XRGB(255, 255, 255));
	D3DXMATRIX oldMatrix, curMatrix;
	D3DXMatrixTransformation2D(&curMatrix, &pScalingCenter, 0, &pScaling, &pRotationCenter, 0, &pTranslation);
	spriteHandler->GetTransform(&oldMatrix);
	spriteHandler->SetTransform(&curMatrix);
	spriteHandler->Draw(texture, &rect, &center, &p, D3DCOLOR_XRGB(255, 255, 255));
	spriteHandler->SetTransform(&oldMatrix);
}

void CSprites::Add(int id, int t, int l, int r, int b, LPDIRECT3DTEXTURE9 tex)
{
	LPSPRITE s = new CSprite(id, t, l, r, b, tex);
	sprites[id] = s;
}

LPSPRITE CSprites::Get(int id)
{
	return sprites[id];
}



void CAnimation::Add(int spriteId, DWORD time)
{
	int t = time;
	if (time == 0) t = this->defaultTime;

	LPSPRITE sprite = CSprites::GetInstance()->Get(spriteId);
	LPANIMATION_FRAME frame = new CAnimationFrame(sprite, t);
	frames.push_back(frame);
}

void CAnimation::Render(float x, float y)
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
	frames[currentFrame]->GetSprite()->isreverse = this->isreverse;
	frames[currentFrame]->GetSprite()->Draw(x, y);
}

CAnimations * CAnimations::__instance = NULL;

CAnimations * CAnimations::GetInstance()
{
	if (__instance == NULL) __instance = new CAnimations();
	return __instance;
}

void CAnimations::Add(int id, LPANIMATION ani)
{
	animations[id] = ani;
}

LPANIMATION CAnimations::Get(int id)
{
	return animations[id];
}