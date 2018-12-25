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
	DirectX::XMStoreFloat4x4(&view, XMMatrixLookToLH(XMLoadFloat4(_pEye), XMLoadFloat4(_pAt), XMLoadFloat4(_pUp)));
}

void Camera::LookAt()
{
	DirectX::XMStoreFloat4x4(&view, XMMatrixLookAtLH(XMLoadFloat4(_pEye), XMLoadFloat4(_pAt), XMLoadFloat4(_pUp)));
}



void Camera::FollowObject(Object *object)
{
	_pTarget = object;
}

XMMATRIX Camera::Rotate()
{
	XMMATRIX viewMat = XMLoadFloat4x4(&view);
	XMMATRIX iViewMat = XMMatrixInverse(&XMMatrixDeterminant(viewMat), viewMat);
	XMVECTOR posVec = XMLoadFloat3(&MathsFunctions::AddFloats(*_pTarget->GetPosition(), *_pTarget->GetForward()));

	return XMMatrixRotationAxis(posVec, GetRotation()->y * _pTarget->GetRotation()->y);
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
}

void Camera::Update(float time)
{

	if (_pTarget) {
		XMFLOAT3 *_pTFor = _pTarget->GetForward();
		XMFLOAT3 *_pTPos = _pTarget->GetPosition();
		XMFLOAT3 *_pTRot = _pTarget->GetRotation();

		XMVECTOR *tPos = &XMLoadFloat3(_pTPos);

		XMVECTOR *tFor = &XMLoadFloat3(_pTFor);
		XMVECTOR *tRot = &XMLoadFloat3(_pTRot);
		SetPosition(_pTPos->x - _pTFor->x, _pTPos->y + (_pUp->y), _pTPos->z - _pTFor->z);
		SetRotation(_pTRot->x, _pTRot->y, _pTRot->z);

		//XMStoreFloat4x4(&world,XMMatrixTranspose( XMMatrixScaling(_pScale->x, _pScale->y, _pScale->z) * XMMatrixRotationX(_pTRot->x) * XMMatrixRotationY(_pTRot->y) * XMMatrixRotationZ(_pTRot->z)* XMMatrixRotationX(_pRotation->x) * XMMatrixRotationY(_pRotation->y) * XMMatrixRotationZ(_pRotation->z) * XMMatrixTranslation(_pPosition->x, _pPosition->y, _pPosition->z) ) );
		
		XMStoreFloat4x4(&view, XMMatrixLookAtLH(XMLoadFloat4(_pEye), XMLoadFloat4(_pAt), XMLoadFloat4(_pUp)));



	}

}

Camera::~Camera()
{
	delete _pEye, _pAt, _pUp, _pForward;
}
