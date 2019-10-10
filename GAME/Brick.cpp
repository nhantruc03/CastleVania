#include "Brick.h"

void CBrick::Render()
{
	//animations[0]->Render(x, y);
	//RenderBoundingBox();
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x-16;
	t = y-16;
	r = x + 32;
	b = y + 32;
}