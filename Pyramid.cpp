#include "Pyramid.h"



Pyramid::Pyramid(const wchar_t *name)
{
	Object();
	_pTexturePath = name;
	_pVertices = vertices;
	_pIndices = indices;
	indexAmount = 18;
	vertexAmount = 5;
	CalculateNormals();
}


Pyramid::~Pyramid()
{
}

void Pyramid::Cleanup()
{
	Object::Cleanup();
}

void Pyramid::Initialise(ID3D11Device * deviceRef, D3D11_SUBRESOURCE_DATA data, ID3D11DeviceContext * context, ID3D11Buffer * cBuffer)
{
	Object::Initialise(deviceRef, data, context, cBuffer);
}

void Pyramid::Draw(DirectX::XMMATRIX appWorld, StaticStructs::ConstantBuffer cb)
{
	Object::Draw(appWorld, cb);
}

void Pyramid::Update(float time)
{
	Object::Update(time);
}
