#pragma once
#include "PhysicalObject.h"
class Ball : public PhysicalObject
{
public:
	Ball();
	~Ball();
	virtual void Initialise(ID3D11Device *deviceRef, ID3D11DeviceContext *context, ID3D11Buffer *cBuffer) override;
	virtual void Draw(DirectX::XMMATRIX appWorld, StaticStructs::ConstantBuffer cb) override;
	virtual void Update(float time) override;
};

