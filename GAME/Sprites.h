#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>

using namespace std;

class CSprite
{
	int id;				// Sprite ID in the sprite database

	RECT rect;			// thay rectangle cho left top right bottom
	D3DXVECTOR3 center;

	LPDIRECT3DTEXTURE9 texture;
public:
	CSprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);

	void Draw(float x, float y);
	bool isreverse;
};

typedef CSprite * LPSPRITE;
