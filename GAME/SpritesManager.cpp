#include "SpritesManager.h"



SpritesManager *SpritesManager ::__instance = NULL;

SpritesManager *SpritesManager::GetInstance()
{
	if (__instance == NULL) __instance = new SpritesManager();
	return __instance;
}



void SpritesManager::Add(int id, int t, int l, int r, int b, LPDIRECT3DTEXTURE9 tex)
{
	LPSPRITE s = new CSprite(id, t, l, r, b, tex);
	sprites[id] = s;
}

LPSPRITE SpritesManager::Get(int id)
{
	return sprites[id];
}
