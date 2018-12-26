#include "Car.h"



void Car::Turn(float amount)
{
	if (velocity != 0)
		Object::Turn(amount * turnSpeed);
}

void Car::Drive(float deltaTime)
{
	MovePosition(_pForward->x * velocity * deltaTime, _pForward->y * velocity * deltaTime, _pForward->z * velocity * deltaTime);
}

void Car::Accelerate(float deltaTime)
{
	if (deltaTime > 0) {
		if (velocity < maxVelocity) {
			AppTime::Timer(deltaTime, 0.5f, velocity, acceleration);
		}
	}
	else if (deltaTime < 0) {
		if (velocity > -maxVelocity) {
			AppTime::Timer(-deltaTime, 0.5f, velocity, -acceleration);
		}
	}
}

void Car::Decelerate(float deltaTime)
{
	if (velocity > 0) {
		AppTime::Timer(deltaTime, 0.5f, velocity, -acceleration);
	}
	else if(velocity < 0) {
		AppTime::Timer(deltaTime, 0.5f, velocity, acceleration);
	}
}

void Car::SetVelocity(float amount)
{
	velocity = amount;
}

void Car::Update(float deltaTime)
{
	if (velocity > 0 && velocity < (maxVelocity * 0.5f)) {
		turnSpeed = 3.5f;
	}
	else if(velocity > (maxVelocity * 0.5f))
	{
		turnSpeed = 2;
	}
	Object::Update(deltaTime);
}

Car::Car()
{
	_pModelPath = "Models/Car.obj";
	_pTexturePath = L"Textures/black.dds";
	Object();
}


Car::~Car()
{
}
