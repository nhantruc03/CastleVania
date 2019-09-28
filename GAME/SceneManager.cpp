#include "SceneManager.h"

SceneManager* SceneManager::_instance = NULL;

SceneManager::SceneManager()
{
	CurScene = nullptr;
}

// Thay thế Scene hiện có bằng Scene khác (dùng cho chuyển cảnh)
void SceneManager::ReplaceScene(Scene * scene)
{
	delete CurScene;
	CurScene = scene;
}

// Get Instance (Singleton Pattern)
SceneManager * SceneManager::GetInstance()
{
	if (_instance == NULL)
		_instance = new SceneManager();
	return _instance;
}