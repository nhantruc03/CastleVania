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

void SpritesManager::LoadResources()
{
	LPDIRECT3DTEXTURE9 texSimon = CTextures::GetInstance()->Get(ID_TEX_SIMON);
	//				SIMON
	Add(1, 12, 2, 44, 64, texSimon); // idle
	// walking
	Add(2, 78, 2, 102, 64, texSimon);
	Add(3, 136, 2, 166, 64, texSimon);
	Add(4, 196, 2, 220, 64, texSimon);

	Add(5, 240, 1, 300, 47, texSimon); // jumping

	// attacking 
	Add(6, 300, 2, 360, 64, texSimon);
	Add(7, 360, 2, 420, 64, texSimon);
	Add(8, 420, 2, 480, 64, texSimon);

	// sit attacking
	Add(9, 420, 67, 480, 113, texSimon);
	Add(10, 0, 133, 60, 179, texSimon);
	Add(11, 60, 133, 120, 179, texSimon);
	//				WEAPON
	//		MORNINGSTAR
	LPDIRECT3DTEXTURE9 texMorningStar = CTextures::GetInstance()->Get(ID_TEX_MORNINGSTAR);
	//	level 1
	Add(12, 136, 18, 152, 64, texMorningStar);
	Add(13, 280, 12, 312, 50, texMorningStar);
	Add(14, 352, 16, 396, 32, texMorningStar);
	//	level 2
	Add(15, 136, 86, 152, 134, texMorningStar);
	Add(16, 280, 80, 312, 118, texMorningStar);
	Add(17, 352, 90, 396, 102, texMorningStar);
	//	level 3
	Add(18, 136, 154, 152, 202, texMorningStar);
	Add(19, 280, 148, 312, 186, texMorningStar);
	Add(20, 320, 158, 395, 170, texMorningStar);

//	Add(18, 136, 217, 136+15, 217+50, texMorningStar);
	//Add(19, 281, 215, 281+30, 215+40, texMorningStar);
	//Add(20, 320, 225, 320+74, 255+13, texMorningStar);


}
