#include "Cube.h"



Cube::Cube(const wchar_t *texturePath = nullptr)
{
	Object();
	_pTexturePath = texturePath;
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

void Cube::Initialise(ID3D11Device * deviceRef,  ID3D11DeviceContext * context, ID3D11Buffer * cBuffer)
{
	Object::Initialise(deviceRef, context, cBuffer);
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
	Object::Cleanup();
}
