#include"effect.h"
class hit :public Effect
{

public:
	float timetoshoweffect;
	hit(float x, float y)
	{
		tag = TAG_EFFECT;
		type = TYPE_EFFECT_HIT;
		this->x = x;
		this->y = y;
		width = 32;
		height = 18;
		isDead = false;
		effect = Sprites::GetInstance()->Get(tag, type);
		timetoshoweffect = 200;
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