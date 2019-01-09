#pragma once

#include <windows.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <directxcolors.h>
#include "GameManager.h"
#include "resource.h"
#include "StaticStructs.h"
#include <DirectXColors.h>
#include <vector>
#include <WinUser.h>
#include "AppTime.h"
#include "Shader.h"

using namespace DirectX;

class Object;

class Application
{
private:
	HINSTANCE               _hInst;
	HWND                    _hWnd;
	D3D_DRIVER_TYPE         _driverType;
	D3D_FEATURE_LEVEL       _featureLevel;
	ID3D11Device*           _pd3dDevice;
	ID3D11DeviceContext*    _pImmediateContext;
	IDXGISwapChain*         _pSwapChain;
	ID3D11RenderTargetView* _pRenderTargetView;
	ID3D11SamplerState*		_pSamplerLinear;
	ID3D11Buffer* _pConstantBuffer;

	ID3D11DepthStencilView* _pDepthStencilView;
	ID3D11Texture2D* _pDepthStencilBuffer;

	ID3D11BlendState* _pTransparency;

	PBYTE kbState;

	D3D11_BUFFER_DESC bd;
	D3D11_SUBRESOURCE_DATA InitData;
private:
	GameManager *_pGameManager;
	HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);
	HRESULT InitDevice();
	void Cleanup();
	HRESULT InitShadersAndInputLayout();
	HRESULT InitDrawBuffers();
	
	UINT _WindowHeight;
	UINT _WindowWidth;





public:
	float gTime;
	Application();
	~Application();

	HRESULT Initialise(HINSTANCE hInstance, int nCmdShow);

	void Update();
	void Draw();
};

