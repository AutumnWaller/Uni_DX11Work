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
	for (int i = 0; i < accumulatedForces.size(); i++) {
		accForce.x += accumulatedForces.at(i).x;
		accForce.y += accumulatedForces.at(i).y;
		accForce.z += accumulatedForces.at(i).z;
	}
	netForce = accForce;
	accForce = Vector3(0);

}

void MassAggregate::CalculateAcceleration(float deltaTime)
{
	acceleration = netForce / mass;
}

void MassAggregate::CalculateVelocity(float deltaTime)
{
	velocity = ((prevVelocity + acceleration) * deltaTime);
}

void MassAggregate::AddForce(Vector::Vector3 force)
{
	accumulatedForces.push_back(force);
}

void MassAggregate::Move(PhysicalObject* object, float deltaTime)
{
	netForce = Vector3(0);
	accForce = Vector3(0);
	ApplyForces();
	CalculateAcceleration(deltaTime);
	Vector3 prevPosition = object->GetPrevPosition();
	CalculateVelocity(deltaTime);
	object->MovePosition(((prevVelocity * deltaTime) + (acceleration / 2) * (deltaTime * deltaTime)).ToXMFLOAT3());
	prevVelocity = velocity;
}

void MassAggregate::Update(float deltaTime)
{


}
