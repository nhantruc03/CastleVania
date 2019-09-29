#pragma once
#include"Sprites.h"
#include"Textures.h"
class SpritesManager
{
	static SpritesManager * __instance;

	unordered_map<int, LPSPRITE> sprites;

public:
	void Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);
	LPSPRITE Get(int id);
	void LoadResources();
	static SpritesManager * GetInstance();
};

