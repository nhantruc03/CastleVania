#include"effect.h"
class burn :public Effect
{

public:
	burn(float x, float y)
	{
		tag = TAG_EFFECT;
		type = TYPE_EFFECT_BURN;
		this->x = x;
		this->y = y;
		width = 32;
		height = 18;
		isDead = false;
		animation = Animations::GetInstance()->Get(tag, type);
	}
	void Update(DWORD dt)
	{
		animation->Update();
		if (animation->CheckEndAni())
		{
			animation->SetEndAniFalse();
			animation->currentFrame = -1;
			this->isDead = true;
		}
	}
	void Render()
	{
		animation->Render(x, y);
	}
};