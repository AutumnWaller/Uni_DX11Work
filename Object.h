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
public:
	int vertexAmount;
	int indexAmount;
	
	
	
	Object(StaticStructs::StandardVertex *vertices, WORD *indices, int vertexSize, int indexSize, const wchar_t *texturePath);
	Object(const wchar_t *texturePath);
	Object();
	~Object();

	void ChangeWorld(DirectX::XMMATRIX matrix);
	virtual void Initialise(ID3D11Device *deviceRef, D3D11_SUBRESOURCE_DATA data, ID3D11DeviceContext *context, ID3D11Buffer* cBuffer);
	virtual void Initialise(char *filePath, ID3D11Device *deviceRef, D3D11_SUBRESOURCE_DATA data, ID3D11DeviceContext *context, ID3D11Buffer* cBuffer);

	virtual void Draw(DirectX::XMMATRIX appWorld, StaticStructs::ConstantBuffer cb);
	virtual void Update(float time);
	virtual void Cleanup();
protected:
	void CalculateNormals();
	StaticStructs::StandardVertex *_pVertices;
	WORD *_pIndices = nullptr;

	const wchar_t *_pTexturePath;
	ID3D11Resource *_pTexture;
	ID3D11ShaderResourceView *_pTextureRV;

	DirectX::XMFLOAT4X4 world;
	ID3D11Buffer* _pIndexBuffer;
	ID3D11Buffer* _pVertexBuffer;
	ID3D11Buffer* _pConstantBuffer;
	ID3D11DeviceContext* _pDeviceContext;
	ID3D11SamplerState * _pSamplerLinear;
	ID3D11VertexShader *_pVertexShader;
	ID3D11PixelShader *_pPixelShader;
	ID3D11Device *_pDeviceRef;
	StaticStructs::Vector3f translationOffset;
	DirectX::XMMATRIX currMatrix;
	
};

