#include "SpritesManager.h"
#include<fstream>


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
	LPDIRECT3DTEXTURE9 texture;
	std::ifstream iFile;
	char fileName[30];
	sprintf_s(fileName, "Res\\Text\\sprites.txt");
	iFile.open(fileName);
	int idtex, numsprites, tag;
	while (!iFile.eof())
	{
		iFile >> tag;
		iFile >> idtex;
		iFile >> numsprites;
		texture = CTextures::GetInstance()->Get(idtex);
		for (int i = 0; i < numsprites; i++)
		{
			int l, t, r, b;
			iFile >> l >> t >> r >> b;
			Add(tag, l, t, r, b, texture);

		}
	}
	iFile.close();

	//				MAP(TILESET)
	//		MAP1
	texture = CTextures::GetInstance()->Get(ID_TEX_MAP1);
	for (int i = 0; i < 49; i++)
	{
		Add(TAG_MAP1, i * 32, 0, (i + 1) * 32, 32, texture);
	}
}
