#pragma once

#include "Object.h"
#include "MassAggregate.h"
#include "RigidBody.h"

class MassAggregate;
class PhysicalObject : public Object
{
protected:
	RigidBody* _rigidBody = nullptr;
	MassAggregate* _massAggregate = nullptr;

public:
	PhysicalObject();
	~PhysicalObject();
};

