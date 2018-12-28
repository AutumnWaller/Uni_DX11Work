#include "Object.h"

void Object::CreateBuffers(ID3D11Device *deviceRef)
{
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(StaticStructs::StandardVertex) * vertexAmount;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = _pVertices;

	deviceRef->CreateBuffer(&bd, &InitData, &_pVertexBuffer);


	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(WORD) * indexAmount;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;

	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = _pIndices;
	deviceRef->CreateBuffer(&bd, &InitData, &_pIndexBuffer);

}

void Object::Nullify() {
	_pVertices = nullptr;
	_pIndices = nullptr;

	_pTexturePath = nullptr;
	_pTextureRV = nullptr;

	_pIndexBuffer = nullptr;
	_pVertexBuffer = nullptr;
	_pConstantBuffer = nullptr;
	_pDeviceContext = nullptr;
	_pDeviceRef = nullptr;
	_pModelPath = nullptr;
}


Object::Object()
{
	Nullify();
	StaticObject();
}

Object::Object(char *modelPath, bool _InvertTexCoords = true, const wchar_t *texturePath = nullptr)
{
	Nullify();
	_pTexturePath = texturePath;
	invertTexCoords = _InvertTexCoords;
	_pModelPath = modelPath;
	StaticObject();

}

Object::Object(float xPos, float yPos, float zPos)
{
	Nullify();
	StaticObject(new XMFLOAT3(xPos, yPos, zPos));
}

void Object::CalculateNormals()
{
	for (int i = 0; i < vertexAmount; i++) {

		XMVECTOR v1 = XMVectorSubtract(XMLoadFloat3(&_pVertices[i + 1].Pos), XMLoadFloat3(&_pVertices[i].Pos));
		XMVECTOR v2 = XMVectorSubtract(XMLoadFloat3(&_pVertices[i + 2].Pos), XMLoadFloat3(&_pVertices[i].Pos));
		XMStoreFloat3(&_pVertices[i].Normal, XMVector3Normalize(XMVector3Cross(v1, v2)));
	}
}

Object::~Object()
{
	Cleanup();
}


void Object::SetTexture(const wchar_t *texturePath)
{
	_pTexturePath = texturePath;
}

void Object::LoadModel(char *filePath)
{
	if (_pDeviceRef) {
		meshData = OBJLoader::Load(filePath, _pDeviceRef, invertTexCoords);
		_pVertexBuffer = meshData.VertexBuffer;
		_pIndexBuffer = meshData.IndexBuffer;
		indexAmount = meshData.IndexCount;
	}
}

void Object::Initialise(ID3D11Device *deviceRef, ID3D11DeviceContext *context, ID3D11Buffer *cBuffer)
{
	_pDeviceRef = deviceRef;
	_pDeviceContext = context;
	_pConstantBuffer = cBuffer;
	if (!_pTexturePath)
		_pTexturePath = L"Textures/black.dds";
	if (_pModelPath)
		LoadModel(_pModelPath);
	else {
		CreateBuffers(deviceRef);
	}
	CreateDDSTextureFromFile(_pDeviceRef, _pTexturePath, nullptr, &_pTextureRV);

}

void Object::Draw(DirectX::XMMATRIX appWorld, StaticStructs::ConstantBuffer cb)
{
	_pDeviceContext->PSSetShaderResources(0, 1, &_pTextureRV);
	appWorld = DirectX::XMLoadFloat4x4(&world);
	cb.mWorld = XMMatrixTranspose(appWorld);
	_pDeviceContext->UpdateSubresource(_pConstantBuffer, 0, nullptr, &cb, 0, 0);

	UINT stride = sizeof(StaticStructs::StandardVertex);
	UINT offset = 0;
	_pDeviceContext->IASetVertexBuffers(0, 1, &_pVertexBuffer, &stride, &offset);
	_pDeviceContext->IASetIndexBuffer(_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
	
	//Per object shader at some point
	//_pDeviceContext->VSSetShader(_pVertexShader, nullptr, 0);

	//_pDeviceContext->PSSetShader(_pPixelShader, nullptr, 0);

	_pDeviceContext->DrawIndexed(indexAmount, 0, 0);
}

void Object::Update(float time)
{
	StaticObject::Update(time);
}

void Object::Turn(float amount)
{
	StaticObject::Turn(amount);
}

void Object::Cleanup()
{
	if (_pTextureRV) _pTextureRV->Release();
	StaticObject::Cleanup();
}
