#pragma once
#include "Camera.h"
class ThirdPersonCamera : public Camera
{
public:
	ThirdPersonCamera(Object* target);
	~ThirdPersonCamera();
	virtual void Update(float deltaTime) override;
};

