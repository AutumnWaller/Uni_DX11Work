#include "Object.h"
#include "MathsFunctions.h"

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

Object::Object()
{
	meshData = {};
	vertexAmount = 0;
	indexAmount = 0;
	type = StaticStructs::OBJECT;
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
	Transform();
}

Object::Object(char *modelPath, bool _InvertTexCoords = true, const wchar_t *texturePath = nullptr)
{
	_pVertices = nullptr;
	_pIndices = nullptr;

	_pTextureRV = nullptr;

	_pIndexBuffer = nullptr;
	_pVertexBuffer = nullptr;
	_pConstantBuffer = nullptr;
	_pDeviceContext = nullptr;
	_pDeviceRef = nullptr;
	_pTexturePath = texturePath;
	invertTexCoords = _InvertTexCoords;
	_pModelPath = modelPath;
	Transform();

}

Object::Object(float xPos, float yPos, float zPos)
{
	meshData = {};
	vertexAmount = 0;
	indexAmount = 0;
	type = StaticStructs::OBJECT;
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
	Transform((Vector::Vector3(xPos, yPos, zPos)));
}

void Object::CalculateNormals()
{
	for (int i = 0; i < vertexAmount; i++) {

		XMVECTOR v1 = XMVectorSubtract(XMLoadFloat3(&_pVertices[i + 1].Pos), XMLoadFloat3(&_pVertices[i].Pos));
		XMVECTOR v2 = XMVectorSubtract(XMLoadFloat3(&_pVertices[i + 2].Pos), XMLoadFloat3(&_pVertices[i].Pos));
		XMStoreFloat3(&_pVertices[i].Normal, XMVector3Normalize(XMVector3Cross(v1, v2)));
	}
}



void Object::SetTexture(const wchar_t *texturePath)
{
	_pTexturePath = texturePath;
}

void Object::LoadModel(char *filePath)
{
	if (_pDeviceRef) {
		meshData = OBJLoader::Load(filePath, _pDeviceRef, invertTexCoords);
		vertexAmount = meshData.VertexCount;
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
	_pDeviceContext->DrawIndexed(indexAmount, 0, 0);
}

void Object::Update(float time)
{
	Transform::Update(time);
}

void Object::Turn(float amount)
{
	if (amount == 0)
		return;
	if (amount > 0) {
		if (_pRotation.y >= XM_PI * 2)
			_pRotation.y = 0;
	}
	else if (amount < 0) {
		if (_pRotation.y <= -(XM_PI * 2))
			_pRotation.y = 0;
	}

	MoveRotation(0, amount, 0);
	float rot = _pRotation.y;
	SetForward(MathsFunctions::Normalise(sin(rot)), 0, MathsFunctions::Normalise(cos(rot)));
}

void Object::MovePosition(float x, float y, float z)
{
	Transform::MovePosition(x, y, z);
}

void Object::MovePosition(XMFLOAT3 xyz)
{
	Transform::MovePosition(xyz.x, xyz.y, xyz.z);
}

void Object::SetRotation(float x, float y, float z)
{
	_pRotation = { x, y, z };
}

void Object::SetRotation(XMFLOAT3 xyz)
{
	_pRotation = Vector::Vector3(xyz.x, xyz.y, xyz.z);
}

void Object::MoveRotation(float x, float y, float z)
{
	_pRotation = { _pRotation.x += x, _pRotation.y += y, _pRotation.z += z };
}

void Object::SetForward(float x, float y, float z)
{
	_pForward = { x, y, z };
}

void Object::MoveForward(float x, float y, float z)
{
	_pForward = { _pForward.x + x, _pForward.y + y, _pForward.z + z };
}


Object::~Object()
{
	if (_pTextureRV) _pTextureRV->Release();
	Transform::~Transform();
}