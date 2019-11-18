#include"effect.h"
class burn :public Effect
{

public:
	int model;
	burn(float x, float y, int model)
	{
		tag = TAG_EFFECT;
		type = TYPE_EFFECT_BURN;
		this->x = x;
		this->y = y;
		width = 32;
		height = 18;
		isDead = false;
		this->model = model;
		if (model == 0)
		{
			animation = Animations::GetInstance()->Get(tag, 0);
		}
		else
			animation = Animations::GetInstance()->Get(tag, 1);

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