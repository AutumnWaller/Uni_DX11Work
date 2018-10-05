#pragma once

#include <DirectXMath.h>
#include <Windows.h>
#include <cstdio>
#include <vector>

class Object
{

public:
	static struct StandardVertex
	{
		DirectX::XMFLOAT3 Pos;
		DirectX::XMFLOAT4 Colour;
	};


	int vertexAmount;
	int indexAmount;
	void ChangeColour(DirectX::XMFLOAT4 newColour = DirectX::XMFLOAT4{0,1,1,0});

	StandardVertex* GetVertices() { return pVertices; };
	WORD* GetIndices() { return pIndices; };
	std::size_t GetVertexByteWidth() { return sizeof(StandardVertex) * vertexAmount; };
	std::size_t GetIndexByteWidth() { return sizeof(WORD) * indexAmount; };
	
	Object(StandardVertex *vertices, WORD *indices, int vertexSize, int indexSize);
	Object();
	~Object();

protected:
	StandardVertex *pVertices = nullptr;
	WORD *pIndices = nullptr;
	DirectX::XMFLOAT4 colour = {0,0,0,0};
};

