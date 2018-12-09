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

void Camera::SetForward(int amountToIncrease)
{
	_pForward->z += amountToIncrease;
	LookTo();
}

void Camera::MoveForward(int amount)
{
	_pEye->z += amount;

	LookAt();
}


Camera::~Camera()
{
	delete _pEye, _pAt, _pUp;
}
