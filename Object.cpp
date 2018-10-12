#include "Object.h"

Object::Object()
{
	
}


void Object::ChangeColour(DirectX::XMFLOAT4 newColour)
{
	colour = newColour;
	for (int i = 0; i < vertexAmount; i++) {
		pVertices[i].Colour = newColour;
	}
}


Object::Object(StaticStructs::StandardVertex *vertices, WORD *indices, int vertexSize, int indexSize)
{
	pVertices = vertices;
	pIndices = indices;
	indexAmount = indexSize;
	vertexAmount = vertexSize;
}

Object::~Object()
{
	delete pVertices;
	delete pIndices;
}

void Object::Translate(StaticStructs::Vector3f newPosition)
{
	translationOffset = newPosition;
}

void Object::ChangeMatrix(DirectX::XMMATRIX matrix)
{
	currMatrix = matrix;
}

void Object::Initialise(ID3D11Device *deviceRef, D3D11_SUBRESOURCE_DATA data, ID3D11DeviceContext *context, ID3D11Buffer* cBuffer)
{

	currMatrix = DirectX::XMMatrixIdentity();

	D3D11_BUFFER_DESC bd;

	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(StaticStructs::StandardVertex) * vertexAmount;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	data.pSysMem = GetVertices();
	deviceRef->CreateBuffer(&bd, &data, &vertexBuffer);

	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(unsigned int) * 3 * indexAmount;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	data.pSysMem = GetIndices();
	deviceRef->CreateBuffer(&bd, &data, &indexBuffer);
	deviceContext = context;
	constantBuffer = cBuffer;
	
}

void Object::Draw(DirectX::XMMATRIX appWorld, StaticStructs::ConstantBuffer cb)
{
	UINT stride = sizeof(StaticStructs::StandardVertex);
	UINT offset = 0;
	deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);


	deviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R16_UINT, 0);
	appWorld = DirectX::XMLoadFloat4x4(&world);
	cb.mWorld = XMMatrixTranspose(appWorld);
	deviceContext->UpdateSubresource(constantBuffer, 0, nullptr, &cb, 0, 0);
	deviceContext->DrawIndexed(indexAmount, 0, 0);
}

void Object::Update(float time)
{
	DirectX::XMStoreFloat4x4(&world, currMatrix * DirectX::XMMatrixTranslation(translationOffset.x, translationOffset.y, translationOffset.z));
}
