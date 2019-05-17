#pragma once
#include "Camera.h"
class BumperCamera : public Camera
{
public:
	BumperCamera(Object* target);
	~BumperCamera();
	virtual void Update(float deltaTime) override;
};

