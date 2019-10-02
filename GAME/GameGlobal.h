#pragma once
#include <d3dx9.h>
#include <d3d9.h>
#include <dinput.h>
#include <WinUser.h>
#include <unordered_map>

// Các thông số và biến tổng dùng cho toàn bộ Game
#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"02 - Sprite animation"
#define SCREEN_WIDTH 365//1536
#define SCREEN_HEIGHT 365 // Chiều dài cửa sổ
//#define SCREEN_TRANSLATEY 60
#define MAX_FRAME_RATE 90			// FPS
#define BACKGROUND_COLOR D3DCOLOR_XRGB(0, 0, 0)		// Màu nền BackBuffer
//#define DEFAULT_TPF 120							// Thời gian tồn tại của mỗi Frame (cho Animation)
//#define GRAVITY_SPEED 0.014f					// Tốc độ trọng lực
#define KEYBOARD_BUFFER_SIZE 1024
//#define NUMBER_MAP_LEVEL 3
//#define TILE_SIZE 16


#define ID_TEX_SIMON 0
#define ID_TEX_MORNINGSTAR 1
#define ID_TEX_MAP1 2
#define ID_TEX_ENEMY 10
#define ID_TEX_MISC 20

#define ID_WEAPON_MORNINGSTAR 0

#define TAG_SIMON 0
#define TAG_WEAPON 1
#define TAG_MAP1 2
//// ===== Các thông số cho PLAYER ====
//#define PLAYER_RUNNING_SPEED 0.095f
//#define PLAYER_INJURED_SPEED 0.065f
//#define PLAYER_JUMPING_SPEED 0.28f
//#define PLAYER_FALLING_SPEED 0.25f
//#define PLAYER_CLIMBING_SPEED 0.1f
//#define PLAYER_WIDTH 20
//#define PLAYER_STANDING_HEIGHT 26
//#define PLAYER_SITTING_HEIGHT 18


#define SIMON CSimon::GetInstance()

extern HINSTANCE hInstance;										// hInstance của windows hiện tại
extern HWND hWnd;								// hWnd hiện tại
extern LPDIRECT3D9 d3d;
extern LPD3DXSPRITE spriteHandler;								// SpriteHanlder hiện tại
extern LPDIRECT3DDEVICE9 d3ddev;								// Device directX hiện tại (nhằm đại diện card màn hình)
extern LPDIRECT3DSURFACE9 backBuffer;							// BackBuffer

extern std::unordered_map<int, bool> keyCode;

// === ENUM dùng định dạng loại Object và State ====
//extern enum Tag
//{
//	PLAYER,
//	ITEM,
//	WEAPON,
//	GROUND,
//	MAP1,
//	MAP2,
//	MAP3,
//	FONT,
//	ENEMY,
//	HOLDER,
//	BULLET,
//	INTROSCENE,
//	ENDSCENE,
//};
//
//
