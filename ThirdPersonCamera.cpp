#include "ThirdPersonCamera.h"



ThirdPersonCamera::~ThirdPersonCamera()
{
	delete _pEye, _pAt, _pForward, _pUp;
}


ThirdPersonCamera::ThirdPersonCamera(Object * target)
{
	Camera();
	_pTarget = target;
	_pEye->y = 3;
}

void ThirdPersonCamera::Update(float deltaTime)
{
	if (_pTarget) {
		XMFLOAT3 *_pTFor = &_pTarget->GetForward().ToXMFLOAT3();
		XMFLOAT3 *_pTPos = &_pTarget->GetPosition().ToXMFLOAT3();


		_pEye->x = (-_pTFor->x * 3) + _pTPos->x;
		_pEye->z = (-_pTFor->z * 3) + _pTPos->z;
		_pAt->x = (_pTFor->x) + _pTPos->x;
		_pAt->z = (_pTFor->z) + _pTPos->z;
		int n = 10;
		if (_pAt->x > 0)
			_pAt->x + n;
		else
			_pAt->x - n;

		if (_pAt->z > 0)
			_pAt->z + n;
		else
			_pAt->z - n;

		XMStoreFloat4x4(&view, XMMatrixLookAtLH(XMLoadFloat4(_pEye), XMLoadFloat4(_pAt), XMLoadFloat4(_pUp)));

	}
	Camera::Update(deltaTime);
}
