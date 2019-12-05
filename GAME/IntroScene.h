#pragma once
#include"Sprites.h"
#include"Sprite.h"
#include"Animations.h"
#include"Scene.h"
#include"Font.h"
#include"IntroObjects.h"
#include"Board.h"
#define TAG_BACKGROUND 13
class IntroScene: public Scene
{
private:
	IntroObjects* mainmenu_bat;
	Board* board;
	vector<LPGAMEOBJECT>objects;
	Font* font;
	CSprite* background;
	float time_to_show_text;
	bool inmainmenu;
	IntroObjects* temp_simon;
	bool run_time;
	float time_delay_changescene;
public:
	IntroScene();
	~IntroScene();

	void Update(DWORD dt);

	void createeffectsteam(float x, float y){}

	void LoadResources(int level);
	void Render();
	void OnKeyDown(int key);
	void OnKeyUp(int key){}

};

