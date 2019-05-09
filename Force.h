#pragma once
#include "Vector.h"
class Force
{
protected:
	Vector::Vector3 forceVector;
public:
	Force(Vector::Vector3 _forceVector);
	void SetForceVector(Vector::Vector3 _forceVector);
	Vector::Vector3 GetForceVector() { return forceVector; };
	~Force();
};