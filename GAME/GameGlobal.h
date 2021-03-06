﻿#pragma once
#include <d3dx9.h>
#include <d3d9.h>
#include <dinput.h>
#include <WinUser.h>
#include <unordered_map>
//#include"effect.h"
// Các thông số và biến tổng dùng cho toàn bộ Game
#define WINDOW_CLASS_NAME L"CastleVania-17520122"
#define MAIN_WINDOW_TITLE L"CastleVania-17520122"
#define BOARD_HEIGHT 80
#define SCREEN_WIDTH 520//365//1536
#define SCREEN_HEIGHT 390 // Chiều dài cửa sổ
#define MAX_FRAME_RATE 120	// FPS
#define BACKGROUND_COLOR D3DCOLOR_XRGB(0, 0, 0)		// Màu nền BackBuffer
#define BACKGROUND_COLOR_WHILE_USING_HOLY_CROSS D3DCOLOR_XRGB(188, 188, 188)		
#define KEYBOARD_BUFFER_SIZE 1024

#define ID_TEX_SIMON 0
#define ID_TEX_MORNINGSTAR 1
#define ID_TEX_MAP1 2
#define ID_TEX_HOLDER 3
#define ID_TEX_DAGGER 4
#define ID_TEX_ITEM 5
#define ID_TEX_BURN_EFFECT 6
#define ID_TEX_MAP2 7


#define TAG_SIMON 0
#define TAG_WEAPON 1
	#define TYPE_WEAPON_MORNINGSTAR 0
	#define TYPE_WEAPON_DAGGER 1
	#define TYPE_WEAPON_HOLY_WATER 2
	#define TYPE_WEAPON_STOP_WATCH 3
	#define TYPE_WEAPON_AXE 4
	#define TYPE_ENEMY_BULLET 5
#define TAG_MAP1 2
#define TAG_HOLDER 3
	#define TYPE_HOLDER_FIREPILLAR 0
	#define TYPE_HOLDER_CANDLE 1
#define TAG_ITEM 4
	#define TYPE_ITEM_BIG_HEART 0
	#define TYPE_ITEM_WHIP 1
	#define TYPE_ITEM_DAGGER 2
	#define TYPE_ITEM_HEART 3
	#define TYPE_ITEM_MONEY_1000 4
	#define TYPE_ITEM_MONEY_700 5
	#define TYPE_ITEM_MONEY_400 6
	#define TYPE_ITEM_HOLY_WATER 7
	#define TYPE_ITEM_HOLY_CROSS 8
	#define TYPE_ITEM_STOP_WATCH 9
	#define TYPE_ITEM_CHICKEN 10
	#define TYPE_ITEM_AXE 11
	#define TYPE_ITEM_DOUBLE_SHOT 12
	#define TYPE_ITEM_GOLD_POTION 13
	#define TYPE_ITEM_CRYSTAL 14
#define TAG_EFFECT 5
	#define TYPE_EFFECT_BURN 0 // Burn gom 3 sprite 0 1 2 
	#define TYPE_EFFECT_HIT 3
	#define TYPE_EFFECT_400 4
	#define TYPE_EFFECT_700 5
	#define TYPE_EFFECT_BIG_BURN 6
#define TYPE_EFFECT_STEAM 6
#define TYPE_EFFECT_BROKENBRICK 7
#define TAG_MAP2 6
#define TAG_BRICK 7
#define TAG_ENEMY 8
	#define TYPE_ENEMY_GHOST 0
	#define TYPE_ENEMY_PANTHER 1
	#define TYPE_ENEMY_BAT 2
	#define TYPE_ENEMY_FISHMAN 3
#define TYPE_ENEMY_BOSS_1 4
#define TAG_DOOR 9
#define TAG_SPECIAL_BRICK 10
	#define TYPE_SPECIAL_BRICK1 0
	#define TYPE_SPECIAL_BRICK2	1
#define TAG_BOARD 11
#define TAG_FONT 12

#define TAG_INVISIBLE_OBJECT 999
	#define TYPE_INVI_O_ENDRECT_MAP1	0
	#define TYPE_INVI_O_GO_UP_STAIR_LTR 1
	#define TYPE_INVI_O_GO_UP_STAIR_RTL -1
	#define TYPE_INVI_O_GO_DOWN_STAIR_RTL 2
	#define TYPE_INVI_O_GO_DOWN_STAIR_LTR -2
	#define TYPE_INVI_O_GO_DOWN_BASEMENT 100
	#define TYPE_INVI_O_GO_UP_BASEMENT -100
	#define TYPE_INVI_O_WATER 3
	#define TYPE_INVI_O_RESPAWN 4

