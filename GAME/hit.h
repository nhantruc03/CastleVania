#include"effect.h"
#define TIME_TO_SHOW_EFFECT 200
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
		timetoshoweffect = TIME_TO_SHOW_EFFECT;
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