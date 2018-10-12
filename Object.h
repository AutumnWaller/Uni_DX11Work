#pragma once

#include <DirectXMath.h>
#include <Windows.h>
#include "StaticStructs.h"
#include <cstdio>
#include <vector>
#include <d3d11.h>

class Object
{

public:



	int vertexAmount;
	int indexAmount;
	void ChangeColour(DirectX::XMFLOAT4 newColour = DirectX::XMFLOAT4{0,1,1,0});

	StaticStructs::StandardVertex* GetVertices() { return pVertices; };
	WORD* GetIndices() { return pIndices; };
	
	Object(StaticStructs::StandardVertex *vertices, WORD *indices, int vertexSize, int indexSize);
	Object();
	~Object();
	void Translate(StaticStructs::Vector3f newPosition);
	void ChangeMatrix(DirectX::XMMATRIX matrix);
	virtual void Initialise(ID3D11Device *deviceRef, D3D11_SUBRESOURCE_DATA data, ID3D11DeviceContext *context, ID3D11Buffer* cBuffer);
	virtual void Draw(DirectX::XMMATRIX appWorld, StaticStructs::ConstantBuffer cb);
	virtual void Update(float time);

protected:
	StaticStructs::StandardVertex *pVertices = nullptr;
	WORD *pIndices = nullptr;
	DirectX::XMFLOAT4 colour = {0,0,0,0};
	DirectX::XMFLOAT4X4 world;
	ID3D11Buffer* indexBuffer;
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* constantBuffer;
	ID3D11DeviceContext* deviceContext;
	StaticStructs::Vector3f translationOffset;
	DirectX::XMMATRIX currMatrix;
};

