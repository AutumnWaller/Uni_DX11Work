#pragma once
#include "PhysicalObject.h"



PhysicalObject::PhysicalObject()
{
	isPhysical = true;
	_pMassAggregate = new MassAggregate();
	_pRigidBody = new RigidBody();
	_pCollision = new Collision();
	Object();
}


PhysicalObject::~PhysicalObject()
{
	if (_pRigidBody) delete _pRigidBody;
	if (_pMassAggregate) delete _pMassAggregate;
	if (_pCollision) delete _pCollision;
	Object::~Object();
}
