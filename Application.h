#pragma once

#include <windows.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <directxcolors.h>
#include "resource.h"
#include "Object.h"
#include "Cube.h"
#include "Pyramid.h"
#include <DirectXColors.h>
#include <vector>
#include <WinUser.h>

using namespace DirectX;



struct ConstantBuffer
{
	XMMATRIX mWorld;
	XMMATRIX mView;
	XMMATRIX mProjection;
	float gTime;
};


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
	ID3D11VertexShader*     _pVertexShader;
	ID3D11PixelShader*      _pPixelShader;
	ID3D11InputLayout*      _pVertexLayout;
	ID3D11InputLayout*      _pVertexLayoutPyramid;
	ID3D11Buffer*           _pVertexBuffer;
	ID3D11Buffer*			_pVertexBufferPyramid;
	ID3D11Buffer*           _pIndexBuffer;
	ID3D11Buffer*           _pIndexBufferPyramid;
	
	ID3D11Buffer*           _pConstantBuffer;
	XMFLOAT4X4              _world, _world2, _world3, _world4, _world5, _world6;
	XMFLOAT4X4              _view;
	XMFLOAT4X4              _projection;
	ID3D11DepthStencilView* _depthStencilView;
	ID3D11Texture2D* _depthStencilBuffer;
	ID3D11RasterizerState* _wireFrame;
	ID3D11RasterizerState* _solid;

	PBYTE kbState;

	D3D11_BUFFER_DESC bd;
	D3D11_SUBRESOURCE_DATA InitData;
private:
	Cube *cube;
	Cube *cube2;
	Cube *cube3;
	Cube *cube4;
	Cube *cube5;
	Pyramid *pyramid;

	HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);
	HRESULT InitDevice();
	void Cleanup();
	HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);
	HRESULT InitShadersAndInputLayout();
	HRESULT InitDrawBuffers();
	
	UINT _WindowHeight;
	UINT _WindowWidth;



public:
	float gTime;
	Application();
	~Application();

	HRESULT Initialise(HINSTANCE hInstance, int nCmdShow);

	std::vector<Object*> objects;

	void Update();
	void Draw();
};

