#include"effect.h"
class steam :public Effect
{

public:
	steam(float x,float y, int model)
	{
		tag = TAG_EFFECT;
		type = TYPE_EFFECT_STEAM;
		this->x = x;
		this->y = y;
		width = 14;
		height = 28;
		isDead = false;
		effect = Sprites::GetInstance()->Get(tag, type);
		switch (model)
		{
		case 1:
			vy = -0.1f;
			vx = -0.04f;
			break;
		case 2:
			vy = -0.15f;
			vx = 0.0f;
			break;
		case 3:
			vy = -0.1f;
			vx = 0.07f;
			break;
		}
	}
};