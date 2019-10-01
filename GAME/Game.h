#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include"GameGlobal.h"
#define DIRECTINPUT_VERSION 0x0800

#include <dinput.h>
#include "SceneManager.h"
#include"PlayScene.h"
#define KEYBOARD_BUFFER_SIZE 1024
/*
Abstract class to define keyboard event handlers
*/

class CGame
{
	static CGame * __instance;
	//HWND hWnd;									// Window handle

	//LPDIRECT3D9 d3d = NULL;						// Direct3D handle
	//LPDIRECT3DDEVICE9 d3ddv = NULL;				// Direct3D device object

	//LPDIRECT3DSURFACE9 backBuffer = NULL;
	//LPD3DXSPRITE spriteHandler = NULL;			// Sprite helper library to help us draw 2D image on the screen 

	LPDIRECTINPUT8       di;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 didv;		// The keyboard device 

	BYTE  keyStates[256];			// DirectInput keyboard state buffer 
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data


public:
	void Init(HWND hWnd);
	void Draw(float x, float y, LPDIRECT3DTEXTURE9 texture, RECT rect,bool isreverse,D3DXVECTOR3 center);
	int IsKeyDown(int KeyCode);
	void ProcessKeyboard();



//	LPDIRECT3DDEVICE9 GetDirect3DDevice() { return this->d3ddv; }
	//LPDIRECT3DSURFACE9 GetBackBuffer() { return backBuffer; }
	//LPD3DXSPRITE GetSpriteHandler() { return this->spriteHandler; }
	void LoadResources();
	void Run();
	void Render();
	void Update(DWORD dt);
	static CGame * GetInstance();
	CGame();
	~CGame();
};


