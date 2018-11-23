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
	XMFLOAT4X4 *_pEye;
	XMFLOAT4X4 *_pAt;
	XMFLOAT4X4 *_pUp;
public:
	Camera(XMVECTOR _Eye, XMVECTOR _At, XMVECTOR _Up);
	~Camera();
	XMFLOAT4X4* GetEye() { return _pEye; }
	XMFLOAT4X4* GetAt() { return _pAt; }
	XMFLOAT4X4* GetUp() { return _pUp; }
};

