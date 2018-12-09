#include "Grid.h"


Grid::Grid(int width, int length)
{
	Object();
	SetSize(width, length);
}

Grid::~Grid()
{
	Cleanup();
}

void Grid::SetSize(int width, int length)
{
	_pVertices = new StaticStructs::StandardVertex[((width * length) * 4) + 1];
	_pIndices = new WORD[(width * length) * 6];

	int vertIndex = 0, indIndex = 0, indPos = 0;

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < length; j++) {
			_pVertices[0 + vertIndex] = { XMFLOAT3(0.0f + i, 0.0f, 0.0f + j), XMFLOAT3(0, 1, 0), XMFLOAT2(0, 0) };
			_pVertices[1 + vertIndex] = { XMFLOAT3(1.0f + i, 0.0f, 0.0f + j), XMFLOAT3(0, 1, 0), XMFLOAT2(1, 0) };
			_pVertices[2 + vertIndex] = { XMFLOAT3(1.0f + i, 0.0f, 1.0f + j), XMFLOAT3(0, 1, 0), XMFLOAT2(1, 1) };
			_pVertices[3 + vertIndex] = { XMFLOAT3(0.0f + i, 0.0f, 1.0f + j), XMFLOAT3(0, 1, 0), XMFLOAT2(0, 1) };
			vertIndex += 4;
			_pIndices[0 + indIndex] = indPos;
			_pIndices[1 + indIndex] = indPos + 3;
			_pIndices[2 + indIndex] = indPos + 2;
			_pIndices[3 + indIndex] = indPos + 2;
			_pIndices[4 + indIndex] = indPos + 1;
			_pIndices[5 + indIndex] = indPos;
			indIndex += 6;
			indPos += 4;
		}

	}
	vertexAmount = (width * length) * 4;
	indexAmount = (width * length) * 6;
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
