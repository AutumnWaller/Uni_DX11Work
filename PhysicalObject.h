#pragma once

#include "Object.h"
#include "MassAggregate.h"
#include "RigidBody.h"
#include "Collision.h"
class MassAggregate;
class PhysicalObject : public Object
{
protected:
	RigidBody* _pRigidBody = nullptr;
	MassAggregate* _pMassAggregate = nullptr;
	Collision* _pCollision = nullptr;

public:
	MassAggregate* GetMassAggregate() { return _pMassAggregate; };
	Collision* GetCollision() { return _pCollision; };
	PhysicalObject();
	~PhysicalObject();
};

