#include "Camera.h"




Camera::Camera(XMVECTOR _Eye, XMVECTOR _At, XMVECTOR _Up, XMVECTOR _Forward, int windowWidth, int windowHeight)
{
	_pEye = new XMFLOAT4();
	_pAt = new XMFLOAT4();
	_pUp = new XMFLOAT4();
	_pForward = new XMFLOAT4();
	DirectX::XMStoreFloat4(_pEye, _Eye);
	DirectX::XMStoreFloat4(_pAt, _At);
	DirectX::XMStoreFloat4(_pUp, _Up);
	DirectX::XMStoreFloat4(_pForward, _Forward);

	LookAt();
	
	// Initialize the projection matrix
	DirectX::XMStoreFloat4x4(&projection, XMMatrixPerspectiveFovLH(XM_PIDIV2, windowWidth / (FLOAT)windowHeight, 0.01f, 100.0f));

}

void Camera::LookTo() {
	DirectX::XMStoreFloat4x4(&view, XMMatrixLookToLH(XMLoadFloat4(_pEye), XMLoadFloat4(_pForward), XMLoadFloat4(_pUp)));
}

void Camera::LookAt()
{
	DirectX::XMStoreFloat4x4(&view, XMMatrixLookAtLH(XMLoadFloat4(_pEye), XMLoadFloat4(_pAt), XMLoadFloat4(_pUp)));
}

void Camera::Rotate(float angle)
{
	XMStoreFloat4(_pAt, XMQuaternionRotationAxis(XMLoadFloat4(_pAt), angle));
	XMStoreFloat4(_pEye, XMQuaternionRotationAxis(XMLoadFloat4(_pEye), angle));
	XMStoreFloat4(_pUp, XMQuaternionRotationAxis(XMLoadFloat4(_pUp), angle));
}

void Camera::SetPosition(float x, float y, float z)
{
	_pAt->x = x, _pAt->y = y, _pAt->z = z;
	_pEye->x = x, _pEye->y = y + 1, _pEye->z = z;
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

void Camera::Update(float time)
{
	StaticObject::Update(time);
}

Camera::~Camera()
{
	delete _pEye, _pAt, _pUp, _pForward;
}
