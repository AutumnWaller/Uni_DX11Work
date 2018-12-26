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

static float timer = 0;




void StaticObject::SetPosition(float x, float y, float z)
{
	*_pPosition = { x, y, z };
}

void StaticObject::SetPosition(XMFLOAT3 xyz)
{
	*_pPosition = xyz;
}

void StaticObject::SetScale(float x, float y, float z)
{
	*_pScale = { x, y, z };
}

void StaticObject::MovePosition(float x, float y, float z)
{
	*_pPosition = { _pPosition->x + x, _pPosition->y + y, _pPosition->z + z };
}

void StaticObject::MovePosition(XMFLOAT3 xyz)
{
	*_pPosition = xyz;
}

void StaticObject::SetRotation(float x, float y, float z)
{
	*_pRotation = { x, y, z };
}

void StaticObject::SetRotation(XMFLOAT3 xyz)
{
	*_pRotation = { xyz };
}

void StaticObject::MoveRotation(float x, float y, float z)
{
	*_pRotation = { _pRotation->x += x, _pRotation->y += y, _pRotation->z += z };
}

void StaticObject::SetForward(float x, float y, float z)
{
	*_pForward = { x, y, z };
}

void StaticObject::MoveForward(float x, float y, float z)
{
	*_pForward = { _pForward->x + x, _pForward->y + y, _pForward->z + z };
}

void StaticObject::Turn(float amount)
{
	if (amount == 0)
		return;
	if (amount > 0) {
		if (_pRotation->y >= XM_PI * 2)
			_pRotation->y = 0;
	}
	else if (amount < 0) {
		if (_pRotation->y <= -(XM_PI * 2))
			_pRotation->y = 0;
	}

	MoveRotation(0, amount, 0);
	float rot = _pRotation->y;
	SetForward(MathsFunctions::Normalise(sin(rot)), 0, MathsFunctions::Normalise(cos(rot)));
}

void StaticObject::Initialise()
{
	_pPosition = nullptr;
	_pScale = new XMFLOAT3(1, 1, 1);
	_pRotation = new XMFLOAT3(0, 0, 0);
	_pForward = new XMFLOAT3(0, 0, 1);
}



void StaticObject::Update(float time) {
	DirectX::XMStoreFloat4x4(&world, XMMatrixScaling(_pScale->x, _pScale->y, _pScale->z) * XMMatrixRotationX(_pRotation->x) * XMMatrixRotationY(_pRotation->y) * XMMatrixRotationZ(_pRotation->z) * XMMatrixTranslation(_pPosition->x, _pPosition->y, _pPosition->z));

}

void StaticObject::Cleanup()
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
