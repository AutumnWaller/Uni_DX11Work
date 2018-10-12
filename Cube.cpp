#include "Cube.h"



Cube::Cube()
{
	vertexAmount = 8;
	indexAmount = 36;
	pVertices = vertices;
	pIndices = indices;
}


Cube::~Cube()
{
	pVertices = nullptr;
	pIndices = nullptr;
}

void Cube::Initialise(ID3D11Device * deviceRef, D3D11_SUBRESOURCE_DATA data, ID3D11DeviceContext * context, ID3D11Buffer * cBuffer)
{
	Object::Initialise(deviceRef, data, context, cBuffer);
}

void Cube::Draw(DirectX::XMMATRIX appWorld, StaticStructs::ConstantBuffer cb)
{
	Object::Draw(appWorld, cb);
}

void Cube::Update(float time)
{
	Object::Update(time);
}