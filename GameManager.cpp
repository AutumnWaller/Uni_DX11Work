#include "GameManager.h"



void GameManager::LoadConstantBuffer()
{
	cbData.gTime = time;
	cbData.LightVecW = lightDirection;
	cbData.DiffuseLight = diffuseLight;
	cbData.DiffuseMtrl = diffuseMaterial;
	cbData.AmbientLight = ambientLight;
	cbData.AmbientMtrl = ambientMaterial;
	cbData.cameraEye = *_pCurrCamera->GetEye();
	cbData.specularPower = 256.0f;
	cbData.specularLight = specularLight;
	cbData.specularMtrl = specularMaterial;
}

GameManager::GameManager()
{
	_pCameraTop = nullptr;
	_pCameraBumper = nullptr;
	_pCameraThirdPerson = nullptr;
	car = nullptr;
	_pWireframe = nullptr;
	_pSolid = nullptr;
	_pSolidFrontCull = nullptr;
	_pSolidNoCull = nullptr;
	_pCurrRasteriserState = nullptr;
	_pSamplerLinear = nullptr;
	_pTransparency = nullptr;
	_pConstantBuffer = nullptr;
	_pVertexLayouts = nullptr;
	_pVertexShaders = nullptr;
	_pPixelShaders = nullptr;
	_pDContext = nullptr;
	_pDeviceRef = nullptr;
	cbData = {};
	_pCurrCamera = nullptr;


	fm = new FileManager();
}


GameManager::~GameManager()
{
	gameObjects.clear();

	if (_pCameraThirdPerson)delete _pCameraThirdPerson;
	if (_pCameraBumper) delete _pCameraBumper;
	if (car) delete car;
	if (fm) delete fm;

	if (_pVertexShaders) for each(ID3D11VertexShader* shader in *_pVertexShaders)shader->Release();
	if (_pVertexLayouts) for each(ID3D11InputLayout* iLayout in *_pVertexLayouts)iLayout->Release();
	if (_pPixelShaders) for each(ID3D11PixelShader* shader in *_pPixelShaders)shader->Release();

	if(_pWireframe) _pWireframe->Release();
	if(_pSolid) _pSolid->Release();
	if(_pSolidFrontCull) _pSolidFrontCull->Release();
	if(_pSolidNoCull) _pSolidNoCull->Release();
	if(_pSamplerLinear) _pSamplerLinear->Release();
	if(_pTransparency) _pTransparency->Release();
}

void GameManager::Initialise(ID3D11Device *deviceRef, ID3D11DeviceContext *context, ID3D11Buffer *constantBuffer)
{

	_pDContext = context;
	_pDeviceRef = deviceRef;
	_pConstantBuffer = constantBuffer;
	_pVertexShaders = new vector<ID3D11VertexShader*>();
	_pPixelShaders = new vector<ID3D11PixelShader*>();
	_pVertexLayouts = new vector<ID3D11InputLayout*>();

	

	CompileShaders();
	XMStoreFloat4x4(&_World, XMMatrixIdentity());

	fm->ConvertRBD("Data/StartingPositions.rbd", &gameObjects);
	

	//Object *object = new Object("Models/Hercules.obj", true, L"Textures/Hercules_COLOR.dds");
	//object->SetPosition(5, 0, 0);
	//gameObjects.emplace_back(object);

	for (int i = 1; i < 30; i++) {
		for (int j = 1; j < 30; j++) {
			int x = rand() % 98 + 3;
			int z = rand() % 98 + 4;
			int yRot = rand() % 360;
			Grass *grass = new Grass();
			grass->SetPosition(x, 0.5f, z);
			grass->SetScale(0.6f, 0.4f, 0.6f);
			grass->SetRotation(0, yRot, 0);
			gameObjects.emplace_back(grass);
			Grass *grass2 = new Grass();
			grass2->SetScale(0.6f, 0.4f, 0.6f);
			grass2->SetPosition(x, 0.5f, z);
			grass2->SetRotation(0, yRot + 90, 0);
			gameObjects.emplace_back(grass2);
		}
	}


	for (int i = 0; i < gameObjects.size(); i++) {
		if (gameObjects[i]->GetObjectType() == StaticStructs::CAR)
			car = (Car*)gameObjects[i];
		gameObjects[i]->Initialise(_pDeviceRef, _pDContext, _pConstantBuffer);
	}

	//Eye is position, at is the target
	_pCameraThirdPerson = new ThirdPersonCamera(car);
	_pCameraBumper = new BumperCamera(car);
	_pCameraTop = new Camera(XMVECTOR(XMVectorSet(50.0f, 60.0f, 40.0f, 0.0f)), XMVECTOR(XMVectorSet(50.0f, 0.0f, 50.0f, 0.0f)));
	_pCurrCamera = _pCameraTop;

}

