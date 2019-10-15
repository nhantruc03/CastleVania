#pragma once
#include "Scene.h"
#include<unordered_set>
#include "Simon.h"
#include"WeaponFactory.h"
#include"map.h"
#include"Brick.h"
using namespace std;
class PlayScene : public Scene
{
private:
	CSimon* simon;
	vector<LPGAMEOBJECT>objects;

public:
	PlayScene();
	~PlayScene();
	Map *map1;

	void Update(DWORD dt);
	//void UpdateScene();						// Update các thông số các đối tượng trong Scene

	void UpdatePlayer(DWORD dt);
	void UpdateObjects(DWORD dt);
	void LoadResources();
	void Render();									// Tải Scene lên màn hình
	void OnKeyDown(int key);						// Xử lí Scene khi nhấn phím
	void OnKeyUp(int key);							// Xử lí Scene khi thả phím
};
