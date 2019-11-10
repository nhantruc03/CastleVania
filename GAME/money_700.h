#include"effect.h"
class money_700:public Effect
{

public:
	float timetoshoweffect;
	money_700(float x, float y)
	{
		tag = TAG_EFFECT;
		type = TYPE_EFFECT_700;
		this->x = x;
		this->y = y;
		width = 32;
		height = 18;
		isDead = false;
		effect = Sprites::GetInstance()->Get(tag, type);
		timetoshoweffect = 1000;
	}
	void Update(DWORD dt)
	{
		timetoshoweffect -= dt;
		if (timetoshoweffect <= 0)
		{
			this->isDead = true;
		}
	}
};