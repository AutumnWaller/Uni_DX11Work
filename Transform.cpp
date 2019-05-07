#include "Transform.h"



Transform::Transform()
{
}

Transform::Transform(XMFLOAT3 position)
{
	SetPosition(position);
}

void Transform::SetPosition(float x, float y, float z)
{
	_pPrevPosition = _pPosition;

	*_pPosition = { x, y, z };
}

void Transform::SetPosition(XMFLOAT3 xyz)
{
	_pPrevPosition = _pPosition;
	*_pPosition = xyz;
}

void Transform::SetScale(float x, float y, float z)
{
	*_pScale = { x, y, z };
}

void Transform::Update(float deltaTime)
{
	DirectX::XMStoreFloat4x4(&world, XMMatrixScaling(_pScale->x, _pScale->y, _pScale->z) * XMMatrixRotationX(_pRotation->x) * XMMatrixRotationY(_pRotation->y) * XMMatrixRotationZ(_pRotation->z) * XMMatrixTranslation(_pPosition->x, _pPosition->y, _pPosition->z));
}

Transform::~Transform()
{
	if (_pPosition) delete _pPosition;
	_pPosition = nullptr;

	if (_pScale) delete _pScale;
	_pScale = nullptr;

	if (_pRotation) delete _pRotation;
	_pRotation = nullptr;

	if (_pForward) delete _pForward;
	_pForward = nullptr;
}
