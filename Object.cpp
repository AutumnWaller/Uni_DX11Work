#include "Object.h"

Object::Object()
{
	
}


void Object::CalculateNormals()
{

	for (int i = 0; i < vertexAmount; i++) {
		pVertices[i].Normal = pVertices[i].Pos;
		pVertices[i].Normal.y += 1;
	}
	CalculateTexCoords();
}

void Object::CalculateTexCoords()
{
	for (int i = 0; i < vertexAmount; i++) {
		pVertices[i].TexC = XMFLOAT2{ pVertices[i].Pos.x, pVertices[i].Pos.y };
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


void Object::ChangeWorld(DirectX::XMMATRIX matrix)
{
	DirectX::XMStoreFloat4x4(&world, matrix);
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
	//
}
