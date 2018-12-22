#include "Car.h"



void Car::SetVelocity(float amount)
{
	velocity = amount;
}

void Car::TurnRight(float amount)
{
	if (amount == 0)
		return;
	if (amount < 0)
		amount *= -1;
	if (_pRotation->y > XM_PI * 2)
		_pRotation->y = 0;
	MoveRotation(0, amount, 0);
	float rot = _pRotation->y;
	//float x = 0, z = 0;
	//if (rot > 0 && rot <= XM_PI / 2) {
	//	x = sin(rot);
	//	z = 1 - x;
	//}
	//else if (rot > XM_PI / 2 && rot <= XM_PI) {
	//	z = sin(rot);
	//	z *= -1;
	//	x = 1 + z;
	//}
	//else if (rot > XM_PI && rot <= (3 / (2 * XM_PI)))
	//	x = -sin(rot);
	//else if (rot > (3 / (2 * XM_PI)) && rot <= (2 * XM_PI))
	//	x = -cos(rot);
	float x, z;
	SetForward(cos(rot) * cos(rot), 0, sin(rot));
}

void Car::TurnLeft(float amount)
{
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
