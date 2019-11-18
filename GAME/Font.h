#pragma once
#include"Sprites.h"
#include"Camera.h"
class Font
{
public:
	float x, y;
	int tag;
	LPSPRITE sprite;
	Font();
	void update();
	void Draw(float x, float y,  string  s);
	~Font();
};

