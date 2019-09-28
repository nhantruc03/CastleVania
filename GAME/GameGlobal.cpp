#include "GameGlobal.h"


HINSTANCE hInstance = NULL;						// hInstance của windows hiện tại
HWND hWnd = NULL;								// hWnd hiện tại
LPDIRECT3D9 d3d = NULL;
LPD3DXSPRITE spriteHandler = NULL;			// SpriteHanlder hiện tại
LPDIRECT3DDEVICE9 d3ddev = NULL;				// Device directX hiện tại (nhằm đại diện card màn hình)
LPDIRECT3DSURFACE9 backBuffer = NULL;		// BackBuffer

std::unordered_map<int, bool> keyCode;