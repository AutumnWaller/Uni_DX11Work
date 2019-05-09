#pragma once

#include <DirectXMath.h>
#include <vector>
#include "Vector.h"
#include "PhysicalObject.h"
#include "Force.h"
class PhysicalObject;
class MassAggregate
{
private:

	Force* gravity = new Force(Vector::Vector3(0, -9.81, 0));
	Force* velocity = new Force(Vector::Vector3(0, 0, 0));
	Force* prevVelocity = new Force(Vector::Vector3(0, 0, 0));
	Force* acceleration = new Force(Vector::Vector3(0, 0, 0));
	Force* netForce = new Force(Vector::Vector3(0, 0, 0));


	std::vector<Force*> accumulatedForces;

	float mass = 1;
	bool isGrounded = false;
public:
	MassAggregate();
	
	Force* GetVelocity() { return velocity; };
	Force* GetPrevVelocity() { return prevVelocity; };
	Force* GetAcceleration() { return acceleration; };
	float GetMass() { return mass; };


	
	void ApplyForces();

	void CalculateAcceleration();
	void CalculateVelocity(float deltaTime);
	void CalculateGravity();

	void AddForce(Force* force);
	void MoveVelocity(Vector::Vector3 force);
	void Move(PhysicalObject* object, float deltaTime);
	void Bounce();
	void Update(float deltaTime);
	
	
	~MassAggregate();
};

