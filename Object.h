#pragma once

#include <DirectXMath.h>
#include <Windows.h>
#include "StaticStructs.h"
#include <cstdio>
#include <vector>
#include "DDSTextureLoader.h"
#include "OBJLoader.h"
#include <d3d11.h>


class Object
{
private:
	StaticStructs::StandardVertex* GetVertices() { return _pVertices; };
	WORD* GetIndices() { return _pIndices; };
	MeshData meshData;
	XMFLOAT3 *_pPosition;
public:
	int vertexAmount;
	int indexAmount;
	
	
	
	Object(StaticStructs::StandardVertex *vertices, WORD *indices, int vertexSize, int indexSize, const wchar_t *texturePath);
	Object(char *modelPath, const wchar_t *texturePath);
	Object();
	~Object();

	void SetPosition(int x, int y, int z);
	void SetRotation(int x, int y, int z);
	void SetTexture(const wchar_t *texturePath);
	virtual void Initialise(ID3D11Device *deviceRef, ID3D11DeviceContext *context, ID3D11Buffer* cBuffer);
	void LoadModel(char *filePath);
	virtual void Draw(DirectX::XMMATRIX appWorld, StaticStructs::ConstantBuffer cb);
	virtual void Update(float time);
	virtual void Cleanup();
protected:
	void CalculateNormals();
	StaticStructs::StandardVertex *_pVertices;
	WORD *_pIndices = nullptr;

	const wchar_t *_pTexturePath;
	char *_pModelPath;
	ID3D11ShaderResourceView *_pTextureRV;

	XMFLOAT4X4 world;
	XMFLOAT4X4 currMatrix;
	ID3D11Buffer* _pIndexBuffer;
	ID3D11Buffer* _pVertexBuffer;
	ID3D11Buffer* _pConstantBuffer;
	ID3D11DeviceContext* _pDeviceContext;
	ID3D11Device *_pDeviceRef;
	
};