HRESULT GameManager::CompileShaders()
{
	CreateSampleAndBlend();
	CreateRasterizers();
	// Define the input layout
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	std::vector<std::string> strings;
	fm->ConvertRBS("Data/ShaderPaths.rbs", &strings);
	for(int i = 0; i < strings.size(); i++)
	{
		ID3D11VertexShader* vs = nullptr;
		ID3D11PixelShader* ps = nullptr;
		ID3D11InputLayout* il = nullptr;

		_pVertexShaders->emplace_back(vs);
		_pPixelShaders->emplace_back(ps);
		_pVertexLayouts->emplace_back(il);
	}
	Shader::InitialiseShaders(_pDeviceRef, _pVertexShaders, _pPixelShaders, layout, _pVertexLayouts, strings);

	return S_OK;
}

HRESULT GameManager::CreateRasterizers()
{
	HRESULT hr;  
	D3D11_RASTERIZER_DESC wfDesc;
	ZeroMemory(&wfDesc, sizeof(D3D11_RASTERIZER_DESC));
	wfDesc.FillMode = D3D11_FILL_WIREFRAME;
	wfDesc.CullMode = D3D11_CULL_NONE;
	hr = _pDeviceRef->CreateRasterizerState(&wfDesc, &_pWireframe);
	if (hr == E_FAIL)
		MessageBox(nullptr, L"Rasterizer failure", L"Error", MB_OK);

	D3D11_RASTERIZER_DESC solidDesc;
	ZeroMemory(&solidDesc, sizeof(D3D11_RASTERIZER_DESC));
	solidDesc.FillMode = D3D11_FILL_SOLID;
	solidDesc.CullMode = D3D11_CULL_BACK;
	hr = _pDeviceRef->CreateRasterizerState(&solidDesc, &_pSolid);

	_pCurrRasteriserState = _pSolid;

	if (hr == E_FAIL)
		MessageBox(nullptr, L"Rasterizer failure", L"Error", MB_OK);

	D3D11_RASTERIZER_DESC solidFrontCullDesc;
	ZeroMemory(&solidFrontCullDesc, sizeof(D3D11_RASTERIZER_DESC));
	solidFrontCullDesc.FillMode = D3D11_FILL_SOLID;
	solidFrontCullDesc.CullMode = D3D11_CULL_FRONT;
	hr = _pDeviceRef->CreateRasterizerState(&solidFrontCullDesc, &_pSolidFrontCull);
	
	if (hr == E_FAIL)
		MessageBox(nullptr, L"Rasterizer failure", L"Error", MB_OK);

	D3D11_RASTERIZER_DESC solidNoCullDesc;
	ZeroMemory(&solidNoCullDesc, sizeof(D3D11_RASTERIZER_DESC));
	solidNoCullDesc.FillMode = D3D11_FILL_SOLID;
	solidNoCullDesc.CullMode = D3D11_CULL_NONE;
	hr = _pDeviceRef->CreateRasterizerState(&solidNoCullDesc, &_pSolidNoCull);

	if (hr == E_FAIL)
		MessageBox(nullptr, L"Rasterizer failure", L"Error", MB_OK);
	return hr;
}

HRESULT GameManager::CreateSampleAndBlend()
{
	HRESULT hr;
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

	hr = _pDeviceRef->CreateSamplerState(&sampDesc, &_pSamplerLinear);
	if (hr == E_FAIL)
		MessageBox(nullptr, L"Sampler failure", L"Error", MB_OK);

	D3D11_BLEND_DESC blendDesc;
	ZeroMemory(&blendDesc, sizeof(blendDesc));

	D3D11_RENDER_TARGET_BLEND_DESC rtbd;
	ZeroMemory(&rtbd, sizeof(rtbd));

	rtbd.BlendEnable = true;
	rtbd.SrcBlend = D3D11_BLEND_SRC_COLOR;
	rtbd.DestBlend = D3D11_BLEND_BLEND_FACTOR;
	rtbd.BlendOp = D3D11_BLEND_OP_ADD;
	rtbd.SrcBlendAlpha = D3D11_BLEND_ONE;
	rtbd.DestBlendAlpha = D3D11_BLEND_ZERO;
	rtbd.BlendOpAlpha = D3D11_BLEND_OP_ADD;
	rtbd.RenderTargetWriteMask = D3D10_COLOR_WRITE_ENABLE_ALL;

	blendDesc.AlphaToCoverageEnable = false;
	blendDesc.RenderTarget[0] = rtbd;

	hr = _pDeviceRef->CreateBlendState(&blendDesc, &_pTransparency);
	if (hr == E_FAIL)
		MessageBox(nullptr, L"Blend State failure", L"Error", MB_OK);
	return hr;
}

