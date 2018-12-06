#include "Grid.h"


Grid::Grid()
{
	Object();
	_pIndices = indices;
	_pVertices = vertices;
	vertexAmount = 4;
	indexAmount = 6;
}

Grid::~Grid()
{
	Cleanup();
}

void Grid::SetSize(int width, int length)
{
	for (int i = 0; i < vertexAmount; i++) {
		vertices[i].Pos.x *= width;
		vertices[i].Normal.x *= width;
		vertices[i].Pos.y *= length;
		vertices[i].Normal.y *= length;
	}
	_pIndices = indices;
	_pVertices = vertices;

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
