#pragma once
#include "Object.h"
class Grid : public Object
{
public:
	void SetSize(int _Width, int _Length);

	Grid(int width, int length);
	~Grid();

private:
	virtual void Initialise(ID3D11Device *deviceRef, ID3D11DeviceContext *context, ID3D11Buffer* cBuffer) override;
	virtual void Draw(DirectX::XMMATRIX appWorld, StaticStructs::ConstantBuffer cb) override;
	virtual void Update(float time) override;
	virtual void Cleanup() override;
};

