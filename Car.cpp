#include "Car.h"



void Car::SetVelocity(float amount)
{
	velocity = amount;
}

void Car::Update(float deltaTime)
{
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
