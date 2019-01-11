#include "Grid.h"


Grid::Grid()
{
	Object();
	if (!_pTexturePath)
		_pTexturePath = L"Textures/grassfloor.dds";
}

Grid::Grid(int width, int length)
{
	Object();
	SetSize(width, length);
}

Grid::Grid(int width, int length, char *heightmapFileName)
{
	Object();
	LoadHeightmap("Textures/Heightmap.raw", 513, 513);
	SetSize(width, length);
}

Grid::~Grid()
{
	Cleanup();
}

void Grid::Nullify()
{
	Object::Nullify();
	_pHeightMap = nullptr;
}

void Grid::SetSize(int width, int length)
{
	_pVertices = new StaticStructs::StandardVertex[((width * length) * 4)];
	_pIndices = new WORD[(width * length) * 6];

	int vertIndex = 0, indIndex = 0, indPos = 0;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < length; j++) {
			_pVertices[0 + vertIndex] = { XMFLOAT3(0.0f + (j + 2), 0.0f, 0.0f + (i + 2)), XMFLOAT3(0, 1, 0), XMFLOAT2(0, 0) };
			_pVertices[1 + vertIndex] = { XMFLOAT3(1.0f + (j + 2), 0.0f, 0.0f + (i + 2)), XMFLOAT3(0, 1, 0), XMFLOAT2(1, 0) };
			_pVertices[2 + vertIndex] = { XMFLOAT3(1.0f + (j + 2), 0.0f, 1.0f + (i + 2)), XMFLOAT3(0, 1, 0), XMFLOAT2(1, 1) };
			_pVertices[3 + vertIndex] = { XMFLOAT3(0.0f + (j + 2), 0.0f, 1.0f + (i + 2)), XMFLOAT3(0, 1, 0), XMFLOAT2(0, 1) };
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

void Grid::LoadHeightmap(char* fileName, int width, int height)
{
		// A height for each vertex 
		std::vector<unsigned char> in(width * height);

		_pHeightMap = new float[width * height];

		// Open the file
		std::ifstream inFile;
		inFile.open(fileName, std::ios_base::binary);

		if (inFile)
		{
			// Read the RAW bytes
			inFile.read((char*)&in[0], (std::streamsize)in.size());

			// Done with file.
			inFile.close();
		}

		// Copy the array data into a float array and scale it heightmap.resize(heightMapHeight * heightMapWidth, 0);

		for (UINT i = 0; i < height * width; ++i)
		{
			_pHeightMap[i] = (in[i] / 255.0f); //Scale if needed here
		}
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
	if (_pHeightMap) delete[] _pHeightMap;
}
