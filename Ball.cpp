#include "Ball.h"



Ball::Ball()
{
	_pModelPath = "Models/ball.obj";
	_pTexturePath = L"Textures/ball.dds";
	invertTexCoords = false;
	type = StaticStructs::BALL;
}


Ball::~Ball()
{
}

void Ball::Initialise(ID3D11Device * deviceRef, ID3D11DeviceContext * context, ID3D11Buffer * cBuffer)
{
	PhysicalObject::Initialise(deviceRef, context, cBuffer);
}

void Ball::Draw(DirectX::XMMATRIX appWorld, StaticStructs::ConstantBuffer cb)
{
	PhysicalObject::Draw(appWorld, cb);
}

void Ball::Update(float time)
{
	PhysicalObject::Update(time);
}