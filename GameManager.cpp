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
	cbData.specularPower = 10.0f;
	cbData.specularLight = specularLight;
	cbData.specularMtrl = specularMaterial;
}

GameManager::GameManager()
{
	fm = new FileManager();
}


GameManager::~GameManager()
{
	gameObjects.~vector();
	if (_pCameraThirdPerson)delete _pCameraThirdPerson;
	if(_pCameraFront) delete _pCameraFront;
	if(car) delete car;
	if (_pVertexShaders) for each(ID3D11VertexShader* shader in *_pVertexShaders)shader->Release();
	//if (_pVertexLayout) _pVertexLayout->Release();
	if (_pPixelShaders) for each(ID3D11PixelShader* shader in *_pPixelShaders)shader->Release();
	if (fm) delete fm;
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

	D3D11_RASTERIZER_DESC wfDesc;
	ZeroMemory(&wfDesc, sizeof(D3D11_RASTERIZER_DESC));
	wfDesc.FillMode = D3D11_FILL_WIREFRAME;
	wfDesc.CullMode = D3D11_CULL_NONE;
	_pDeviceRef->CreateRasterizerState(&wfDesc, &_pWireframe);

	D3D11_RASTERIZER_DESC solidDesc;
	ZeroMemory(&solidDesc, sizeof(D3D11_RASTERIZER_DESC));
	solidDesc.FillMode = D3D11_FILL_SOLID;
	solidDesc.CullMode = D3D11_CULL_BACK;
	_pDeviceRef->CreateRasterizerState(&solidDesc, &_pSolid);

	_pCurrRasteriserState = _pSolid;


	D3D11_RASTERIZER_DESC solidFrontCullDesc;
	ZeroMemory(&solidFrontCullDesc, sizeof(D3D11_RASTERIZER_DESC));
	solidFrontCullDesc.FillMode = D3D11_FILL_SOLID;
	solidFrontCullDesc.CullMode = D3D11_CULL_FRONT;
	_pDeviceRef->CreateRasterizerState(&solidFrontCullDesc, &_pSolidFrontCull);

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

	_pDeviceRef->CreateBlendState(&blendDesc, &_pTransparency);

	XMStoreFloat4x4(&_World, XMMatrixIdentity());

	fm->ConvertRBD("Data/StartingPositions.rbd", &gameObjects);
	

	_pCameraThirdPerson = new Camera(XMVECTOR(XMVectorSet(0.0f, 0.0f, -3.0f, 0.0f)), XMVECTOR(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f)));
	_pCameraFront = new Camera(XMVECTOR(XMVectorSet(0.0f, 10.0f, 3.0f, 0.0f)), XMVECTOR(XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f)));
	//_pCameraTop = new Camera(XMVECTOR(XMVectorSet(0.0f, 10.0f, 3.0f, 0.0f)), XMVECTOR(XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f)));
	
	_pCurrCamera = _pCameraFront;


	Object *object = new Object("Models/Hercules.obj", true, L"Textures/Hercules_COLOR.dds");
	object->SetPosition(5, 0, 0);
	gameObjects.emplace_back(object);

	//Grid *grid = new Grid(100, 100);
	//grid->SetPosition(0, 1, 0);
	//grid->SetTexture(L"Textures/asphalt.dds");
	//gameObjects.emplace_back(grid);


	for (int i = 0; i < gameObjects.size(); i++) {
		if (gameObjects[i]->GetObjectType() == StaticStructs::CAR)
			car = (Car*)gameObjects[i];
		gameObjects[i]->Initialise(_pDeviceRef, _pDContext, _pConstantBuffer);
	}

	_pCurrCamera->FollowObject(car);


}

HRESULT GameManager::CompileShaders()
{

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
		ID3D11VertexShader* vs;
		ID3D11PixelShader* ps;
		ID3D11InputLayout* il;

		_pVertexShaders->emplace_back(vs);
		_pPixelShaders->emplace_back(ps);
		_pVertexLayouts->emplace_back(il);
	}
	Shader::InitialiseShaders(_pDeviceRef, _pVertexShaders, _pPixelShaders, layout, _pVertexLayouts, strings);

	// Set the input layout
	//_pDContext->IASetInputLayout(_pVertexLayout);
	return S_OK;
}

