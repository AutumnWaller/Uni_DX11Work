#pragma once

#include "Object.h"
#include "MassAggregate.h"
#include "RigidBody.h"

class MassAggregate;
class PhysicalObject : public Object
{
protected:
	RigidBody* _pRigidBody = nullptr;
	MassAggregate* _pMassAggregate = nullptr;
public:
	PhysicalObject();
	~PhysicalObject();
};

