#pragma once

#include "Object.h"
#include "Camera.h"
#include "ThirdPersonCamera.h"
#include "BumperCamera.h"
#include "Grid.h"
#include "Cube.h"
#include "Ball.h"
#include "Car.h"
#include "Dome.h"
#include "FileManager.h"
#include "Grass.h"
#include "Goal.h"
#include "Shader.h"
#include <random>


using namespace DirectX;
__declspec(align(16)) class GameManager
{

	

private:

	XMFLOAT4X4 _World;

	float time = 0;

	// Light direction from surface (XYZ)
	XMFLOAT3 lightDirection = XMFLOAT3(0.0f, 1.0f, -1.0f);

	// Diffuse material properties (RGBA)
	XMFLOAT4 diffuseMaterial = XMFLOAT4(0.5f, 0.5f, 0.5f, 0.002f);
	// Diffuse light colour (RGBA)

	XMFLOAT4 diffuseLight = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	XMFLOAT3 ambientLight = XMFLOAT3(0.5f, 0.5f, 0.5f);
	XMFLOAT3 ambientMaterial = XMFLOAT3(0.2f, 0.2f, 0.0f);

	XMFLOAT4 specularLight = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	XMFLOAT4 specularMaterial = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

	D3D11_SUBRESOURCE_DATA data;


	std::vector<Object*> gameObjects;
	Camera *_pCameraTop;
	BumperCamera * _pCameraBumper;
	ThirdPersonCamera *_pCameraThirdPerson;
	Car *car;
	ID3D11RasterizerState* _pWireframe;
	ID3D11RasterizerState* _pSolid;
	ID3D11RasterizerState* _pSolidFrontCull;
	ID3D11RasterizerState* _pSolidNoCull;
	ID3D11RasterizerState* _pCurrRasteriserState;
	ID3D11SamplerState*		_pSamplerLinear;
	ID3D11BlendState *_pTransparency;

	ID3D11Buffer* _pConstantBuffer;
	std::vector < ID3D11InputLayout*> *_pVertexLayouts;
	std::vector<ID3D11VertexShader*> *_pVertexShaders;
	std::vector <ID3D11PixelShader*> *_pPixelShaders;

	ID3D11DeviceContext *_pDContext;
	ID3D11Device *_pDeviceRef;

	StaticStructs::ConstantBuffer cbData;

	FileManager* fm;


	void LoadConstantBuffer();
public:

	void* operator new(size_t i)
	{
		return _mm_malloc(i, 16);
	}

	void operator delete(void* p)
	{
		_mm_free(p);
	}

	Camera *_pCurrCamera;
	GameManager();
	~GameManager();
	void Initialise(ID3D11Device *deviceRef, ID3D11DeviceContext *context, ID3D11Buffer *constantBuffer);
	HRESULT CompileShaders();
	HRESULT CreateRasterizers();
	HRESULT CreateSampleAndBlend();
	void Draw();
	void Update(float _Time);
	void Input(float deltaTime);
};

