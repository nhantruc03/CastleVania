/* =============================================================
	INTRODUCTION TO GAME PROGRAMMING SE102

	SAMPLE 03 - KEYBOARD AND OBJECT STATE

	This sample illustrates how to:

		1/ Process keyboard input
		2/ Control object state with keyboard events
================================================================ */

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "debug.h"
#include "Game.h"
#include "Textures.h"

#include "Simon.h"

CGame *game;
//CSimon *simon;
LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
	Load all game resources
	In this example: load textures, sprites, animations and SIMON object
*/
//void LoadResources()
//{
//	CTextures * textures = CTextures::GetInstance();
//
//	//textures->Add(ID_TEX_SIMON, L"textures\\SIMON.png",D3DCOLOR_XRGB(176, 224, 248));
//	textures->Add(ID_TEX_SIMON, L"player.png", D3DCOLOR_XRGB(255, 0, 255));
//
//	CSprites * sprites = CSprites::GetInstance();
//	CAnimations * animations = CAnimations::GetInstance();
//
//	LPDIRECT3DTEXTURE9 texSimon = textures->Get(ID_TEX_SIMON);
//
//
//
//	sprites->Add(10011, 12, 2, 44,64, texSimon); // idle
//	// walking
//	sprites->Add(10012, 78, 2, 102, 64, texSimon);
//	sprites->Add(10013, 136, 2, 166, 64, texSimon);
//	sprites->Add(10014, 196, 2, 220, 64, texSimon);
//
//
//
//	sprites->Add(2, 252, 1, 284, 47, texSimon); // jumping
//
//	// attacking 
//	sprites->Add(6, 300, 2, 360, 64, texSimon);
//	sprites->Add(7, 360, 2, 420, 64, texSimon);
//	sprites->Add(8, 420, 2, 480, 64, texSimon);
//	LPANIMATION ani;
//
//
//	ani = new CAnimation(100);
//	ani->Add(10011);
//	animations->Add(401, ani);
//
//
//	ani = new CAnimation(100);
//	ani->Add(10011);
//	ani->Add(10012);
//	ani->Add(10013);
//	ani->Add(10014);
//	animations->Add(501, ani);
//
//
//	ani = new CAnimation(100);
//	ani->Add(2);
//	animations->Add(504, ani);
//
//	ani = new CAnimation(100);
//	ani->Add(10011);
//	ani->Add(6);
//	ani->Add(7);
//	ani->Add(8);
//	animations->Add(506, ani);
//
//	ani = new CAnimation(100);
//	ani->Add(2);
//	animations->Add(507, ani);
//
//	simon = new CSimon();
//	CSimon::AddAnimation(401);		// idle left
//	CSimon::AddAnimation(501);		// walk left
//	CSimon::AddAnimation(504);		// jump left
//	CSimon::AddAnimation(506);		// attacking left
//	CSimon::AddAnimation(507);
//	simon->SetPosition(30.0f, 100.0f);
//}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/


/*
	Render a frame
*/


HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd)
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	game = CGame::GetInstance();
	game->Init(hWnd);
	game->LoadResources();


	//LoadResources();
	game->Run();

	return 0;
}