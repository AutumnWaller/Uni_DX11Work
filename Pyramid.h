#pragma once
#include "Object.h"

class Pyramid : public Object
{
private:
	StaticStructs::StandardVertex vertices[5] =
	{ 
		{ DirectX::XMFLOAT3(1.0f, 1.0f, 0.0f), DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f) , XMFLOAT2(0, 0)},
		{ DirectX::XMFLOAT3(3.0f, 1.0f, 0.0f), DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f) , XMFLOAT2(1, 0)},
		{ DirectX::XMFLOAT3(1.0f, -1.0f, 0.0f), DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(1, 1)},
		{ DirectX::XMFLOAT3(3.0f, -1.0f, 0.0f), DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(0, 1)},

		{ DirectX::XMFLOAT3{2, 0, 1}, DirectX::XMFLOAT3{2, 0, 1}}
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
	Pyramid(const wchar_t *name);
	~Pyramid();
	virtual void Cleanup() override;
	virtual void Initialise(ID3D11Device *deviceRef, ID3D11DeviceContext *context, ID3D11Buffer* cBuffer) override;
	virtual void Draw(DirectX::XMMATRIX appWorld, StaticStructs::ConstantBuffer cb) override;
	virtual void Update(float time) override;
};

