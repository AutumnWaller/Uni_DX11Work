#include "Ball.h"



Ball::Ball()
{
	_pModelPath = "Models/Ball3.obj";
	_pTexturePath = L"Textures/black.dds";
	invertTexCoords = false;
	type = StaticStructs::BALL;
}


Ball::~Ball()
{
}

void Ball::Initialise(ID3D11Device * deviceRef, ID3D11DeviceContext * context, ID3D11Buffer * cBuffer)
{
	Object::Initialise(deviceRef, context, cBuffer);
}

void Ball::Draw(DirectX::XMMATRIX appWorld, StaticStructs::ConstantBuffer cb)
{
	Object::Draw(appWorld, cb);
}

void Ball::Update(float time)
{
	Object::Update(time);
}

void Ball::Cleanup()
{
	Object::Cleanup();
}
