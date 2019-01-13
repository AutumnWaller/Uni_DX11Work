#pragma once

#include <DirectXMath.h>

using namespace DirectX;
class MathsFunctions
{
public:
	static float Normalise(float value, float min = 0, float max = 1);
	static XMFLOAT3 AddFloats(XMFLOAT3 a, XMFLOAT3 b);
};

