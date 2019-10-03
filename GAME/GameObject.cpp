#include <d3dx9.h>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Sprites.h"

CGameObject::CGameObject()
{
	//tag = 0;
	/*sitting = false;
	attacking = false;
	jumping = false;*/
	x = y = 0;
	vx = vy = 0;
	nx = 1;
	isReverse = true;
}

void CGameObject::Update(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

//void CGameObject::Render()
//{
//}

void CGameObject::AddAnimation(int aniId)
{
	LPANIMATION ani = CAnimations::GetInstance()->Get(aniId);
	animations.push_back(ani);
}



CGameObject::~CGameObject()
{
}
