#include "Force.h"


Force::Force(Vector::Vector3 _forceVector)
{
	forceVector = _forceVector;
}

void Force::SetForceVector(Vector::Vector3 _forceVector)
{
	forceVector = _forceVector;
}

Force::~Force()
{
}
