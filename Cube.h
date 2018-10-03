#pragma once
#include "Object.h"

using namespace DirectX;

class Cube : public Object
{
private:
	Object::StandardVertex vertices[16] =
	{
		{ XMFLOAT3(-3.0f, 1.0f, 0.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(-1.0f, 1.0f, 0.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(-3.0f, -1.0f, 0.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(-1.0f, -1.0f, 0.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) },

		{ XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(-1.0f, -1.0f, -1.0f),  XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(-3.0f, -1.0f, -1.0f),  XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(-3.0f, 1.0f, -1.0f),  XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
	};

public:
	Object::StandardVertex* GetVertices() { return vertices; };
	Cube();
	~Cube();
};

