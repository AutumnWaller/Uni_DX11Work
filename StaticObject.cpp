#include "StaticObject.h"



StaticObject::StaticObject(XMFLOAT3 *position)
{
	Initialise();
	_pPosition = position;
}

StaticObject::StaticObject() {
	Initialise();
	_pPosition = new XMFLOAT3(0, 0, 0);
}

StaticObject::~StaticObject()
{
	Cleanup();
}

void StaticObject::SetPosition(float x, float y, float z)
{
	*_pPosition = { x, y, z };
}

void StaticObject::SetScale(float x, float y, float z)
{
	*_pScale = { x, y, z };
}

void StaticObject::MovePosition(float x, float y, float z)
{
	*_pPosition = { _pPosition->x + x, _pPosition->y + y, _pPosition->z + z };
}

void StaticObject::SetRotation(float x, float y, float z)
{
	*_pRotation = { x, y, z };
}

void StaticObject::MoveRotation(float x, float y, float z)
{
	*_pRotation = { _pRotation->x += x, _pRotation->y += y, _pRotation->z += z };
}

void StaticObject::Initialise()
{
	_pPosition = nullptr;
	_pScale = new XMFLOAT3(1, 1, 1);
	_pRotation = new XMFLOAT3(0, 0, 0);
}

void StaticObject::Update(float time) {
	DirectX::XMStoreFloat4x4(&world, XMMatrixScaling(_pScale->x, _pScale->y, _pScale->z) * (XMMatrixRotationX(_pRotation->x) * XMMatrixRotationY(_pRotation->y) * XMMatrixRotationZ(_pRotation->z)) * XMMatrixTranslation(_pPosition->x, _pPosition->y, _pPosition->z));
}

void StaticObject::Cleanup()
{
	if (_pPosition) delete _pPosition;
	_pPosition = nullptr;

	if (_pScale) delete _pScale;
	_pScale = nullptr;

	if (_pRotation) delete _pRotation;
	_pRotation = nullptr;

}
