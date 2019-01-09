#pragma once

#include <d3d11.h>
#include "MathsFunctions.h"
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
	virtual void SetPosition(XMFLOAT3 xyz);

	virtual void MovePosition(float x, float y, float z);
	virtual void MovePosition(XMFLOAT3 xyz);

	virtual void SetScale(float x, float y, float z);

	virtual void SetRotation(float x, float y, float z);
	virtual void SetRotation(XMFLOAT3 xyz);
	virtual void MoveRotation(float x, float y, float z);
	XMFLOAT3 *GetRotation() { return _pRotation; }

	virtual void SetForward(float x, float y, float z);
	virtual void MoveForward(float x, float y, float z);
	XMFLOAT3 *GetForward() { return _pForward; };


	virtual void Turn(float amount);

	virtual void Initialise();
protected:

	virtual void Cleanup();

	float turnSpeed = 1; 

	XMFLOAT4X4 world;
	XMFLOAT3 *_pPosition;
	XMFLOAT3 *_pScale;
	XMFLOAT3 *_pRotation;
	XMFLOAT3 *_pForward;
};

