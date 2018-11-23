#include "Object.h"

Object::Object()
{
	_pVertices = nullptr;
	_pIndices = nullptr;

	_pTexturePath = nullptr;
	_pTexture = nullptr;
	_pTextureRV = nullptr;

	_pIndexBuffer = nullptr;
	_pVertexBuffer = nullptr;
	_pConstantBuffer = nullptr;
	_pDeviceContext = nullptr;
	_pSamplerLinear = nullptr;
	_pVertexShader = nullptr;
	_pPixelShader = nullptr;

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


Object::Object(StaticStructs::StandardVertex *vertices, WORD *indices, int vertexSize, int indexSize, const wchar_t *texturePath = L"Crate_COLOR.dds")
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


void Object::ChangeWorld(DirectX::XMMATRIX matrix)
{
	DirectX::XMStoreFloat4x4(&world, matrix);
}

void Object::Initialise(ID3D11Device *deviceRef, D3D11_SUBRESOURCE_DATA data, ID3D11DeviceContext *context, ID3D11Buffer* cBuffer)
{
	_pDeviceRef = deviceRef;
	_pDeviceContext = context;
	_pConstantBuffer = cBuffer;

	CreateDDSTextureFromFile(_pDeviceRef, _pTexturePath, nullptr, &_pTextureRV);

	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

	_pDeviceRef->CreateSamplerState(&sampDesc, &_pSamplerLinear);

	currMatrix = DirectX::XMMatrixIdentity();

	

	D3D11_BUFFER_DESC bd;

	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(StaticStructs::StandardVertex) * vertexAmount;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	data.pSysMem = GetVertices();
	_pDeviceRef->CreateBuffer(&bd, &data, &_pVertexBuffer);

	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(unsigned int) * 3 * indexAmount;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	data.pSysMem = GetIndices();
	_pDeviceRef->CreateBuffer(&bd, &data, &_pIndexBuffer);

	
}

void Object::Draw(DirectX::XMMATRIX appWorld, StaticStructs::ConstantBuffer cb)
{
	UINT stride = sizeof(StaticStructs::StandardVertex);
	UINT offset = 0;
	_pDeviceContext->IASetVertexBuffers(0, 1, &_pVertexBuffer, &stride, &offset);

	//Per object shader at some point
	//_pDeviceContext->VSSetShader(_pVertexShader, nullptr, 0);
	//_pDeviceContext->VSSetConstantBuffers(0, 1, &_pConstantBuffer);
	//_pDeviceContext->PSSetConstantBuffers(0, 1, &_pConstantBuffer);
	//_pDeviceContext->PSSetShader(_pPixelShader, nullptr, 0);

	_pDeviceContext->IASetIndexBuffer(_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
	appWorld = DirectX::XMLoadFloat4x4(&world);
	cb.mWorld = XMMatrixTranspose(appWorld);
	_pDeviceContext->UpdateSubresource(_pConstantBuffer, 0, nullptr, &cb, 0, 0);
	_pDeviceContext->PSSetSamplers(0, 1, &_pSamplerLinear);
	_pDeviceContext->PSSetShaderResources(0, 1, &_pTextureRV);
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
	if (_pTexture) delete _pTexture;
	if (_pTextureRV) delete _pTextureRV;
	if (_pSamplerLinear) delete _pSamplerLinear;
	if(_pVertexShader) delete _pVertexShader;
	if(_pPixelShader) delete _pPixelShader;
}
