#include "Car.h"


using namespace Vector;
void Car::Turn(float amount)
{
	if (velocity != 0) {
		PhysicalObject::Turn(amount * turnSpeed);
		if (velocity > maxVelocity)
			Decelerate(amount);
	}
}

void Car::Drive(float deltaTime)
{
	_massAggregate->AddForce(Vector3(1 * deltaTime, 0, 0));
}

void Car::ChargeBoost()
{
	boostAmount = 100;
}

void Car::Boost(float deltaTime)
{
	if (boostAmount > 0) {
		boostAmount -= (boostTimer * deltaTime);
		if (velocity < maxBoostVelocity) {
			AppTime::Timer(deltaTime, 0.2f, velocity, boostAcceleration);
		}
	}
}

void Car::SetVelocity(float amount)
{
	velocity = amount;
}

void Car::Update(float deltaTime)
{
	_massAggregate->Update(deltaTime);
	_massAggregate->Move(this, deltaTime);
	PhysicalObject::Update(deltaTime);
}

Car::Car()
{
	_pModelPath = "Models/Car.obj";
	_pTexturePath = L"Textures/black.dds";
	type = StaticStructs::CAR;
	PhysicalObject();
}


Car::~Car()
{
}
