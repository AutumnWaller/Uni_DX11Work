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

	XMFLOAT3 *GetPosition() { return _pPosition; };
	virtual void SetPosition(float x, float y, float z);
	virtual void MovePosition(float x, float y, float z);

	virtual void SetScale(float x, float y, float z);
	void SetRotation(float x, float y, float z);
	void MoveRotation(float x, float y, float z);
	void Initialise();
protected:

	virtual void Cleanup();

	XMFLOAT4X4 world;
	XMFLOAT3 *_pPosition;
	XMFLOAT3 *_pScale;
	XMFLOAT3 *_pRotation;
};

