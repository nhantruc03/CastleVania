#pragma once
#include "Scene.h"
#include<unordered_set>
#include "Simon.h"
#include"WeaponFactory.h"
#include"map.h"
using namespace std;
class PlayScene : public Scene
{
private:
	CSimon* simon;

	unordered_set<CGameObject*> visibleObjects;
public:
	PlayScene();
	~PlayScene();
	map *map1;

	void Update(float dt);
	//void UpdateScene();						// Update các thông số các đối tượng trong Scene

	void UpdatePlayer(float dt);
	void UpdateObjects(float dt);
	void UpdateVisibleObjects();
	void LoadResources();
	void Render();									// Tải Scene lên màn hình
	void OnKeyDown(int key);						// Xử lí Scene khi nhấn phím
	void OnKeyUp(int key);							// Xử lí Scene khi thả phím
};
