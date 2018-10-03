#pragma once
#include "Object.h"

using namespace DirectX;

class Cube : public Object
{
private:
	Object::StandardVertex vertices[8] =
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

	WORD indices[36] = 
	{

		//Bottom
		0,1,3,
		0,3,2,

		1,5,4,
		3,5,1,

		3,6,5,
		2,6,3,

		2,0,7,
		7,6,2,

		0,1,4,
		4,7,0,

		//Top
		7,4,5,
		5,6,7
	};

public:

	Cube();
	~Cube();

protected:

};

