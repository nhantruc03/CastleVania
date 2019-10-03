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
	camWidht = width;
	camHeight = height;

	camPosition = D3DXVECTOR3(0, 0, 0);
}

RECT Camera::GetBound()
{
	RECT CamBound;
	CamBound.left = camPosition.x - camWidht / 2;
	CamBound.top = 0;
	CamBound.right = CamBound.left + camWidht;
	CamBound.bottom = CamBound.top + camHeight;
	return CamBound;
}

void Camera::SetPosition(float cx, float cy)
{
	camPosition = D3DXVECTOR3(cx, cy, 0);
}

bool Camera::IsContain(RECT a, RECT b)
{
	if (a.left > b.right || a.top > b.bottom || a.bottom < b.top || a.right < b.left)
	{
		return false;
	}
	return true;
}

void Camera::Update()
{
	if (camPosition.x - camWidht / 2 < 0)
	{
		camPosition = D3DXVECTOR3(camWidht / 2, 0, 0);
	}
}

Camera::~Camera()
{
}
