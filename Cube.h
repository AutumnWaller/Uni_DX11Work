#pragma once
#include "Object.h"

using namespace DirectX;

class Cube : public Object
{
private:
	StaticStructs::StandardVertex vertices[24] =
	{
		//Bottom
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0, 1, 0), XMFLOAT2(0, 0)},
		{ XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT3(0, 1, 0), XMFLOAT2(1, 0)},
		{ XMFLOAT3(1.0f, 1.0f, 0.0f), XMFLOAT3(0, 1, 0), XMFLOAT2(1, 1)},
		{ XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT3(0, 1, 0), XMFLOAT2(0, 1)},
		
		//Top
		{ XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT3(0, 1, 0), XMFLOAT2(0, 0)},
		{ XMFLOAT3(1.0f, 0.0f, 1.0f), XMFLOAT3(0, 1, 0), XMFLOAT2(1, 0)},
		{ XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT3(0, 1, 0), XMFLOAT2(1, 1)},
		{ XMFLOAT3(0.0f, 1.0f, 1.0f), XMFLOAT3(0, 1, 0), XMFLOAT2(0, 1)},
		//Left
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0, 1, 0), XMFLOAT2(0, 0)},
		{ XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT3(0, 1, 0), XMFLOAT2(1, 0)},
		{ XMFLOAT3(1.0f, 0.0f, 1.0f), XMFLOAT3(0, 1, 0), XMFLOAT2(1, 1)},
		{ XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT3(0, 1, 0), XMFLOAT2(0, 1)},
		//Right
		{ XMFLOAT3(1.0f, 1.0f, 0.0f), XMFLOAT3(0, 1, 0), XMFLOAT2(0, 0)},
		{ XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT3(0, 1, 0), XMFLOAT2(1, 0)},
		{ XMFLOAT3(0.0f, 1.0f, 1.0f), XMFLOAT3(0, 1, 0), XMFLOAT2(1, 1)},
		{ XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT3(0, 1, 0), XMFLOAT2(0, 1)},
		//Front
		{ XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT3(0, 1, 0), XMFLOAT2(0, 0)},
		{ XMFLOAT3(1.0f, 0.0f, 1.0f), XMFLOAT3(0, 1, 0), XMFLOAT2(1, 0)},
		{ XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT3(0, 1, 0), XMFLOAT2(1, 1)},
		{ XMFLOAT3(1.0f, 1.0f, 0.0f), XMFLOAT3(0, 1, 0), XMFLOAT2(0, 1)},
		//Back
		{ XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT3(0, 1, 0), XMFLOAT2(0, 0)},
		{ XMFLOAT3(0.0f, 1.0f, 1.0f), XMFLOAT3(0, 1, 0), XMFLOAT2(1, 0)},
		{ XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT3(0, 1, 0), XMFLOAT2(1, 1)},
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0, 1, 0), XMFLOAT2(0, 1)},
	};

	WORD indices[36] = 
	{
		0,3,2,
		2,1,0,

		4,7,6,
		6,5,4,

		8,11,10,
		10,9,8,

		12,15,14,
		14,13,12,

		16,19,18,
		18,17,16,

		20,23,22,
		22,21,20,
	};

	XMFLOAT4X4 world;
	ID3D11Buffer* indexBuffer;
	ID3D11Buffer* vertexBuffer;
	
public:

	Cube(const wchar_t *texturePathRef);
	~Cube();
	virtual void Initialise(ID3D11Device *deviceRef, D3D11_SUBRESOURCE_DATA data, ID3D11DeviceContext *context, ID3D11Buffer* cBuffer) override;
	virtual void Draw(DirectX::XMMATRIX appWorld, StaticStructs::ConstantBuffer cb) override;
	virtual void Update(float time) override;
	virtual void Cleanup() override;
protected:

};

