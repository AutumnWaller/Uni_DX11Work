#include "Cube.h"



Cube::Cube(const wchar_t *name)
{
	_pTexturePath = name;
	vertexAmount = 24;
	indexAmount = 36;
	_pVertices = vertices;
	_pIndices = indices;
	CalculateNormals();
}



Cube::~Cube()
{
	Cleanup();
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

void Cube::Cleanup()
{
	if (indexBuffer) delete indexBuffer;
	if (vertexBuffer) delete vertexBuffer;
	Object::Cleanup();
}
