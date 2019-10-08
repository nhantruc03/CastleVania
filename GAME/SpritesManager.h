#pragma once
#include"Sprite.h"
#include"Textures.h"
class SpritesManager
{
	static SpritesManager * __instance;

	unordered_map<int, vector<LPSPRITE>> sprites;

public:
	void Add(int tag, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);
	LPSPRITE Get(int tag, int index);
	void LoadResources();
	static SpritesManager * GetInstance();
};

