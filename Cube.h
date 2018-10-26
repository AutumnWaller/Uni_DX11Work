#pragma once
#include "Object.h"

using namespace DirectX;

class Cube : public Object
{
private:
	StaticStructs::StandardVertex vertices[8] =
	{
		{ XMFLOAT3(-1.0f, 1.0f, 0.0f), XMFLOAT3(0, 1, 0)},
		{ XMFLOAT3(1.0f, 1.0f, 0.0f), XMFLOAT3(0, 1, 0) },
		{ XMFLOAT3(-1.0f, -1.0f, 0.0f), XMFLOAT3(0, 1, 0)},
		{ XMFLOAT3(1.0f, -1.0f, 0.0f), XMFLOAT3(0, 1, 0) },

		{ XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT3(0, 1, 0)},
		{ XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT3(0, 1, 0)},
		{ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT3(0, 1, 0)},
		{ XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT3(0, 1, 0) },
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

	XMFLOAT4X4 world;
	ID3D11Buffer* indexBuffer;
	ID3D11Buffer* vertexBuffer;

public:

	Cube();
	~Cube();
	virtual void Initialise(ID3D11Device *deviceRef, D3D11_SUBRESOURCE_DATA data, ID3D11DeviceContext *context, ID3D11Buffer* cBuffer) override;
	virtual void Draw(DirectX::XMMATRIX appWorld, StaticStructs::ConstantBuffer cb) override;
	virtual void Update(float time) override;
protected:

};

