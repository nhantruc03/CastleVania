#pragma once
#include <unordered_map>
#include <d3dx9.h>
#define ID_TEX_SIMON 0
#define ID_TEX_MORNINGSTAR 1
using namespace std;

/*
	Manage texture database
*/
class CTextures
{
	static CTextures * __instance;

	unordered_map<int, LPDIRECT3DTEXTURE9> textures;

public:
	CTextures();
	void Add(int id, LPCWSTR filePath, D3DCOLOR transparentColor);
	LPDIRECT3DTEXTURE9 Get(unsigned int i);
	void LoadResources();
	static CTextures * GetInstance();
};