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

void Camera::SetForward(int amount)
{
	_pForward->z += amount;
	_pAt->z += amount;
	LookTo();
}

void Camera::MoveForward(int amount)
{
	_pEye->z += amount;
	_pAt->z += amount;
	LookAt();
}

void Camera::MoveRight(int amount)
{
	_pEye->x += amount;
	_pAt->x += amount;
	LookAt();
}

void Camera::MoveUp(int amount)
{
	_pEye->y += amount;
	_pAt->y += amount;
	_pUp->y += amount;
	LookAt();
}

void Camera::Rotate(float angle)
{
	XMStoreFloat4(_pAt, XMQuaternionRotationAxis(XMLoadFloat4(_pAt), angle));
	XMStoreFloat4(_pEye, XMQuaternionRotationAxis(XMLoadFloat4(_pEye), angle));
	XMStoreFloat4(_pUp, XMQuaternionRotationAxis(XMLoadFloat4(_pUp), angle));
}




Camera::~Camera()
{
	delete _pEye, _pAt, _pUp, _pForward;
}
