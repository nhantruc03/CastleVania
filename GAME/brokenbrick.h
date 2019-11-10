#include"effect.h"
class brokenbrick :public Effect
{

public:
	brokenbrick(float x, float y, int model)
	{
		tag = TAG_EFFECT;
		type = TYPE_EFFECT_BROKENBRICK;
		this->x = x;
		this->y = y;
		width = 18;
		height = 23;
		isDead = false;
		effect = Sprites::GetInstance()->Get(tag, type);
		switch (model)
		{
		case 1: // trai
		{
			vx =  -0.07f;
			vy = -0.15f;
			break;
		}

		case 2:// phải
		{
			vx = 0.07f;
			vy = -0.1f;
			break;
		}

		case 3:// trai
		{
			vx = -0.03f;
			vy = -0.12f;
			break;	}

		case 4:// phải
		{
			vx = 0.07f;
			vy = -0.2f;
			break;
		}
		}
	}
};