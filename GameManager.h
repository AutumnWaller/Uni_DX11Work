#pragma once

#include "Object.h"
#include "Camera.h"
#include "Grid.h"
#include "Cube.h"
#include "Car.h"

using namespace DirectX;

class GameManager
{
private:

	XMFLOAT4X4 _World;

	float time = 0;

	// Light direction from surface (XYZ)
	XMFLOAT3 lightDirection = XMFLOAT3(-3.0f, 10.0f, 0.0f);

	// Diffuse material properties (RGBA)
	XMFLOAT4 diffuseMaterial = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
	// Diffuse light colour (RGBA)

	XMFLOAT4 diffuseLight = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
	XMFLOAT3 ambientLight = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 ambientMaterial = XMFLOAT3(0.0f, 0.0f, 0.0f);

	D3D11_SUBRESOURCE_DATA data;


	std::vector<Object*> gameObjects;
	Camera *_pCameraThirdPerson, *_pCameraFront;
	Car *car;
public:
	Camera *_pCurrCamera;
	GameManager();
	~GameManager();
	void Initialise(ID3D11Device *deviceRef, ID3D11DeviceContext *context, ID3D11Buffer *cb);
	void Draw();
	void Update(float _Time);
	void Input(float deltaTime);
};

