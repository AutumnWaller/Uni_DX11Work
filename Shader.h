#pragma once
#include <Windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
static class Shader
{
public:
	static HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);
};