void GameManager::Draw()
{
	LoadConstantBuffer();
	_pDContext->PSSetShader(_pPixelShaders->at(0), nullptr, 0);
	_pDContext->VSSetShader(_pVertexShaders->at(0), nullptr, 0);
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
		_pPrevRasteriserState = _pCurrRasteriserState;
		if (gameObjects[i]->GetObjectType() == StaticStructs::DOME) {
			_pCurrRasteriserState = _pSolidFrontCull;
			_pDContext->OMSetBlendState(_pTransparency, blendFactor, 0xffffffff);
		}else
			_pDContext->OMSetBlendState(0, 0, 0xffffffff);
		_pDContext->RSSetState(_pCurrRasteriserState);
		gameObjects[i]->Draw(world, cbData);
		if (_pCurrRasteriserState == _pSolidFrontCull)
			_pCurrRasteriserState = _pPrevRasteriserState;
	}

	
}

void GameManager::Update(float _Time)
{
	Input(_Time);

	//gameObjects[0]->SetRotation(-1 * time, 1, -1);
	//gameObjects[0]->ChangeWorld(XMMatrixScaling(0.5f, 0.5f, 0.5f)  * XMMatrixRotationZ(time * 0.25f));
	//gameObjects[1]->ChangeWorld(XMMatrixScaling(1.0f, 1.0f, 1.0f) * XMMatrixRotationZ(time) * XMMatrixTranslation(2.5f, 0, 0)  * XMMatrixRotationZ(time * 2.0f));
	//objects[2]->ChangeWorld(XMMatrixScaling(0.2f, 0.2f, 0.2f) * XMMatrixRotationZ(t) * XMMatrixTranslation(1.0f, 0, 0)  * XMMatrixRotationZ(t * 3.0f)  * XMMatrixTranslation(2.5f, 0, 0)  * XMMatrixRotationZ(t * 2.0f));
	//objects[3]->ChangeWorld(XMMatrixScaling(0.1f, 0.1f, 0.1f) * XMMatrixRotationZ(t) * XMMatrixTranslation(0.5f, 0, 0)  * XMMatrixRotationZ(t * 4.0f) * XMMatrixTranslation(1.0f, 0, 0)  * XMMatrixRotationZ(t * 3.0f)  * XMMatrixTranslation(2.5f, 0, 0)  * XMMatrixRotationZ(t * 2.0f));
	//objects[4]->ChangeWorld(XMMatrixScaling(0.25f, 0.25f, 0.25f)  * XMMatrixTranslation(1.5f, 0, 0) * XMMatrixRotationZ(-t));
	//objects[5]->ChangeWorld(XMMatrixScaling(0.25f, 0.25f, 0.25f)  * XMMatrixTranslation(3.0f, 0, 0) * XMMatrixRotationZ(t));
	for (int i = 0; i < gameObjects.size(); i++)
		gameObjects[i]->Update(_Time);
	_pDContext->RSSetState(_pCurrRasteriserState);
	_pCurrCamera->Update(_Time);
}

void GameManager::Input(float deltaTime)
{

	if (GetAsyncKeyState(VK_SPACE))
		_pCurrRasteriserState = _pWireframe;
	if (GetAsyncKeyState(VK_RETURN))
		_pCurrRasteriserState = _pSolid;

	if (GetAsyncKeyState(VK_NUMPAD1))
		_pCurrCamera = _pCameraThirdPerson;
	else if (GetAsyncKeyState(VK_NUMPAD2))
		_pCurrCamera = _pCameraFront;


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


	
	if (GetAsyncKeyState(VK_SPACE))
		_pCurrCamera->MovePosition(0, (1 * deltaTime) * _pCurrCamera->GetMovementSpeed(), 0);
	if (GetAsyncKeyState(VK_SHIFT))
		_pCurrCamera->MovePosition(0, (-1 * deltaTime) * _pCurrCamera->GetMovementSpeed(), 0);
	if (GetAsyncKeyState('E'))
		_pCurrCamera->MoveRotation((1 * deltaTime), 0, 0);

	if (GetAsyncKeyState('Q'))
		car->Boost(deltaTime);

}
