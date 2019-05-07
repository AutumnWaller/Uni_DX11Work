#pragma once

#include <DirectXMath.h>
using namespace DirectX;
class Transform
{
protected:
	XMFLOAT4X4 world;
	XMFLOAT3* _pPosition = { new XMFLOAT3(0, 0, 0) };
	XMFLOAT3* _pScale = { new XMFLOAT3(1, 1, 1) };
	XMFLOAT3* _pRotation = { new XMFLOAT3(0, 0, 0) };
	XMFLOAT3* _pForward = { new XMFLOAT3(0, 0, 0) };
public:
	Transform();
	Transform(XMFLOAT3 position);

	XMFLOAT3* GetPosition() { return _pPosition; };
	virtual void SetPosition(float x, float y, float z);
	virtual void SetPosition(XMFLOAT3 xyz);

	void SetScale(float x, float y, float z);
	virtual void Update(float deltaTime);


	~Transform();
};

