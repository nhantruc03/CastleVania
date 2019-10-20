#pragma once
#include <d3dx9.h>
#include <d3d9.h>
#include <dinput.h>
#include <WinUser.h>
#include <unordered_map>

// Các thông số và biến tổng dùng cho toàn bộ Game
#define WINDOW_CLASS_NAME L"CastleVania-17520122"
#define MAIN_WINDOW_TITLE L"CastleVania-17520122"
#define SCREEN_WIDTH 365//1536
#define SCREEN_HEIGHT 365 // Chiều dài cửa sổ
#define MAX_FRAME_RATE 90			// FPS
#define BACKGROUND_COLOR D3DCOLOR_XRGB(0, 0, 0)		// Màu nền BackBuffer
#define KEYBOARD_BUFFER_SIZE 1024

#define ID_TEX_SIMON 0
#define ID_TEX_MORNINGSTAR 1
#define ID_TEX_MAP1 2
#define ID_TEX_HOLDER 3
#define ID_TEX_DAGGER 4
#define ID_TEX_ITEM 5
#define ID_TEX_BURN_EFFECT 6


#define TAG_SIMON 0
#define TAG_WEAPON 1
#define TYPE_WEAPON_MORNINGSTAR 0
#define TYPE_WEAPON_DAGGER 1
#define TAG_MAP1 2
#define TAG_HOLDER 3
	#define TYPE_HOLDER_FIREPILLAR 0
#define TAG_ITEM 4
	#define TYPE_ITEM_BIG_HEART 0
	#define TYPE_ITEM_WHIP 1
	#define TYPE_ITEM_DAGGER 2
#define TAG_EFFECT 5
	#define TYPE_EFFECT_BURN 0

//// ===== Các thông số cho PLAYER ====
#define SIMON_WALKING_SPEED		0.12f
#define SIMON_JUMP_SPEED_Y		0.36f
#define SIMON_GRAVITY			0.001f

#define STATE_STANDING		0
#define STATE_WALKING			1
#define STATE_JUMP			2
#define STATE_FALL			3
#define STATE_ATTACK			4
#define STATE_SITTING			5
#define STATE_SIT_ATTACKING	6


#define SIMON_WIDTH					32
#define SIMON_HEIGHT				62
#define SIMON_SITTING_HEIGHT		46

#define SIMON CSimon::GetInstance()

extern std::unordered_map<int, bool> keyCode;


