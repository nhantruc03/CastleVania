#pragma once
#include<d3dx9.h>
#include<d3d9.h>
#include"GameGlobal.h"
class Camera
{
	static Camera* instance;
private:


public:
	bool inzone2;
	int camWidht, camHeight;
	D3DXVECTOR3 camPosition;
	static Camera* GetInstance();
	Camera(int width,int height);
	RECT GetBound();
	int GetWidth() { return camWidht; };
	int GetHeight() { return camHeight; };
	void SetPosition(float cx,float cy);
	D3DXVECTOR3 GetPosition() { return camPosition; };
	bool IsContain(RECT a);
	void Update(int maplevel);
	bool movedownstair;


	~Camera();
};

