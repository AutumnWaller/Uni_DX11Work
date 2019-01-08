#pragma once
#include "Object.h"
class Grid : public Object
{
protected:
	virtual void Nullify() override;
public:
	void SetSize(int _Width, int _Length);

	Grid();
	Grid(int width, int length);
	Grid(int width, int length, char *heightmapFileName);
	~Grid();

private:
	float *_pHeightMap;
	void LoadHeightmap(char* fileName, int width, int height);
	virtual void Initialise(ID3D11Device *deviceRef, ID3D11DeviceContext *context, ID3D11Buffer* cBuffer) override;
	virtual void Draw(DirectX::XMMATRIX appWorld, StaticStructs::ConstantBuffer cb) override;
	virtual void Update(float time) override;
	virtual void Cleanup() override;
};

