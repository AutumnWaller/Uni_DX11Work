#include "Object.h"

Object::Object(char *modelPath, const wchar_t *texturePath = nullptr)
{
	_pVertices = nullptr;
	_pIndices = nullptr;

	_pTexturePath = nullptr;
	_pTextureRV = nullptr;

	_pIndexBuffer = nullptr;
	_pVertexBuffer = nullptr;
	_pConstantBuffer = nullptr;
	_pDeviceContext = nullptr;
	_pTexturePath = texturePath;
	_pModelPath = modelPath;

}

Object::Object()
{
	_pVertices = nullptr;
	_pIndices = nullptr;

	_pTexturePath = nullptr;
	_pTextureRV = nullptr;

	_pIndexBuffer = nullptr;
	_pVertexBuffer = nullptr;
	_pConstantBuffer = nullptr;
	_pDeviceContext = nullptr;
	_pTexturePath = nullptr;
	_pModelPath = nullptr;
}

void Object::CalculateNormals()
{
	for (int i = 0; i < vertexAmount; i+=3) {

		XMVECTOR v1 = XMLoadFloat3(&XMFLOAT3((float)_pIndices[i], (float)_pIndices[i + 1], (float)_pIndices[i + 2]));
		XMVECTOR v2 = XMLoadFloat3(&XMFLOAT3((float)_pIndices[i + 3], (float)_pIndices[i + 4], (float)_pIndices[i + 5]));
		XMVECTOR v3 = XMLoadFloat3(&XMFLOAT3((float)_pIndices[i + 6], (float)_pIndices[i + 7], (float)_pIndices[i + 8]));
		XMStoreFloat3(&_pVertices[i].Normal, XMVector3Cross(XMVectorSubtract(v1, v2), XMVectorSubtract(v3, v1)));
	}
}


Object::Object(StaticStructs::StandardVertex *vertices, WORD *indices, int vertexSize, int indexSize, const wchar_t *texturePath = nullptr)
{
	_pTexturePath = texturePath;
	_pVertices = vertices;
	_pIndices = indices;
	indexAmount = indexSize;
	vertexAmount = vertexSize;
}

Object::~Object()
{
	Cleanup();
}


void Object::SetPosition(int x, int y, int z)
{
	//_pPosition->x = x;
	//_pPosition->y = y;
	//_pPosition->z = z;
	DirectX::XMStoreFloat4x4(&world, XMMatrixTranslation(x, y, z));
}

void Object::SetRotation(int x, int y, int z)
{
	
	//DirectX::XMStoreFloat4x4(&world, XMMatrixRotationAxis(XMLoadFloat3(position), (x != 0) ? XMMatrixRotationX(x) : y != 0 ? : XMMatrixRotationY(y));
}

void Object::SetTexture(const wchar_t *texturePath)
{
	_pTexturePath = texturePath;
	CreateDDSTextureFromFile(_pDeviceRef, _pTexturePath, nullptr, &_pTextureRV);
}

void Object::LoadModel(char *filePath)
{
	if (_pDeviceRef) {
		meshData = OBJLoader::Load(filePath, _pDeviceRef);
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
	//_pDeviceContext->VSSetConstantBuffers(0, 1, &_pConstantBuffer);
	//_pDeviceContext->PSSetConstantBuffers(0, 1, &_pConstantBuffer);
	//_pDeviceContext->PSSetShader(_pPixelShader, nullptr, 0);



	_pDeviceContext->DrawIndexed(indexAmount, 0, 0);
}

void Object::Update(float time)
{

}

void Object::Cleanup()
{
	if (_pVertices) delete _pVertices;
	if (_pIndices) delete _pIndices;
	if (_pIndexBuffer) delete _pIndexBuffer;
	if (_pConstantBuffer) delete _pConstantBuffer;
	if (_pDeviceContext) delete _pDeviceContext;
	if (_pTexturePath) delete _pTexturePath;
	if (_pTextureRV) delete _pTextureRV;
}
