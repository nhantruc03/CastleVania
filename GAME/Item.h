#pragma once
#include"GameObject.h"
#include"Brick.h"
class Item:public CGameObject
{
protected:
	CSprite* sprite;
public:
	Item()
	{
		tag = TAG_ITEM;
		vy = 0.2f;
	}
	virtual void Render()
	{
		sprite->Draw(x, y);
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
	{
		CGameObject::Update(dt, coObjects);
		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();

		// turn off collision when die 
		CalcPotentialCollisions(coObjects, coEvents);
		// No collision occured, proceed normally
		if (coEvents.size() == 0)
		{
			y += dy;
		}
		else
		{
			float min_tx, min_ty, nx = 0, ny;

			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

			// block 
			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];

				if (dynamic_cast<CBrick *>(e->obj)) // if e->obj is Goomba 
				{
					y += min_ty * dy + ny * 0.1f;
					if (ny != 0) vy = 0;
				}

			}
		}
	}
};

