#include "MassAggregate.h"

using namespace DirectX;
using namespace Vector;
MassAggregate::MassAggregate()
{
	accumulatedForces.push_back(gravity);
}


MassAggregate::~MassAggregate()
{
}

void MassAggregate::SetCoefficient(float _coefficient)
{
	frictionCoefficient = _coefficient;
}

void MassAggregate::ApplyForces()
{
	for (int i = 0; i < accumulatedForces.size(); i++) {
		netForce->SetForceVector(netForce->GetForceVector() + accumulatedForces.at(i)->GetForceVector());
	}
	accumulatedForces.clear();
	//netForce->SetForceVector(Vector3(0));
}

void MassAggregate::CalculateAcceleration()
{
	acceleration->SetForceVector(netForce->GetForceVector() / mass);
}

void MassAggregate::CalculateVelocity(float deltaTime)
{
	velocity->SetForceVector(prevVelocity->GetForceVector() + (acceleration->GetForceVector() * deltaTime));
	AddForce(velocity);
}

void MassAggregate::CalculateGravity()
{
	gravity->SetForceVector(Vector3(0, (-9.81 * GetMass()), 0));
	AddForce(gravity);
}

void MassAggregate::CalculateFriction()
{
	Vector3 vForce = velocity->GetForceVector();
	friction->SetForceVector(Vector3(frictionCoefficient * -vForce.x, 0, frictionCoefficient * -vForce.z));
	MoveVelocity(friction->GetForceVector());
}

void MassAggregate::CalculateLaminarDrag()
{
	float airDensity = 1.2;
	Vector3 pressure = ((GetVelocity()->GetForceVector() * airDensity) * (GetVelocity()->GetForceVector() * airDensity)) * 0.5;
	//dragForce = (dragFactor * -1) * GetVelocity();
	AddForce(dragForce);
}

void MassAggregate::AddForce(Force* force)
{
	accumulatedForces.push_back(force);
}

void MassAggregate::AddThrust(Vector::Vector3 force)
{
	thrust->SetForceVector(force);
	AddForce(thrust);
}

void MassAggregate::MoveVelocity(Vector::Vector3 force)
{
	velocity->SetForceVector(velocity->GetForceVector() + force);
}

void MassAggregate::SetVelocity(Vector::Vector3 force)
{
	velocity->SetForceVector(force);
}

Vector::Vector3 MassAggregate::Move(Vector::Vector3 position, float deltaTime)
{


	if (position.y <= 0.5) {
		isGrounded = true;
		Bounce();
	}
	else {
		isGrounded = false;
	}

	Vector::Vector3 newPos = (((prevVelocity->GetForceVector() * deltaTime) + (acceleration->GetForceVector() / 2) * (deltaTime * deltaTime)));

	prevVelocity = velocity;
	netForce->SetForceVector(Vector3(0));

	return newPos;

}

void MassAggregate::Bounce()
{
	acceleration->SetForceVector(Vector3(acceleration->GetForceVector().x, acceleration->GetForceVector().y * -1.25, acceleration->GetForceVector().z));
}

void MassAggregate::Update(float deltaTime)
{
	CalculateGravity();
	ApplyForces();
	CalculateFriction();
	CalculateAcceleration();

}
