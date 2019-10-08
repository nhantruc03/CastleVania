#pragma once
class Weapon :public CGameObject
{
protected:
	CAnimation* animation;
public:
	//virtual void Update(float dt) {};
	Weapon()
	{
		tag = TAG_WEAPON;
	}
	virtual void Render()
	{
		float x = this->x;
		float y = this->y;
		animation->Render(x, y);
	}
	virtual void Update(float dt)
	{
		animation->isreverse = this->isReverse;
	}
};