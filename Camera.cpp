#include "Camera.h"




Camera::Camera(XMVECTOR _Eye, XMVECTOR _At, int windowWidth, int windowHeight)
{
	_pTarget = nullptr;

	_pEye = new XMFLOAT4();
	_pAt = new XMFLOAT4();
	_pUp = new XMFLOAT4(0, 1, 0, 0);
	_pForward = new XMFLOAT4(0, 0, 1, 0);

	DirectX::XMStoreFloat4(_pEye, _Eye);
	DirectX::XMStoreFloat4(_pAt, _At);
	
	DirectX::XMStoreFloat3(StaticObject::_pForward, DirectX::XMLoadFloat3(new XMFLOAT3(0, 0, 1)));
	
	DirectX::XMStoreFloat4x4(&projection, XMMatrixPerspectiveFovLH(XM_PIDIV2, windowWidth / (FLOAT)windowHeight, 0.01f, 100.0f));
	LookAt();

}

void Camera::LookTo() {
	DirectX::XMStoreFloat4x4(&view, XMMatrixLookToLH(DirectX::XMLoadFloat4(_pEye), DirectX::XMLoadFloat4(_pAt), DirectX::XMLoadFloat4(_pUp)));
}

void Camera::LookAt()
{
	DirectX::XMStoreFloat4x4(&view, XMMatrixLookAtLH(DirectX::XMLoadFloat4(_pEye), DirectX::XMLoadFloat4(_pAt), DirectX::XMLoadFloat4(_pUp)));
}



void Camera::FollowObject(Object *object)
{
	_pTarget = object;
}

void Camera::SetPosition(float x, float y, float z)
{
	_pAt->x = x, _pAt->y = y, _pAt->z = z;
	_pEye->x = x, _pEye->y = _pAt->y + 1, _pEye->z = _pAt->z - 3;
	StaticObject::SetPosition(_pAt->x, _pAt->y, _pAt->z);
	LookAt();
}

void Camera::MovePosition(float x, float y, float z)
{
	_pAt->x += x, _pAt->y += y, _pAt->z += z;
	_pEye->x += x, _pEye->y += y, _pEye->z += z;
	StaticObject::MovePosition(x, y, z);
	LookAt();
}

void Camera::SetRotation(float x, float y, float z)
{
	_pRotation->x = x;
	_pRotation->y = y;
	_pRotation->z = z;
}

void Camera::Update(float time)
{
	DirectX::XMStoreFloat4x4(&world, XMMatrixTranspose( XMMatrixRotationX(_pRotation->x) * XMMatrixRotationY(_pRotation->y) * XMMatrixRotationZ(_pRotation->z) * XMMatrixTranslation(_pPosition->x, _pPosition->y, _pPosition->z) ) );
}

Camera::~Camera()
{
	delete _pAt, _pUp, _pForward;
}
