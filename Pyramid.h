#pragma once
#include "Object.h"

class Pyramid : public Object
{
private:
	StandardVertex vertices[5] = 
	{ 
		{ DirectX::XMFLOAT3(1.0f, 1.0f, 0.0f), DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
		{ DirectX::XMFLOAT3(3.0f, 1.0f, 0.0f), DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
		{ DirectX::XMFLOAT3(1.0f, -1.0f, 0.0f), DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
		{ DirectX::XMFLOAT3(3.0f, -1.0f, 0.0f), DirectX::XMFLOAT4(0.0f, 0.5f, 0.0f, 1.0f) },

		{ DirectX::XMFLOAT3{2, 0, 1},  DirectX::XMFLOAT4{1,1,1,1}}
	};

	WORD indices[18] = {
		//Base
		0,1,3,
		0,3,2,

		0,4,2,
		1,4,0,
		3,4,1,
		2,4,3
	};

public:
	Pyramid();
	~Pyramid();
};

