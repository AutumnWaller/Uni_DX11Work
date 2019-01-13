#pragma once
#include <Windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <vector>
#include <string>
#include <tchar.h>
class Shader
{
public:
	static HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);
	static HRESULT InitialiseShaders(ID3D11Device *device, std::vector<ID3D11VertexShader*> *outputVS, std::vector<ID3D11PixelShader*> *outputPS, D3D11_INPUT_ELEMENT_DESC *layoutDesc, std::vector<ID3D11InputLayout*> *inputLayout, std::vector<std::string> filePaths);
};

