#include "SpritesManager.h"



SpritesManager *SpritesManager::__instance = NULL;

SpritesManager *SpritesManager::GetInstance()
{
	if (__instance == NULL) __instance = new SpritesManager();
	return __instance;
}



void SpritesManager::Add(int tag, int l, int t, int r, int b, LPDIRECT3DTEXTURE9 tex)
{
	LPSPRITE s = new CSprite(tag, l, t, r, b, tex);
	sprites[s->tag].push_back(s);
}

LPSPRITE SpritesManager::Get(int tag, int index)
{
	return sprites[tag][index];
}

void SpritesManager::LoadResources()
{
	LPDIRECT3DTEXTURE9 texture = CTextures::GetInstance()->Get(ID_TEX_SIMON);
	//				SIMON
	Add(TAG_SIMON, 12, 2, 44, 64, texture); // idle
	// walking
	Add(TAG_SIMON, 78, 2, 102, 64, texture);
	Add(TAG_SIMON, 136, 2, 166, 64, texture);
	Add(TAG_SIMON, 196, 2, 220, 64, texture);

	Add(TAG_SIMON, 240, 1, 300, 47, texture); // jumping

	// attacking 
	Add(TAG_SIMON, 300, 2, 360, 64, texture);
	Add(TAG_SIMON, 360, 2, 420, 64, texture);
	Add(TAG_SIMON, 420, 2, 480, 64, texture);

	// sit attacking
	Add(TAG_SIMON, 420, 67, 480, 113, texture);
	Add(TAG_SIMON, 0, 133, 60, 179, texture);
	Add(TAG_SIMON, 60, 133, 120, 179, texture);
	//				WEAPON
	//		MORNINGSTAR
	texture = CTextures::GetInstance()->Get(ID_TEX_MORNINGSTAR);
	//	level 1
	Add(TAG_WEAPON, 136, 18, 152, 64, texture);
	Add(TAG_WEAPON, 280, 12, 312, 50, texture);
	Add(TAG_WEAPON, 352, 16, 396, 32, texture);
	//	level 2
	Add(TAG_WEAPON, 136, 86, 152, 134, texture);
	Add(TAG_WEAPON, 280, 80, 312, 118, texture);
	Add(TAG_WEAPON, 352, 90, 396, 102, texture);
	//	level 3
	Add(TAG_WEAPON, 136, 154, 152, 202, texture);
	Add(TAG_WEAPON, 280, 148, 312, 186, texture);
	Add(TAG_WEAPON, 320, 158, 395, 170, texture);

	//	Add(18, 136, 217, 136+15, 217+50, texMorningStar);
		//Add(19, 281, 215, 281+30, 215+40, texMorningStar);
		//Add(20, 320, 225, 320+74, 255+13, texMorningStar);
	texture = CTextures::GetInstance()->Get(ID_TEX_MAP1);
	for (int i = 0; i < 49; i++)
	{
		Add(TAG_MAP1, i * 32, 0, (i + 1) * 32, 32, texture);
	}
	//				HOLD ITEM OBJECT
	//		FIRE PILLAR
	texture = CTextures::GetInstance()->Get(ID_tex_HOLDER);
	Add(TAG_HOLDER, 0, 0, 32, 64,texture);
	Add(TAG_HOLDER, 32, 0, 64, 64, texture);

	texture = CTextures::GetInstance()->Get(ID_TEX_DAGGER);
	Add(TAG_WEAPON, 0, 0, 32, 18, texture);

}
