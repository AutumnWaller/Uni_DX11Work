#pragma once

#include "Object.h"
#include "Camera.h"
#include "Grid.h"
#include "Cube.h"
#include "Car.h"
#include "Dome.h"

using namespace DirectX;

class GameManager
{
private:

	XMFLOAT4X4 _World;

	float time = 0;

	// Light direction from surface (XYZ)
	XMFLOAT3 lightDirection = XMFLOAT3(0.25f, 0.5f, -1.0f);

	// Diffuse material properties (RGBA)
	XMFLOAT4 diffuseMaterial = XMFLOAT4(1.0f, 1.0f, 1.0f, 0.1f);
	// Diffuse light colour (RGBA)

	XMFLOAT4 diffuseLight = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	XMFLOAT3 ambientLight = XMFLOAT3(0.2f, 0.2f, 0.2f);
	XMFLOAT3 ambientMaterial = XMFLOAT3(0.2f, 0.2f, 0.2f);

	XMFLOAT4 specularLight = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	XMFLOAT4 specularMaterial = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);

	D3D11_SUBRESOURCE_DATA data;


	std::vector<Object*> gameObjects;
	Camera *_pCameraThirdPerson, *_pCameraFront, *_pCameraTop;
	Car *car;
	ID3D11RasterizerState* _pWireframe;
	ID3D11RasterizerState* _pSolid;
	ID3D11RasterizerState* _pSolidFrontCull;
	ID3D11RasterizerState* _pCurrRasteriserState;
	ID3D11RasterizerState* _pPrevRasteriserState;
	ID3D11BlendState *_pTransparency;

	ID3D11DeviceContext *_pDContext;

	StaticStructs::ConstantBuffer cb;


	void LoadConstantBuffer();
public:
	Camera *_pCurrCamera;
	GameManager();
	~GameManager();
	void Initialise(ID3D11Device *deviceRef, ID3D11DeviceContext *context, ID3D11Buffer *cb);
	void Draw();
	void Update(float _Time);
	void Input(float deltaTime);
};

