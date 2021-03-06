#include "GameObject.h"
#include<algorithm>
#include"Simon.h"
#include"Dagger.h"
#include"Enemy.h"
#include"Item.h"
CGameObject::CGameObject()
{
	tag = NULL;
	type = NULL;
	x = y = 0;
	vx = vy = 0;
	nx = 1;
	isDead = false;
	isReverse = false;
}

void CGameObject::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	this->dt = dt;
	dx = vx * dt;
	dy = vy * dt;
}

LPCOLLISIONEVENT CGameObject::SweptAABBEx(LPGAMEOBJECT coO)
{
	float sl, st, sr, sb;		// static object bbox
	float ml, mt, mr, mb;		// moving object bbox
	float t, nx, ny;

	coO->GetBoundingBox(sl, st, sr, sb);

	// deal with moving object: m speed = original m speed - collide object speed
	float svx, svy;
	coO->GetSpeed(svx, svy);

	float sdx = svx * dt;
	float sdy = svy * dt;

	float dx = this->dx - sdx;
	float dy = this->dy - sdy;

	GetBoundingBox(ml, mt, mr, mb);

	CGame::SweptAABB(
		ml, mt, mr, mb,
		dx, dy,
		sl, st, sr, sb,
		t, nx, ny
	);

	CCollisionEvent * e = new CCollisionEvent(t, nx, ny, coO);
	return e;
}

void CGameObject::CalcPotentialCollisions(vector<LPGAMEOBJECT>* coObjects, vector<LPCOLLISIONEVENT>& coEvents)
{
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<CSimon*>(this) && (coObjects->at(i)->tag == TAG_HOLDER || (coObjects->at(i)->tag == TAG_INVISIBLE_OBJECT && coObjects->at(i)->type!=TYPE_INVI_O_WATER) || (dynamic_cast<CSimon*>(this)->untouchable == 1 && (coObjects->at(i)->tag==TAG_ENEMY || coObjects->at(i)->tag == TAG_WEAPON))))
		{
			continue;
		}
		if (dynamic_cast<Weapon*>(this) && (coObjects->at(i)->tag == TAG_ITEM || coObjects->at(i)->tag==TAG_DOOR|| coObjects->at(i)->tag == TAG_INVISIBLE_OBJECT || (this->type!=TYPE_WEAPON_MORNINGSTAR&& coObjects->at(i)->tag == TAG_SPECIAL_BRICK)))
		{
			continue;
		}
		if (dynamic_cast<Enemy*>(this) && (coObjects->at(i)->tag == TAG_ITEM || (coObjects->at(i)->tag == TAG_INVISIBLE_OBJECT && coObjects->at(i)->type != TYPE_INVI_O_WATER) || coObjects->at(i)->tag == TAG_HOLDER || coObjects->at(i)->tag == TAG_ENEMY))
		{
			continue;
		}
		if (dynamic_cast<Item*>(this) && (coObjects->at(i)->tag != TAG_BRICK && coObjects->at(i)->tag!= TAG_SPECIAL_BRICK))
		{
			continue;
		}
		LPCOLLISIONEVENT e = SweptAABBEx(coObjects->at(i));

		if (e->t > 0 && e->t <= 1.0f )
			coEvents.push_back(e);
		else
			delete e;
	}

	std::sort(coEvents.begin(), coEvents.end(), CCollisionEvent::compare);
}

void CGameObject::FilterCollision(vector<LPCOLLISIONEVENT>& coEvents, vector<LPCOLLISIONEVENT>& coEventsResult, float & min_tx, float & min_ty, float & nx, float & ny)
{
	min_tx = 1.0f;
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	nx = 0.0f;
	ny = 0.0f;

	coEventsResult.clear();

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT c = coEvents[i];

		if (c->t < min_tx && c->nx != 0) {
			min_tx = c->t; nx = c->nx; min_ix = i;
		}

		if (c->t < min_ty  && c->ny != 0) {
			min_ty = c->t; ny = c->ny; min_iy = i;
		}
	}

	if (min_ix >= 0) coEventsResult.push_back(coEvents[min_ix]);
	if (min_iy >= 0) coEventsResult.push_back(coEvents[min_iy]);
}

void CGameObject::AddAnimation(int tag,int index)
{
	LPANIMATION ani = Animations::GetInstance()->Get(tag,index);
	ani->SetEndAniFalse();
	ani->currentFrame = -1;
	animations.push_back(ani);
}
CGameObject::~CGameObject()
{
}
