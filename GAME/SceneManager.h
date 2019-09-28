#pragma once
#include "Scene.h"

class SceneManager
{
private:
	static SceneManager* _instance;				// Instance (Singleton Pattern)

public:
	Scene* CurScene;							// Scene hiện tại mà Manager đang giữ
	SceneManager();
	void ReplaceScene(Scene* scene);			// Thay thế Scene hiện có bằng Scene khác (dùng cho chuyển cảnh)
	static SceneManager* GetInstance();			// Get Instance (Singleton Pattern)
};