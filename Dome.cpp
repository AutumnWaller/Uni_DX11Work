#include "Dome.h"



Dome::Dome()
{
	_pModelPath = "Models/Cube.obj";
	_pTexturePath = L"Textures/ChainLink.dds";
	invertTexCoords = false;
	type = StaticStructs::DOME;

}


Dome::~Dome()
{
}

void Dome::Initialise(ID3D11Device * deviceRef, ID3D11DeviceContext * context, ID3D11Buffer * cBuffer)
{
	Object::Initialise(deviceRef, context, cBuffer);
}

void Dome::Draw(DirectX::XMMATRIX appWorld, StaticStructs::ConstantBuffer cb)
{

	Object::Draw(appWorld, cb);
}
