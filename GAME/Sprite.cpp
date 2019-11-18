#include "Sprite.h"
#include "Game.h"
#include "debug.h"
#include "Simon.h"
CSprite::CSprite(int tag, int l, int t, int r, int b, LPDIRECT3DTEXTURE9 tex)
{
	isreverse = false;
	this->tag = tag;
	rect.left = l;
	rect.right = r;
	rect.top = t;
	rect.bottom = b;
	texture = tex;
	center = D3DXVECTOR3((r - l) / 2, (b - t) / 2, 0);
}

void CSprite::Draw(float x, float y,int alpha,int r,int g,int b)
{
	D3DXVECTOR3 CamPosition = Camera::GetInstance()->GetPosition();
	D3DXVECTOR3 p(x , y , 0);
	D3DXVECTOR2 pScalingCenter = D3DXVECTOR2(x, y);							// vi tri thu phong hinh anh
	D3DXVECTOR2 pTranslation;
	if (tag != TAG_BOARD && tag !=TAG_FONT)
	{
		pTranslation = D3DXVECTOR2(floor(SCREEN_WIDTH / 2 - CamPosition.x), -CamPosition.y);	// tinh tien hinh anh
	}
	else
		pTranslation = D3DXVECTOR2(0, 0);
	D3DXVECTOR2 pScaling = D3DXVECTOR2(isreverse ? -1 : 1, 1);					// lat hinh va thu phong hinh anh
	CGame::GetInstance()->Draw(p, texture, rect, center, pScalingCenter, pScaling, pTranslation,alpha,r,g,b);
}


