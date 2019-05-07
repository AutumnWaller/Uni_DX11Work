#pragma once

#include <DirectXMath.h>
#include <vector>
#include "Vector.h"
#include "PhysicalObject.h"
class PhysicalObject;
class MassAggregate
{
private:
	Vector::Vector3 velocity = Vector::Vector3(0, 0, 0);
	Vector::Vector3 prevVelocity = Vector::Vector3(0, 0, 0);
	Vector::Vector3 acceleration = Vector::Vector3(0, 0, 0);
	std::vector<Vector::Vector3> accumulatedForces;
	Vector::Vector3 accForce = Vector::Vector3(0, 0, 0);
	Vector::Vector3 netForce = Vector::Vector3(0, 0, 0);
	float mass = 1;
public:
	MassAggregate();
	
	Vector::Vector3 GetVelocity() { return velocity; };
	float GetMass() { return mass; };

	Vector::Vector3 GetPrevVelocity() { return prevVelocity; };
	Vector::Vector3 GetAcceleration() { return acceleration; };
	
	void ApplyForces();

	void CalculateAcceleration(float deltaTime);
	void CalculateVelocity(float deltaTime);
	void AddForce(Vector::Vector3 force);

	void Move(PhysicalObject* object, float deltaTime);
	void Update(float deltaTime);
	
	
	~MassAggregate();
};

