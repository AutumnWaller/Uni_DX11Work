#include "Car.h"


using namespace Vector;

Car::Car()
{
	_pModelPath = "Models/Car.obj";
	_pTexturePath = L"Textures/black.dds";
	SetForward(0, 0, 1);
	_pMassAggregate->SetMass(500);
	_pMassAggregate->SetGravityScale(_pScale.y);
	_pMassAggregate->SetCoefficient(0.000057);
	type = StaticStructs::CAR;
	_pCollision->SetRadius(1);
	PhysicalObject();
}

void Car::Turn(float amount)
{
	if (_pMassAggregate->GetVelocity() != 0)
		PhysicalObject::Turn(amount);
}

void Car::Drive(float deltaTime)
{
	_pMassAggregate->MoveVelocity(Vector3((_pForward * deltaTime) * 10));
}

void Car::ChargeBoost()
{
	boostAmount = 100;
}

void Car::Boost(float deltaTime)
{

}

float carJumpDelay = -0.1f;

void Car::Jump(float deltaTime)
{
	if(isGrounded)
		_pMassAggregate->AddThrust(Vector3(0, 200 * _pMassAggregate->GetMass(), 0));
	else
	{
		if(boostAmount > 0)
			_pMassAggregate->AddThrust((GetForward() * 5) + (Vector3(0, 200 * _pMassAggregate->GetMass(), 0)));

	}
}

void Car::Update(float deltaTime)
{
	_pMassAggregate->Update(deltaTime);
	MovePosition(_pMassAggregate->Move(GetPosition(), deltaTime).ToXMFLOAT3());
	PhysicalObject::Update(deltaTime);
	if (GetPosition().y <= 0.5) {
		isGrounded = true;
	}
	else {
		isGrounded = false;
	}
}

void Car::CollisionHandling()
{
}




Car::~Car()
{
}
