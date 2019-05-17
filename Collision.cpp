#include "Collision.h"

using namespace Vector;

Collision::Collision()
{
}

bool Collision::CollisionCheck(Vector3 _positionA, Vector3 _positionB, float _radius)
{
	Vector3 dist = Vector3::Abs(_positionA - _positionB);
	float sumRadii = _radius + boundRadius;

	if (dist.x > sumRadii)
		return false;
	if (dist.y > sumRadii)
		return false;
	if (dist.z > sumRadii)
		return false;
	return true;
}

void Collision::ResolveCollision(MassAggregate* a, MassAggregate* b)
{
	if (a->GetMass() > b->GetMass()) {
		Vector3 newVel = (a->GetVelocity()->GetForceVector() * (a->GetMass() / b->GetMass()));
		b->SetVelocity(Vector3(newVel.x, b->GetVelocity()->GetForceVector().y, newVel.z));

	}
	else {
		Vector3 newVel = (b->GetVelocity()->GetForceVector() * (b->GetMass() / a->GetMass()));
		a->SetVelocity(Vector3(newVel.x, a->GetVelocity()->GetForceVector().y, newVel.z));
	}

	//a->SetVelocity(Vector::Vector3::Multiply(a->GetMass(), a->GetPrevVelocity()->GetForceVector())
	//	+ Vector::Vector3::Multiply(b->GetMass(), b->GetPrevVelocity()->GetForceVector())
	//	+ Vector::Vector3::Multiply(b->GetMass(), 1) /
	//	a->GetMass() + b->GetMass()
	//);

	//b->SetVelocity(Vector::Vector3::Multiply(a->GetMass(), a->GetPrevVelocity()->GetForceVector())
	//	+ Vector::Vector3::Multiply(b->GetMass(), b->GetPrevVelocity()->GetForceVector())
	//	+ Vector::Vector3::Multiply(a->GetMass(), 1) /
	//	a->GetMass() + b->GetMass()
	//);

}

void Collision::SetRadius(float _radius)
{
	boundRadius = _radius;
}

Collision::~Collision()
{
}
