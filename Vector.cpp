#include "Vector.h"
using namespace DirectX;
namespace Vector {

	Vector3::Vector3(float _X, float _Y, float _Z)
	{
		x = _X;
		y = _Y;
		z = _Z;
	}

	Vector3::Vector3(float n)
	{
		x = n;
		y = n;
		z = n;
	}

	void Vector3::ToXMFLOAT3(DirectX::XMFLOAT3* destination, Vector3 v)
	{
		destination->x = v.x;
		destination->y = v.y;
		destination->z = v.z;
	}

	Vector3::~Vector3()
	{
	}
}