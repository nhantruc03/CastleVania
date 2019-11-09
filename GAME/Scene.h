#pragma once
#include"GameGlobal.h"
#include"Textures.h"
#include"Camera.h"
using namespace std;
class Scene
{
public:
	Camera * camera;
	Scene() {};
	virtual void LoadResources(int level) =0;			// Tải resources trước khi tạo Scene
	virtual void Update(DWORD dt) =0;			// Update các thông số sau khoảng delta-time
	virtual void Render() =0;					// Render các UI Components lên Scene
	virtual void OnKeyDown(int keyCode) =0;		// Xử lí Scene khi nhấn phím
	virtual void OnKeyUp(int keyCode) =0;		// Xử lí Scene khi thả phím
};