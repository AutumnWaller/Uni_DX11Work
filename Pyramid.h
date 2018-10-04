#pragma once
#include "Object.h"

class Pyramid : public Object
{
private:
	StandardVertex vertices[5] = 
	{ 
		{DirectX::XMFLOAT3{-1, -1, 0}, DirectX::XMFLOAT4{1,1,1,1}},
		{DirectX::XMFLOAT3{-1, 1, 0}, DirectX::XMFLOAT4{1,1,1,1}},
		{DirectX::XMFLOAT3{1, 1, 0}, DirectX::XMFLOAT4{1,1,1,1}},
		{DirectX::XMFLOAT3{-1, 1, 0}, DirectX::XMFLOAT4{1,1,1,1}},
		{DirectX::XMFLOAT3{0, 0, 1}, DirectX::XMFLOAT4{1,1,1,1}}
	};

	WORD indices[12] = {
		0,1,2,
		2,0,1,

		4,0,1,
		4,1,2,


	};

public:
	Pyramid();
	~Pyramid();
};

