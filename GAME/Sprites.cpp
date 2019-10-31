#include "Sprites.h"
#include<fstream>


Sprites*Sprites::__instance = NULL;

Sprites*Sprites::GetInstance()
{
	if (__instance == NULL) __instance = new Sprites();
	return __instance;
}



void Sprites::Add(int tag, int l, int t, int r, int b, LPDIRECT3DTEXTURE9 tex)
{
	LPSPRITE s = new CSprite(tag, l, t, r, b, tex);
	sprites[s->tag].push_back(s);
}

LPSPRITE Sprites::Get(int tag, int index)
{
	return sprites[tag][index];
}

void Sprites::LoadResources()
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
	texture = CTextures::GetInstance()->Get(8);
	for (int i = 0; i < 119; i++)
	{
		Add(TAG_MAP2, i * 32, 0, (i * 32) + 32, 32, texture);
	}
}
