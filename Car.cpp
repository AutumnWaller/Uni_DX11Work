#include "Car.h"


using namespace Vector;

Car::Car()
{
	_pModelPath = "Models/Car.obj";
	_pTexturePath = L"Textures/black.dds";
	SetForward(0, 0, 1);
	type = StaticStructs::CAR;
	PhysicalObject();
}

void Car::Turn(float amount)
{
	if (_massAggregate->GetVelocity() != 0) {
		PhysicalObject::Turn(amount * turnSpeed);
	}
}

void Car::Drive(float deltaTime)
{
	_massAggregate->AddForce((_pForward * deltaTime) * 500);
}

void Car::ChargeBoost()
{
	boostAmount = 100;
}

void Car::Boost(float deltaTime)
{

}

void Car::Update(float deltaTime)
{
	_massAggregate->Update(deltaTime);
	_massAggregate->Move(this, deltaTime);
	PhysicalObject::Update(deltaTime);
}




Car::~Car()
{
}
