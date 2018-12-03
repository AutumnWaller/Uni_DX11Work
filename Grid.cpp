#include "Grid.h"


Grid::Grid(int x = 0, int y = 0, int z = 0, int width = 5, int length = 5)
{
	Object();
	StaticStructs::StandardVertex vertices[] = { XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0, 1, 0), XMFLOAT2(0, 0) ,
												{ XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT3(0, 1, 0), XMFLOAT2(1, 0) },
												{ XMFLOAT3(1.0f, 1.0f, 0.0f), XMFLOAT3(0, 1, 0), XMFLOAT2(1, 1) },
												{ XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT3(0, 1, 0), XMFLOAT2(0, 1) } };

	WORD indices[] = { 0, 3, 2,
						2, 1, 0 };

	_pIndices = indices;
	_pVertices = vertices;
	vertexAmount = 4;
	indexAmount = 6;
}

Grid::~Grid()
{
	Cleanup();
}

void Grid::Initialise(ID3D11Device * deviceRef, ID3D11DeviceContext * context, ID3D11Buffer * cBuffer)
{
	Object::Initialise(deviceRef, context, cBuffer);
}

void Grid::Draw(DirectX::XMMATRIX appWorld, StaticStructs::ConstantBuffer cb)
{
	Object::Draw(appWorld, cb);
}

void Grid::Update(float time)
{
	Object::Update(time);
}

void Grid::Cleanup()
{
	Object::Cleanup();
}
