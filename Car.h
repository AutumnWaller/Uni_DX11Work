#pragma once
#include "Object.h"
#include "AppTime.h"
class Car : public Object
{
private:
	void SetVelocity(float amount);

	float velocity = 0;
	float maxVelocity = 20;

	float acceleration = 2.0f;
public:
	virtual void Turn(float amount) override;
	void Drive(float deltaTime);
	void Accelerate(float deltaTime);
	void Decelerate(float deltaTime);
	virtual void Update(float deltaTime) override;
	Car();
	~Car();
};

