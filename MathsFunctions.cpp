#include "MathsFunctions.h"

	
float MathsFunctions::Normalise(float value, float min, float max)
{
	return (value - min) / (max - min);
}


XMFLOAT3 MathsFunctions::AddFloats(XMFLOAT3 a, XMFLOAT3 b)
{
	XMVECTOR v1 = XMLoadFloat3(&a);
	XMVECTOR v2 = XMLoadFloat3(&b);
	XMFLOAT3 result = XMFLOAT3{0, 0, 0};
	XMStoreFloat3(&result, XMVectorAdd(v1, v2));
	return result;
}