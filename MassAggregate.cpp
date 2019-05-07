#include "MassAggregate.h"

using namespace DirectX;
using namespace Vector;
MassAggregate::MassAggregate()
{
	accumulatedForces.push_back(Vector3(0, -9.81, 0));
}


MassAggregate::~MassAggregate()
{
}

void MassAggregate::ApplyForces()
{
	netForce = Vector3(0, 0, 0);
	for (int i = 0; i < accumulatedForces.size(); i++) {
		netForce.x += accumulatedForces.at(i).x;
		netForce.y += accumulatedForces.at(i).y;
		netForce.z += accumulatedForces.at(i).z;
	}
}

void MassAggregate::CalculateAcceleration(float deltaTime)
{
	acceleration = netForce / mass;
}

void MassAggregate::CalculateVelocity(float deltaTime)
{
	velocity = prevVelocity + acceleration * deltaTime;
}

void MassAggregate::AddForce(Vector::Vector3 force)
{
	accumulatedForces.push_back(force);
}

void MassAggregate::Move(PhysicalObject* object, float deltaTime)
{
	object->SetPosition(*object->GetPrevPosition() + GetPrevVelocity() * deltaTime + acceleration / 2 * deltaTime * deltaTime);
}

void MassAggregate::Update(float deltaTime)
{
	ApplyForces();
	CalculateAcceleration(deltaTime);
	CalculateVelocity(deltaTime);
}
