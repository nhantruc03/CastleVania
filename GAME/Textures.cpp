#include <Windows.h>

#include <d3d9.h>
#include <d3dx9.h>

#include "debug.h"
#include "Game.h"
#include "textures.h"
#include<fstream>
#include<string>

CTextures * CTextures::__instance = NULL;

CTextures::CTextures()
{

}

CTextures *CTextures::GetInstance()
{
	if (__instance == NULL) __instance = new CTextures();
	return __instance;
}

void CTextures::Add(int id, LPCWSTR filePath, D3DCOLOR transparentColor)
{
	D3DXIMAGE_INFO info;
	HRESULT result = D3DXGetImageInfoFromFile(filePath, &info);
	if (result != D3D_OK)
	{
		DebugOut(L"[ERROR] GetImageInfoFromFile failed: %s\n", filePath);
		return;
	}

	LPDIRECT3DDEVICE9 d3ddv = CGame::GetInstance()->GetDirect3DDevice();
	LPDIRECT3DTEXTURE9 texture;

	result = D3DXCreateTextureFromFileEx(
		d3ddv,								// Pointer to Direct3D device object
		filePath,							// Path to the image to load
		info.Width,							// Texture width
		info.Height,						// Texture height
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		transparentColor,
		&info,
		NULL,
		&texture);								// Created texture pointer

	if (result != D3D_OK)
	{
		OutputDebugString(L"[ERROR] CreateTextureFromFile failed\n");
		return;
	}

	textures[id] = texture;

	DebugOut(L"[INFO] Texture loaded Ok: id=%d, %s \n", id, filePath);
}

LPDIRECT3DTEXTURE9 CTextures::Get(unsigned int i)
{
	return textures[i];
}

void CTextures::LoadResources(int level)
{
	textures.clear();
	std::ifstream iFile;
	int numfile;
	int numcolumn;
	char fileName[30];
	sprintf_s(fileName, "Res\\Text\\textures%d.txt",level);
	iFile.open(fileName);
	string line;
	while (!iFile.eof())
	{
		
		int id,r, g, b;
		string SourceTexture;
		iFile >> id >> SourceTexture >> r >> g >> b;

		// convert string to LPCWSTR
		int len;
		int slength = (int)SourceTexture.length() + 1;
		len = MultiByteToWideChar(CP_ACP, 0, SourceTexture.c_str(), slength, 0, 0);
		wchar_t* buf = new wchar_t[len];
		MultiByteToWideChar(CP_ACP, 0, SourceTexture.c_str(), slength, buf, len);
		wstring temp(buf);
		delete[] buf;
		LPCWSTR result =temp.c_str();

		Add(id, result, D3DCOLOR_XRGB(r, g, b));
	}
	
	iFile.close();

}



