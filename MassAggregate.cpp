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
	gravity->SetForceVector(Vector3(0, -9.81 * GetMass(), 0));
	AddForce(gravity);
}

void MassAggregate::AddForce(Force* force)
{
	accumulatedForces.push_back(force);
}

void MassAggregate::MoveVelocity(Vector::Vector3 force)
{
	velocity->SetForceVector(velocity->GetForceVector() + force);

}

void MassAggregate::Move(PhysicalObject* object, float deltaTime)
{


	if (object->GetPosition().y <= 0.5) {
		isGrounded = true;
		Bounce();
	}
	else {
		isGrounded = false;
	}
	object->MovePosition(((prevVelocity->GetForceVector() * deltaTime) + (acceleration->GetForceVector() / 2) * (deltaTime * deltaTime)).ToXMFLOAT3());

	prevVelocity = velocity;
	netForce->SetForceVector(Vector3(0));

}

void MassAggregate::Bounce()
{
	acceleration->SetForceVector(Vector3(acceleration->GetForceVector().x, acceleration->GetForceVector().y * -1.25, acceleration->GetForceVector().z));
}

void MassAggregate::Update(float deltaTime)
{
	CalculateGravity();

	ApplyForces();
	CalculateAcceleration();

}
