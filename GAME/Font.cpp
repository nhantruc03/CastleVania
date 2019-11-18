#include "Font.h"
Font::Font()
{
	tag = TAG_FONT;
	x = SCREEN_WIDTH / 2;
	y = 40;
}

void Font::update()
{
}

void Font::Draw(float x, float y, string  s)
{
	for (UINT i = 0; i < s.size(); i++)
	{
		if (s[i] == ' ')
			continue;
		if (s[i] >= 'A' && s[i] <= 'Z')
		{
			sprite=Sprites::GetInstance()->Get(tag,s[i] - 'A'); // cac ki tu duoc chuyen sang so trong bang ASCII, nho nhat trong ki tu in hoa la A
		}
		else
			if (s[i] >= '0' && s[i] <= '9')
			{
				int temp = s[i] - '0' + 26;
				sprite = Sprites::GetInstance()->Get(12,s[i] - '0' + 26); // trong list sprite co 26 ki tu chu, bat dau tu 0 nen 26 la so dau tien: 0
			}
			else
				sprite = Sprites::GetInstance()->Get(tag,36);
		sprite->Draw(x +i*15 , y);
	}
}


Font::~Font()
{
}
