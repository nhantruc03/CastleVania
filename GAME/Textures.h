#pragma once
#include <unordered_map>
#include <d3dx9.h>
using namespace std;

/*
	Manage texture database
*/
class CTextures
{
	static CTextures * __instance;

	

public:
	unordered_map<int, LPDIRECT3DTEXTURE9> textures;
	CTextures();
	void Add(int id, LPCWSTR filePath, D3DCOLOR transparentColor);
	LPDIRECT3DTEXTURE9 Get(unsigned int i);
	void LoadResources(int level);
	static CTextures * GetInstance();
};