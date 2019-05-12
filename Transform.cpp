#include "Transform.h"

using namespace Vector;

Transform::Transform()
{
	SetPrevPosition(_pPosition);
	_pCollision = new Collision(this);
}

Transform::Transform(Vector3 position)
{
	SetPrevPosition(position);
	SetPosition(position);
}

void Transform::SetStartingPosition(Vector::Vector3 xyz)
{
	_pPrevPosition = xyz;
	_pPosition = _pPrevPosition;
}

void Transform::MovePosition(float x, float y, float z)
{
	_pPosition = { _pPosition.x + x, _pPosition.y + y, _pPosition.z + z };
}

void Transform::MovePosition(XMFLOAT3 xyz)
{
	_pPosition = Vector::Vector3(xyz.x, xyz.y, xyz.z);
}

void Transform::SetPosition(float x, float y, float z)
{
	_pPrevPosition = _pPosition;

	_pPosition = { x, y, z };
}

void Transform::SetPrevPosition(Vector::Vector3 xyz)
{
	_pPrevPosition = xyz;
}

void Transform::SetPosition(XMFLOAT3 xyz)
{
	_pPrevPosition = _pPosition;
	_pPosition = Vector3::ToVector3(xyz);
}

void Transform::SetPosition(Vector::Vector3 xyz)
{
	_pPrevPosition = _pPosition;
	_pPosition = xyz;
}

void Transform::SetScale(float x, float y, float z)
{
	_pScale = { x, y, z };
}

void Transform::Update(float deltaTime)
{
	DirectX::XMStoreFloat4x4(&world, XMMatrixScaling(_pScale.ToXMFLOAT3().x, _pScale.ToXMFLOAT3().y, _pScale.ToXMFLOAT3().z) * XMMatrixRotationX(_pRotation.ToXMFLOAT3().x) * XMMatrixRotationY(_pRotation.ToXMFLOAT3().y) * XMMatrixRotationZ(_pRotation.ToXMFLOAT3().z) * XMMatrixTranslation(_pPosition.ToXMFLOAT3().x, _pPosition.ToXMFLOAT3().y, _pPosition.ToXMFLOAT3().z));
}

Transform::~Transform()
{
}
