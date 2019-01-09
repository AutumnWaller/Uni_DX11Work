#pragma once
#include "Camera.h"
#include "Object.h"
class ThirdPersonCamera : public Camera
{
public:
	ThirdPersonCamera(Object* target);
	~ThirdPersonCamera();
	virtual void Update(float deltaTime) override;
};

