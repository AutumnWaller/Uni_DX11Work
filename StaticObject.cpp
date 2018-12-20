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

void StaticObject::MovePosition(float x, float y, float z)
{
	*_pPosition = { _pPosition->x + x, _pPosition->y + y, _pPosition->z + z };
}

void StaticObject::SetRotation(int x, int y, int z)
{
	XMStoreFloat4x4(&world, XMMatrixRotationX(x) * XMMatrixRotationY(y) * XMMatrixRotationZ(z));
}

void StaticObject::Initialise()
{
	_pPosition = nullptr;
}

void StaticObject::Update(float time) {
	DirectX::XMStoreFloat4x4(&world, XMMatrixTranslation(_pPosition->x, _pPosition->y, _pPosition->z));
}

void StaticObject::Cleanup()
{
	if (_pPosition) delete _pPosition;
	_pPosition = nullptr;
}
