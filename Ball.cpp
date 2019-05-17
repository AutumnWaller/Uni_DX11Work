#include "Ball.h"



Ball::Ball()
{
	_pModelPath = "Models/ball.obj";
	_pTexturePath = L"Textures/ball.dds";
	
	invertTexCoords = false;
	type = StaticStructs::BALL;

	SetForward(0, 0, 1);
	_pMassAggregate->SetMass(300);
	_pMassAggregate->SetGravityScale(_pScale.y);
	_pMassAggregate->SetCoefficient(0.000057);
	type = StaticStructs::BALL;
	_pCollision->SetRadius(2.3);
	PhysicalObject();

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
	_pMassAggregate->Update(time);
	MovePosition(_pMassAggregate->Move(GetPosition(), time).ToXMFLOAT3());
	PhysicalObject::Update(time);
}