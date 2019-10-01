#include "Sprites.h"
#include "Game.h"
#include "debug.h"
#include "Simon.h"
CSprite::CSprite(int tag, int l, int t, int r, int b, LPDIRECT3DTEXTURE9 tex)
{
	this->tag = tag;
	rect.left = l;
	rect.right = r;
	rect.top = t;
	rect.bottom = b;
	texture = tex;
	center = D3DXVECTOR3((r - l) / 2, (b - t) / 2, 0);
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
	// su dung matrix de tao ra ma tran moi cho viec ve hinh, doi goc toa do tu top-left sang giua tam cua hinh
	D3DXMATRIX oldMatrix, curMatrix;
	D3DXMatrixTransformation2D(&curMatrix, &pScalingCenter, 0, &pScaling, &pRotationCenter, 0, &pTranslation);
	spriteHandler->GetTransform(&oldMatrix);
	spriteHandler->SetTransform(&curMatrix);
	spriteHandler->Draw(texture, &rect, &center, &p, D3DCOLOR_XRGB(255, 255, 255));
	spriteHandler->SetTransform(&oldMatrix); // sau khi ve xong tra lai ma tran cu vi ham ve dung chung cho nhieu doi tuong khac nhau
}


