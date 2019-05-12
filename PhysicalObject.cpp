#pragma once
#include "PhysicalObject.h"



PhysicalObject::PhysicalObject()
{
	_pMassAggregate = new MassAggregate();
	_pRigidBody = new RigidBody();
	Object();
}


PhysicalObject::~PhysicalObject()
{
	if (_pRigidBody) delete _pRigidBody;
	if (_pMassAggregate) delete _pMassAggregate;
	Object::~Object();
}
