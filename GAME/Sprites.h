#pragma once
#include"Sprite.h"
#include"Textures.h"
class Sprites
{
	static Sprites* __instance;

	unordered_map<int, vector<LPSPRITE>> sprites;

public:
	void Add(int tag, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);
	void Add(int tag, CSprite * sprite);
	LPSPRITE Get(int tag, int index);
	void LoadResources(int level);
	static Sprites* GetInstance();
};

