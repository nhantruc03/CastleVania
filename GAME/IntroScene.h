#pragma once
#include"Sprites.h"
#include"Sprite.h"
#include"Animations.h"
#include"Scene.h"
#include"Font.h"
#include"IntroObjects.h"
#include"Board.h"
#define TAG_BACKGROUND 13
#define TEMP_SIMON 2
#define ANI_FACETODOOR 15
#define Ani_MAINMENU_BAT_STAND 1
#define TIME_DELAY_CHANGE_SCENE 3000
#define TIME_TO_SHOW_TEXT 400
#define TIME_TO_HIDE_TEXT 600
#define LOCATION_TO_FACE_TO_DOOR 0
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

