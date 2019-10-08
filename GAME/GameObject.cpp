#include "GameObject.h"

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

void CGameObject::AddAnimation(int tag,int index)
{
	LPANIMATION ani = AnimationsManager::GetInstance()->Get(tag,index);
	animations.push_back(ani);
}



CGameObject::~CGameObject()
{
}