void GameManager::Draw()
{
	LoadConstantBuffer();
	_pDContext->PSSetSamplers(0, 1, &_pSamplerLinear);

	_pDContext->PSSetShader(_pPixelShaders->at(0), nullptr, 0);
	_pDContext->VSSetShader(_pVertexShaders->at(0), nullptr, 0);
	_pDContext->IASetInputLayout(_pVertexLayouts->at(0));

	_pDContext->VSSetConstantBuffers(0, 1, &_pConstantBuffer);
	_pDContext->PSSetConstantBuffers(0, 1, &_pConstantBuffer);

	XMMATRIX world = XMLoadFloat4x4(&_World);
	XMMATRIX view = XMLoadFloat4x4(&_pCurrCamera->GetViewMatrix());
	XMMATRIX projection = XMLoadFloat4x4(&_pCurrCamera->GetProjectionMatrix());
	cbData.mWorld = XMMatrixTranspose(world);
	cbData.mView = XMMatrixTranspose(view);
	cbData.mProjection = XMMatrixTranspose(projection);

	float blendFactor[] = { 0.75f, 0.75f, 0.75f, 1.0f };

	for (int i = 0; i < gameObjects.size(); i++) {
		Object *currObject = gameObjects[i];
		if (currObject->GetObjectType() == StaticStructs::BILLBOARD) {
			if (_pCurrRasteriserState == _pWireframe)
				_pDContext->RSSetState(_pWireframe);
			else
			{
				_pDContext->OMSetBlendState(0, 0, 0xffffffff);
				_pDContext->RSSetState(_pSolidNoCull);
				_pDContext->PSSetShader(_pPixelShaders->at(2), nullptr, 0);
				_pDContext->VSSetShader(_pVertexShaders->at(2), nullptr, 0);
				gameObjects[i]->Draw(world, cbData);

			}
		}
		if (currObject->GetObjectType() == StaticStructs::DOME) {
			if(_pCurrRasteriserState == _pWireframe)
				_pDContext->RSSetState(_pWireframe);
			else
				_pDContext->RSSetState(_pSolidNoCull);
			_pDContext->OMSetBlendState(_pTransparency, blendFactor, 0xffffffff);
			_pDContext->PSSetShader(_pPixelShaders->at(1), nullptr, 0);
			_pDContext->VSSetShader(_pVertexShaders->at(1), nullptr, 0);
			gameObjects[i]->Draw(world, cbData);
		}
		else {
			_pDContext->RSSetState(_pCurrRasteriserState);
			_pDContext->OMSetBlendState(0, 0, 0xffffffff);
			_pDContext->PSSetShader(_pPixelShaders->at(0), nullptr, 0);
			_pDContext->VSSetShader(_pVertexShaders->at(0), nullptr, 0);
			gameObjects[i]->Draw(world, cbData);
		}
	}

	
}

void GameManager::Update(float _Time)
{
	Input(_Time);
	for (int i = 0; i < gameObjects.size(); i++)
		gameObjects[i]->Update(_Time);
	_pCurrCamera->Update(_Time);
}

void GameManager::Input(float deltaTime)
{

	if (GetAsyncKeyState(0x31)) //1
		_pCurrRasteriserState = _pWireframe;
	if (GetAsyncKeyState(0x32)) //2
		_pCurrRasteriserState = _pSolid;

	if (GetAsyncKeyState('T'))
		_pCurrCamera = _pCameraThirdPerson;
	else if (GetAsyncKeyState('B'))
		_pCurrCamera = _pCameraBumper;
	else if(GetAsyncKeyState('U'))
		_pCurrCamera = _pCameraTop;



	if (GetAsyncKeyState('D')) 
		car->Turn(deltaTime);
	else if (GetAsyncKeyState('A'))
		car->Turn(-deltaTime);
	else if (GetAsyncKeyState('W')) {
		car->Accelerate(deltaTime);
	}
	else if (GetAsyncKeyState('S')) {
		car->Accelerate(-deltaTime);
	}else
		car->Decelerate(deltaTime);


	
	if (GetAsyncKeyState(VK_UP))
		_pCurrCamera->MovePosition(0, (1 * deltaTime) * _pCurrCamera->GetMovementSpeed(), 0);
	if (GetAsyncKeyState(VK_DOWN))
		_pCurrCamera->MovePosition(0, (-1 * deltaTime) * _pCurrCamera->GetMovementSpeed(), 0);

	if (GetAsyncKeyState(VK_SHIFT))
		car->Boost(deltaTime);

}
