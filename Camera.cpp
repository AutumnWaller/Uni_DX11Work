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



void Camera::FollowObject(Object *object)
{
	_pTarget = object;
}

void Camera::Rotate(float angle)
{

	FXMVECTOR rotation;
	XMMatrixRotationAxis(rotation, angle);

	//if (angle > 0)
	//	_pAt->x = _pAt->y, _pAt->y = _pAt->z, _pAt->z = _pAt->w;
	//else
	//	_pAt->z = _pAt->y, _pAt->y = _pAt->x, _pAt->x = _pAt->w;
	//XMStoreFloat4x4(&view, XMMatrixRotationAxis(XMLoadFloat4(_pAt), XMConvertToRadians(angle)));
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

void Camera::Update(float time)
{

	StaticObject::Update(time);
	if (_pTarget) {
		XMFLOAT3 *tPos = _pTarget->GetPosition();
		SetPosition(tPos->x, tPos->y + _pUp->y, tPos->z);
		DirectX::XMStoreFloat4x4(&view, XMMatrixLookAtLH(XMLoadFloat4(_pEye), XMLoadFloat3(_pTarget->GetPosition()), XMLoadFloat4(_pUp)));
	}
}

Camera::~Camera()
{
	delete _pEye, _pAt, _pUp, _pForward;
}
