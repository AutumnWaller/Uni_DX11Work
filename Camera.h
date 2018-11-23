#pragma once
#include <windows.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <directxcolors.h>

using namespace DirectX;

class Camera
{
private:
	XMFLOAT4X4 view;
	XMFLOAT4X4 projection;
	XMFLOAT4 *_pEye;
	XMFLOAT4 *_pAt;
	XMFLOAT4 *_pUp;
	XMFLOAT4 *_pForward;
public:
	Camera(XMVECTOR _Eye, XMVECTOR _At, XMVECTOR _Up, XMVECTOR _Forward, int windowWidth = 1280, int windowHeight = 720);
	~Camera();
	void LookTo();
	void LookAt();

	XMFLOAT4* GetEye() { return _pEye; }
	XMFLOAT4* GetAt() { return _pAt; }
	XMFLOAT4* GetUp() { return _pUp; }
	XMFLOAT4* GetForward() { return _pForward; }
	XMFLOAT4X4 GetViewMatrix() { return view; }
	XMFLOAT4X4 GetProjectionMatrix() { return projection; }

	void SetForward(int amountToIncrease);
	void MoveForward(int amount);
};

