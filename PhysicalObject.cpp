#pragma once
#include "PhysicalObject.h"



PhysicalObject::PhysicalObject()
{
	_massAggregate = new MassAggregate();
	_rigidBody = new RigidBody();
}


PhysicalObject::~PhysicalObject()
{
	if (_rigidBody) delete _rigidBody;
	if (_massAggregate) delete _massAggregate;
	Object::~Object();
}
