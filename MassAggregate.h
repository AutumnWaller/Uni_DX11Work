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
	Force* thrust = new Force(Vector::Vector3(0, 0, 0));
	Force* friction = new Force(Vector::Vector3(0, 0, 0));
	Force* velocity = new Force(Vector::Vector3(0, 0, 0));
	Force* prevVelocity = new Force(Vector::Vector3(0, 0, 0));
	Force* acceleration = new Force(Vector::Vector3(0, 0, 0));
	Force* netForce = new Force(Vector::Vector3(0, 0, 0));
	Force* dragForce = new Force(Vector::Vector3(0, 0, 0));

	std::vector<Force*> accumulatedForces;

	float frictionCoefficient = 1;
	float mass = 1;
	float gravityScale = 1;
	bool isGrounded = false;
public:
	MassAggregate();
	
	Force* GetVelocity() { return velocity; };
	Force* GetPrevVelocity() { return prevVelocity; };
	Force* GetAcceleration() { return acceleration; };
	float GetMass() { return mass; };
	void SetMass(float _mass) { mass = _mass * gravityScale; };
	void SetGravityScale (float _scale) { gravityScale = _scale; };
	void SetCoefficient(float _coefficient);
	void ApplyForces();

	void CalculateAcceleration();
	void CalculateVelocity(float deltaTime);
	void CalculateGravity();
	void CalculateFriction();
	void CalculateLaminarDrag();

	void AddForce(Force* force);
	void AddThrust(Vector::Vector3 force);
	void MoveVelocity(Vector::Vector3 force);
	void Move(PhysicalObject* object, float deltaTime);
	void Bounce();
	void Update(float deltaTime);
	
	
	~MassAggregate();
};

