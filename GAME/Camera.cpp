#include "Camera.h"

Camera* Camera::instance = NULL;

Camera * Camera::GetInstance()
{
	if (instance == NULL)
		instance = new Camera(SCREEN_WIDTH,SCREEN_HEIGHT);
	return instance;
}

Camera::Camera(int width, int height)
{
	inzone2 = false;
	movedownstair = false;
	camWidht = width;
	camHeight = height;
	camPosition = D3DXVECTOR3(0, 0, 0);
}

RECT Camera::GetBound()
{
	RECT CamBound;
	
	CamBound.left = camPosition.x - camWidht / 2;
	if (movedownstair)
	{
		CamBound.top = 384;
	}
	else
		CamBound.top = 0;
	CamBound.right = CamBound.left + camWidht;
	CamBound.bottom = CamBound.top + camHeight;
	return CamBound;
}

void Camera::SetPosition(float cx, float cy)
{
	camPosition = D3DXVECTOR3(cx, cy, 0);
}

bool Camera::IsContain(RECT a)
{
	if (a.left > GetBound().right || a.top > GetBound().bottom || a.bottom < GetBound().top || a.right < GetBound().left)
	{
		return false;
	}
	return true;
}

void Camera::Update(int maplevel)
{
	if (camPosition.x - camWidht / 2 < 0)
	{
		camPosition = D3DXVECTOR3(camWidht / 2, 0, 0);
	}
	if (maplevel == 1)
	{
		if (camPosition.x + camWidht / 2 > 1552)
		{
			camPosition = D3DXVECTOR3(1552 - camWidht / 2, 0, 0);
		}
	}
	else
	{
		if (inzone2)
		{
			if (camPosition.x - camWidht / 2 < 3088)
			{
				camPosition = D3DXVECTOR3(3088 + camWidht / 2, 0, 0);
			}
		}
		if (movedownstair)
		{
			inzone2 = false;
			if (camPosition.x - camWidht / 2 < 3072)
			{
				camPosition = D3DXVECTOR3(3072+camWidht / 2, -384, 0);
			}
			if (camPosition.x + camWidht / 2 > 4112)
			{
				camPosition = D3DXVECTOR3(4112 - camWidht / 2, -384, 0);
			}
		}
	}
}

Camera::~Camera()
{
}
