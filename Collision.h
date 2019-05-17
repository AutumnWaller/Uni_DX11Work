#pragma once
#include "Vector.h"
#include "MassAggregate.h"
class Collision
{
private:
	float boundRadius = 0;
public:
	Collision();
	bool CollisionCheck(Vector::Vector3 _positionA, Vector::Vector3 _positionB, float _radius);
	static void ResolveCollision(MassAggregate *a, MassAggregate *b);
	static Vector::Vector3 CalculateCoefficient(MassAggregate* a, MassAggregate* b) { return b->GetVelocity()->GetForceVector() - a->GetVelocity()->GetForceVector() / a->GetPrevVelocity()->GetForceVector() - b->GetPrevVelocity()->GetForceVector(); };
	void SetRadius(float _radius);
	float GetRadius() { return boundRadius; };
	~Collision();
};

