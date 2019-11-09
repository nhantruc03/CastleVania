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

void Sprites::LoadResources(int level)
{
	sprites.clear();
	LPDIRECT3DTEXTURE9 texture;
	std::ifstream iFile;
	char fileName[30];
	sprintf_s(fileName, "Res\\Text\\sprites%d.txt",level);
	iFile.open(fileName);
	while (!iFile.eof())
	{
		int tag,idtex;
		iFile >> tag;
		iFile >> idtex;
		texture = CTextures::GetInstance()->Get(idtex);
		if (tag != TAG_MAP1 && tag != TAG_MAP2)
		{
			int numsprites;
			iFile >> numsprites;
			for (int i = 0; i < numsprites; i++)
			{
				int l, t, r, b;
				iFile >> l >> t >> r >> b;
				Add(tag, l, t, r, b, texture);

			}
		}
		else
		{
			int numTileset, widthTileset, heightTileset;
			iFile >> numTileset >> widthTileset >> heightTileset;
			for (int i = 0; i < numTileset; i++)
			{
				Add(tag, i * widthTileset, 0, (i * widthTileset) + widthTileset, heightTileset, texture);
			}

		}
	}
	iFile.close();
	
}
