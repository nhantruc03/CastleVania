#pragma once
//#include"Game.h"
#include"GameGlobal.h"
#include"Textures.h"
using namespace std;
class Scene
{
public:
	Scene() {};
	virtual ~Scene() {};
	virtual void LoadResources() {};			// Tải resources trước khi tạo Scene
	virtual void Update(float dt) {};			// Update các thông số sau khoảng delta-time
	virtual void Render() {};					// Render các UI Components lên Scene
	virtual void OnKeyDown(int keyCode) {};		// Xử lí Scene khi nhấn phím
	virtual void OnKeyUp(int keyCode) {};		// Xử lí Scene khi thả phím
};