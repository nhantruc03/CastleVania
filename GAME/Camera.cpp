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
	inzone1 = true;
	inzone2 = false;
	inzone3 = false;
	inzoneBoss = false;
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
		CamBound.top = SCREEN_HEIGHT-6 + BOARD_HEIGHT;
	}
	else
		CamBound.top = BOARD_HEIGHT;
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
		/*if (camPosition.x + camWidht / 2 > 5648)
		{
			camPosition = D3DXVECTOR3(5648 - camWidht / 2, 0, 0);
		}*/
		if (inzone1)
		{
			if (camPosition.x + camWidht / 2 > 3088)
			{
				camPosition = D3DXVECTOR3(3088- camWidht / 2, 0, 0);
			}
		}
		if (inzone2)
		{
			if (camPosition.x - camWidht / 2 < 3072)
			{
				camPosition = D3DXVECTOR3(3072 + camWidht / 2, 0, 0);
			}
			if (camPosition.x + camWidht / 2 > 4112)
			{
				camPosition= D3DXVECTOR3(4112 - camWidht / 2, 0, 0);
			}
		}
		if (movedownstair)
		{
			inzone2 = false;
			if (camPosition.x - camWidht / 2 < 3072)
			{
				camPosition = D3DXVECTOR3(3072+camWidht / 2, SCREEN_HEIGHT-6, 0);
			}
			if (camPosition.x + camWidht / 2 > 4112)
			{
				camPosition = D3DXVECTOR3(4112 - camWidht / 2, SCREEN_HEIGHT-6, 0);
			}
		}
		if (inzone3)
		{
			if (camPosition.x - camWidht / 2 < 4096)
			{
				camPosition = D3DXVECTOR3(4096 + camWidht / 2, 0, 0);
			}
			if (camPosition.x + camWidht / 2 > 5648)
			{
				inzoneBoss = true;
				camPosition = D3DXVECTOR3(5648 - camWidht / 2, 0, 0);
			}
		}
		if (inzoneBoss)
		{
			inzone3 = false;
			if (camPosition.x - camWidht / 2 < 5136)
			{
				camPosition = D3DXVECTOR3(5136 + camWidht / 2, 0, 0);
			}
			if (camPosition.x + camWidht / 2 > 5648)
			{
				inzoneBoss = true;
				camPosition = D3DXVECTOR3(5648 - camWidht / 2, 0, 0);
			}
		}
	}
}

Camera::~Camera()
{
}
