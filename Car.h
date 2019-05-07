#pragma once
#include "Vector.h"
#include "AppTime.h"
#include "PhysicalObject.h"
class Car : public PhysicalObject
{
private:
	void SetVelocity(float amount);

	float velocity = 0;
	float maxVelocity = 10;

	float acceleration = 2.0f;

	float boostAcceleration = 5.0f;
	int boostAmount = 100;
	float maxBoostVelocity = 30.0f;
	const int boostTimer = 3;
public:
	virtual void Turn(float amount) override;
	void Drive(float deltaTime);
	void ChargeBoost();
	void Boost(float deltaTime);
	//void Accelerate(float deltaTime);
	//void Decelerate(float deltaTime);
	virtual void Update(float deltaTime) override;
	Car();
	~Car();
};

