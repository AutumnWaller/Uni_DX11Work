#pragma once

#include <Windows.h>
#include "StaticStructs.h"
#include <cstdio>
#include <vector>
#include "DDSTextureLoader.h"
#include "OBJLoader.h"
#include "Transform.h"

class Object : public Transform
{
private:
	StaticStructs::StandardVertex* GetVertices() { return _pVertices; };
	WORD* GetIndices() { return _pIndices; };
	void CreateBuffers(ID3D11Device *deviceRef);
	MeshData meshData;
public:
	int vertexAmount;
	int indexAmount;
	
	Object();
	Object(char *modelPath, bool _InvertTexCoords, const wchar_t *texturePath);
	Object(float xPos, float yPos, float zPos);
	~Object();

	StaticStructs::ObjectType GetObjectType() { return type; }

	void SetTexture(const wchar_t *texturePath);
	void LoadModel(char *filePath);
	virtual void Initialise(ID3D11Device *deviceRef, ID3D11DeviceContext *context, ID3D11Buffer* cBuffer);
	virtual void Draw(DirectX::XMMATRIX appWorld, StaticStructs::ConstantBuffer cb);
	virtual void Update(float time) override;
	virtual void Turn(float amount);

	virtual void MovePosition(float x, float y, float z) override;
	virtual void MovePosition(XMFLOAT3 xyz) override;

	virtual void SetRotation(float x, float y, float z);
	virtual void SetRotation(XMFLOAT3 xyz);
	virtual void MoveRotation(float x, float y, float z);
	Vector::Vector3 GetRotation() { return _pRotation; }

	virtual void SetForward(float x, float y, float z);
	virtual void MoveForward(float x, float y, float z);
	Vector::Vector3 GetForward() { return _pForward; };

protected:
	bool isUpdateable = true;

	float turnSpeed = 1;

	void CalculateNormals();
	StaticStructs::StandardVertex *_pVertices;
	WORD *_pIndices;

	const wchar_t *_pTexturePath;
	char *_pModelPath;
	ID3D11ShaderResourceView *_pTextureRV;

	ID3D11Buffer* _pIndexBuffer;
	ID3D11Buffer* _pVertexBuffer;
	ID3D11Buffer* _pConstantBuffer;
	ID3D11DeviceContext* _pDeviceContext;
	ID3D11Device *_pDeviceRef;
	bool invertTexCoords = true;
	StaticStructs::ObjectType type;

};

