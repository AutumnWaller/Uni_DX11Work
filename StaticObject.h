#pragma once

#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;

class StaticObject
{
public:
	StaticObject(XMFLOAT3 *position);
	StaticObject();
	~StaticObject();

	virtual void Update(float time);
	virtual void SetPosition(float x, float y, float z);
	virtual void MovePosition(float x, float y, float z);
	void SetRotation(int x, int y, int z);
	void Initialise();
protected:

	virtual void Cleanup();

	XMFLOAT4X4 world;
	XMFLOAT3 *_pPosition;
};

