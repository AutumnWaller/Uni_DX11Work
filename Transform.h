#pragma once
#include "Vector.h"
#include "Collision.h"
#include <DirectXMath.h>
using namespace DirectX;
class Collision;
class Transform
{
protected:
	XMFLOAT4X4 world;
	Vector::Vector3 _pPosition = { Vector::Vector3(0, 0, 0) };
	Vector::Vector3 _pPrevPosition = { Vector::Vector3(0, 0, 0) };
	Vector::Vector3 _pScale = { Vector::Vector3(1, 1, 1) };
	Vector::Vector3 _pRotation = { Vector::Vector3(0, 0, 0) };
	Vector::Vector3 _pForward = { Vector::Vector3(0, 0, 0) };
	Collision* _pCollision = nullptr;
public:
	Transform();
	Transform(Vector::Vector3 position);

	Vector::Vector3 GetPosition() { return _pPosition; };
	Vector::Vector3 GetPrevPosition() { return _pPrevPosition; };
	virtual void SetStartingPosition(Vector::Vector3 xyz);
	virtual void MovePosition(float x, float y, float z);
	virtual void MovePosition(XMFLOAT3 xyz);

	virtual void SetPosition(float x, float y, float z);
	virtual void SetPrevPosition(Vector::Vector3 xyz);
	virtual void SetPosition(XMFLOAT3 xyz);
	virtual void SetPosition(Vector::Vector3 xyz);

	Collision* GetCollision() { return _pCollision; };

	void SetScale(float x, float y, float z);
	virtual void Update(float deltaTime);


	~Transform();
};