#define TYPE_INTRO_HELI 0
#define TYPE_INTRO_BAT 1
#define TYPE_INTRO_SIMON 2
#define TYPE_INTRO_MENUBAT 3

#define ENEMY_GRAVITY			0.001f
#define ENEMY_WALKING_SPEED		0.1f 
#define ENEMY_JUMP_SPEED_Y		0.15f
//// ===== Các thông số cho PLAYER ====
#define TIME_TO_CHANGE_COLOR_WHILE_USING_HOLY_CROSS 50

#define SIMON_WALKING_SPEED		0.13f
#define SIMON_JUMP_SPEED_Y		0.5f
#define SIMON_GRAVITY			0.0018f

#define STATE_STANDING				0
#define STATE_WALKING				1
#define STATE_JUMP					2
#define STATE_FALL					3
#define STATE_ATTACK				4
#define STATE_SITTING				5
#define STATE_SIT_ATTACKING			6
#define STATE_STAND_ONSTAIR_UP		7
#define STATE_WALK_ONSTAIR_UP		8
#define STATE_STAND_ONSTAIR_DOWN	9
#define STATE_WALK_ONSTAIR_DOWN		10
#define STATE_INJURED				11
#define STATE_ATTACK_ONSTAIR_DOWN	12
#define STATE_ATTACK_ONSTAIR_UP		13
#define STATE_DEAD					14


#define WEAPON_GRAVITY 0.002f
#define WEAPON_SPEED 0.25f

#define TIME_DELAY_FOR_SITTING 200

#define SIMON_WIDTH					32
#define SIMON_HEIGHT				62
#define SIMON_SITTING_HEIGHT		46

#define SIMON CSimon::GetInstance()

extern std::unordered_map<int, bool> keyCode;

extern float globle_time;

//extern  std::vector<Effect*>listeffect;

extern D3DCOLOR D3DCOLOR_BACKGROUND;


extern float ZONE_GHOST_1_LEFT;
extern float ZONE_GHOST_1_RIGHT;
extern float ZONE_GHOST_2_LEFT;
extern float ZONE_GHOST_2_RIGHT;
extern float ZONE_GHOST_3_LEFT;
extern float ZONE_GHOST_3_RIGHT;
extern float ZONE_PANTHER_1_LEFT;
extern float ZONE_PANTHER_1_RIGHT;
extern float ZONE_BAT_1_LEFT;
extern float ZONE_BAT_1_RIGHT;

extern float ZONE_FISHMAN_1_LEFT;
extern float ZONE_FISHMAN_1_RIGHT;

extern float ZONE_FISHMAN_2_LEFT;
extern float ZONE_FISHMAN_2_RIGHT;
extern float ZONE_FISHMAN_3_LEFT;
extern float ZONE_FISHMAN_3_RIGHT;
extern float ZONE_FISHMAN_4_LEFT;
extern float ZONE_FISHMAN_4_RIGHT;

extern float ZONE_FULL_MAP_LEFT;
extern float ZONE_FULL_MAP_RIGHT;
extern float ZONE_STAGE1_LEFT;
extern float ZONE_STAGE1_RIGHT;
extern float ZONE_STAGE2_LEFT;
extern float ZONE_STAGE2_RIGHT;
extern float ZONE_STAGE3_LEFT;
extern float ZONE_STAGE3_RIGHT;

extern float ZONE_BOSS_LEFT;
extern float ZONE_BOSS_RIGHT;

extern float GLOBAL_TIME;
extern float TIME_USE_HOLY_CROSS;
extern float UPGRADE_TIME;
extern float TIME_TO_RESPAWN;
extern float TIME_USE_STOP_WATCH;
extern float UNTOUCHABLETIME;
extern float TIMETOSPAWNCRYSTAL;

extern float CRYSTAL_SPAWN_X;
extern float CRYSTAL_SPAWN_Y;

extern float FISHMAN_POSY;
extern float FISHMAN1_POSX;
extern float FISHMAN2_POSX;
extern float FISHMAN3_POSX;
extern float FISHMAN4_POSX;
extern float FISHMAN5_POSX;
extern float FISHMAN6_POSX;
extern float FISHMAN7_POSX;
extern float FISHMAN8_POSX;

extern float GHOST_POSY;
extern float SPECIAL_GHOST_POSY;
extern float POSX_TOCREATESPECIALGHOST;

extern float BAT1_POSY;
extern float BAT2_POSY;
extern float BAT3_POSY;

extern float POSY_TOCREATEBAT;
extern float POSY_TONOTCREATEBAT;
extern float POSX_TONOTCREATEBAT;

extern float DISTANCE_TOACTIVE_PANTHER;

extern float POSX_ACTIVE_BOSS;
