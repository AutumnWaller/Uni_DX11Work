#pragma once
#include "Object.h"
class Grid : public Object
{
public:
	Grid();
	~Grid();
	void SetSize(int width, int length);
private:
	StaticStructs::StandardVertex vertices[4] = { { XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0, 1, 0), XMFLOAT2(0, 0)},
												{ XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT3(0, 1, 0), XMFLOAT2(1, 0)},
												{ XMFLOAT3(1.0f, 1.0f, 0.0f), XMFLOAT3(0, 1, 0), XMFLOAT2(1, 1)},
												{ XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT3(0, 1, 0), XMFLOAT2(0, 1)} };

	WORD indices[6] = { 0,3,2,
						2,1,0, };
	virtual void Initialise(ID3D11Device *deviceRef, ID3D11DeviceContext *context, ID3D11Buffer* cBuffer) override;
	virtual void Draw(DirectX::XMMATRIX appWorld, StaticStructs::ConstantBuffer cb) override;
	virtual void Update(float time) override;
	virtual void Cleanup() override;
};

