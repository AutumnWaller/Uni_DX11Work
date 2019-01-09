#include "Shader.h"

HRESULT Shader::CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
{
	HRESULT hr = S_OK;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined(DEBUG) || defined(_DEBUG)
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

	ID3DBlob* pErrorBlob;
	hr = D3DCompileFromFile(szFileName, nullptr, nullptr, szEntryPoint, szShaderModel,
		dwShaderFlags, 0, ppBlobOut, &pErrorBlob);

	if (FAILED(hr))
	{
		if (pErrorBlob != nullptr)
			OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());

		if (pErrorBlob) pErrorBlob->Release();

		return hr;
	}

	if (pErrorBlob) pErrorBlob->Release();

	return S_OK;
}

HRESULT Shader::InitialiseShaders(ID3D11Device *device, std::vector<ID3D11VertexShader*>* outputVS, std::vector<ID3D11PixelShader*>* outputPS, D3D11_INPUT_ELEMENT_DESC *layoutDesc, std::vector<ID3D11InputLayout*>* inputLayout, std::vector<std::string> filePaths)
{
	for (int i = 0; i < filePaths.size(); i++) {
		HRESULT hr;
		int size = filePaths.at(i).size();
		int num = MultiByteToWideChar(CP_UTF8, 0, filePaths.at(i).c_str(), -1, NULL, 0);
		wchar_t *convertedPath = new wchar_t[num];

		MultiByteToWideChar(CP_UTF8, 0, filePaths.at(i).c_str(), -1, convertedPath, num);

		ID3DBlob* pVSBlob = nullptr;
		hr = Shader::CompileShaderFromFile(convertedPath, "VS", "vs_4_0", &pVSBlob);
		if (FAILED(hr))
		{
			MessageBox(nullptr,
				L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
			return hr;
		}
		// Create the vertex shader
		hr = device->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &outputVS->at(i));

		if (FAILED(hr))
		{
			pVSBlob->Release();
			return hr;
		}

		// Compile the pixel shader
		ID3DBlob* pPSBlob = nullptr;
		hr = Shader::CompileShaderFromFile(convertedPath, "PS", "ps_4_0", &pPSBlob);

		if (FAILED(hr))
		{
			MessageBox(nullptr,
				L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
			return hr;
		}

		// Create the pixel shader
		hr = device->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &outputPS->at(i));
		pPSBlob->Release();

		if (FAILED(hr))
			return hr;


		
		UINT numElements = 3;

		// Create the input layout
		hr = device->CreateInputLayout(layoutDesc, numElements, pVSBlob->GetBufferPointer(),
			pVSBlob->GetBufferSize(), &inputLayout->at(i));
		pVSBlob->Release();

		if (FAILED(hr))
			return hr;
	}
	return S_OK;
}