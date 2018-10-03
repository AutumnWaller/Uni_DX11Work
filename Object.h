#pragma once

#include <DirectXMath.h>
#include <Windows.h>
#include <cstdio>


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
	std::size_t GetMemoryUsage() { return (sizeof(GetVertices()) * vertexAmount) + (sizeof(GetIndices()) * indexAmount); };
	Object(StandardVertex vertices[]);
	Object();
	~Object();

protected:
	StandardVertex *pVertices = nullptr;
	WORD *pIndices = nullptr;
	DirectX::XMFLOAT4 colour = {0,0,0,0};
};

