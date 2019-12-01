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
	if (camPosition.x - camWidht / 2 < ZONE_FULL_MAP_LEFT)
	{
		camPosition = D3DXVECTOR3(camWidht / 2, 0, 0);
	}
	if (maplevel == 1)
	{
		if (camPosition.x + camWidht / 2 > ZONE_FULL_MAP_RIGHT)
		{
			camPosition = D3DXVECTOR3(ZONE_FULL_MAP_RIGHT - camWidht / 2, 0, 0);
		}
	}
	else
	{
		if (inzone1)
		{
			if (camPosition.x + camWidht / 2 > ZONE_STAGE1_RIGHT)
			{
				camPosition = D3DXVECTOR3(ZONE_STAGE1_RIGHT - camWidht / 2, 0, 0);
			}
		}
		if (inzone2)
		{
			switch (movedownstair)
			{
			case true:
				if (camPosition.x - camWidht / 2 < ZONE_STAGE2_LEFT)
				{
					camPosition = D3DXVECTOR3(ZONE_STAGE2_LEFT + camWidht / 2, SCREEN_HEIGHT - 6, 0);
				}
				if (camPosition.x + camWidht / 2 > ZONE_STAGE2_RIGHT)
				{
					camPosition = D3DXVECTOR3(ZONE_STAGE2_RIGHT - camWidht / 2, SCREEN_HEIGHT - 6, 0);
				}
				break;
			case false:
				if (camPosition.x - camWidht / 2 < ZONE_STAGE2_LEFT)
				{
					camPosition = D3DXVECTOR3(ZONE_STAGE2_LEFT + camWidht / 2, 0, 0);
				}
				if (camPosition.x + camWidht / 2 > ZONE_STAGE2_RIGHT)
				{
					camPosition = D3DXVECTOR3(ZONE_STAGE2_RIGHT - camWidht / 2, 0, 0);
				}
				break;

			}
			
		}
		if (inzone3)
		{
			if (camPosition.x - camWidht / 2 < ZONE_STAGE3_LEFT)
			{
				camPosition = D3DXVECTOR3(ZONE_STAGE3_LEFT + camWidht / 2, 0, 0);
			}
			if (camPosition.x + camWidht / 2 > ZONE_STAGE3_RIGHT)
			{
				inzoneBoss = true;
				camPosition = D3DXVECTOR3(ZONE_STAGE3_RIGHT - camWidht / 2, 0, 0);
			}
		}
		if (inzoneBoss)
		{
			inzone3 = false;
			if (camPosition.x - camWidht / 2 < ZONE_BOSS_LEFT)
			{
				camPosition = D3DXVECTOR3(ZONE_BOSS_LEFT + camWidht / 2, 0, 0);
			}
			if (camPosition.x + camWidht / 2 > ZONE_BOSS_RIGHT)
			{
				inzoneBoss = true;
				camPosition = D3DXVECTOR3(ZONE_BOSS_RIGHT - camWidht / 2, 0, 0);
			}
		}
		
	}
}

Camera::~Camera()
{
}
