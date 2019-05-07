#pragma once
#include "MathsFunctions.h"
#include <windows.h>
#include "Object.h"

#include <d3dcompiler.h>
#include <directxcolors.h>

class Camera : public Object
{
protected:
	float movementSpeed = 100;
	XMFLOAT4X4 view;
	XMFLOAT4X4 projection;
	XMFLOAT4 *_pEye;
	XMFLOAT4 *_pAt;
	XMFLOAT4 *_pUp;
	XMFLOAT4 *_pCamForward;
	Object *_pTarget;
public:
	Camera(XMVECTOR _Eye = XMVECTOR{0, 0, 0}, XMVECTOR _At = XMVECTOR{ 1, 1, 1 }, int windowWidth = 1280, int windowHeight = 720);
	~Camera();
	void LookTo();
	void LookAt();

	float GetMovementSpeed() { return movementSpeed; }
	XMFLOAT4* GetEye() { return _pEye; }
	XMFLOAT4* GetAt() { return _pAt; }
	XMFLOAT4* GetUp() { return _pUp; }
	XMFLOAT4* GetForward4() { return _pCamForward; }
	XMFLOAT4X4 GetViewMatrix() { return view; }
	XMFLOAT4X4 GetProjectionMatrix() { return projection; }

	void FollowObject(Object *object);
	virtual void SetPosition(float x, float y, float z) override;
	virtual void MovePosition(float x, float y, float z) override;
	virtual void SetRotation(float x, float y, float z) override;
	virtual void Update(float time) override;
};

