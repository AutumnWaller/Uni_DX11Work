#include "GameManager.h"
#include <chrono>


GameManager::GameManager()
{
}


GameManager::~GameManager()
{
}

void GameManager::Initialise(ID3D11Device *deviceRef, ID3D11DeviceContext *context, ID3D11Buffer *cb)
{

	XMStoreFloat4x4(&_World, XMMatrixIdentity());

	_pCamera = new Camera(XMVECTOR(XMVectorSet(0.0f, 0.0f, -3.0f, 0.0f)), XMVECTOR(XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)), XMVECTOR(XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)), XMVECTOR(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f)));
	_pCamera2 = new Camera(XMVECTOR(XMVectorSet(0.0f, 10.0f, 3.0f, 0.0f)), XMVECTOR(XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f)), XMVECTOR(XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)), XMVECTOR(XMVectorSet(0.0f, 0.0f, -2.0f, 0.0f)));
	_pCurrCamera = _pCamera;
	
	_pCamera->MovePosition(50, 10, 50);

	
	//Cube *cube = new Cube(nullptr);
	//gameObjects.emplace_back(cube);

	//Object *car = new Object("Models/car.obj", L"Textures/black.dds");
	//gameObjects.emplace_back(car);
	//Object *car2 = new Object("Models/sphere.obj", nullptr);
	//gameObjects.emplace_back(car2);

	Object *object = new Object("Models/Hercules.obj", L"Textures/Hercules_COLOR.dds");
	object->SetPosition(5, 0, 0);
	gameObjects.emplace_back(object);

	Grid *grid = new Grid(256, 164);
	grid->SetPosition(0, 0, 0);
	grid->SetTexture(L"Textures/asphalt.dds");
	//grid->SetSize(5, 5);
	gameObjects.emplace_back(grid);

	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->Initialise(deviceRef, context, cb);
	}
}

void GameManager::Draw()
{
	XMMATRIX world = XMLoadFloat4x4(&_World);
	XMMATRIX view = XMLoadFloat4x4(&_pCurrCamera->GetViewMatrix());
	XMMATRIX projection = XMLoadFloat4x4(&_pCurrCamera->GetProjectionMatrix());

	
	StaticStructs::ConstantBuffer cb;
	cb.mWorld = XMMatrixTranspose(world);
	cb.mView = XMMatrixTranspose(view);
	cb.mProjection = XMMatrixTranspose(projection);
	cb.gTime = time;
	cb.LightVecW = lightDirection;
	cb.DiffuseLight = diffuseLight;
	cb.DiffuseMtrl = diffuseMaterial;
	cb.AmbientLight = ambientLight;
	cb.AmbientMtrl = ambientMaterial;


	for (int i = 0; i < gameObjects.size(); i++)
		gameObjects[i]->Draw(world, cb);

	
}

void GameManager::Update(float _Time)
{
	time = _Time;

	Input(time);

	gameObjects[1]->SetPosition(-2, -2, -1);
	//gameObjects[0]->SetRotation(-1 * time, 1, -1);
	//gameObjects[0]->ChangeWorld(XMMatrixScaling(0.5f, 0.5f, 0.5f)  * XMMatrixRotationZ(time * 0.25f));
	//gameObjects[1]->ChangeWorld(XMMatrixScaling(1.0f, 1.0f, 1.0f) * XMMatrixRotationZ(time) * XMMatrixTranslation(2.5f, 0, 0)  * XMMatrixRotationZ(time * 2.0f));
	//objects[2]->ChangeWorld(XMMatrixScaling(0.2f, 0.2f, 0.2f) * XMMatrixRotationZ(t) * XMMatrixTranslation(1.0f, 0, 0)  * XMMatrixRotationZ(t * 3.0f)  * XMMatrixTranslation(2.5f, 0, 0)  * XMMatrixRotationZ(t * 2.0f));
	//objects[3]->ChangeWorld(XMMatrixScaling(0.1f, 0.1f, 0.1f) * XMMatrixRotationZ(t) * XMMatrixTranslation(0.5f, 0, 0)  * XMMatrixRotationZ(t * 4.0f) * XMMatrixTranslation(1.0f, 0, 0)  * XMMatrixRotationZ(t * 3.0f)  * XMMatrixTranslation(2.5f, 0, 0)  * XMMatrixRotationZ(t * 2.0f));
	//objects[4]->ChangeWorld(XMMatrixScaling(0.25f, 0.25f, 0.25f)  * XMMatrixTranslation(1.5f, 0, 0) * XMMatrixRotationZ(-t));
	//objects[5]->ChangeWorld(XMMatrixScaling(0.25f, 0.25f, 0.25f)  * XMMatrixTranslation(3.0f, 0, 0) * XMMatrixRotationZ(t));

	for (int i = 0; i < gameObjects.size(); i++)
		gameObjects[i]->Update(time);
	_pCurrCamera->Update(time);

}

void GameManager::Input(float deltaTime)
{
	if (GetAsyncKeyState(VK_NUMPAD1))
		_pCurrCamera = _pCamera;
	else if (GetAsyncKeyState(VK_NUMPAD2))
		_pCurrCamera = _pCamera2;

	if (GetAsyncKeyState('W'))
		_pCurrCamera->MovePosition(0, 0, (1 * deltaTime) * _pCurrCamera->GetMovementSpeed());
	if (GetAsyncKeyState('S'))
		_pCurrCamera->MovePosition(0, 0, (-1 * deltaTime) * _pCurrCamera->GetMovementSpeed());
	if (GetAsyncKeyState('D'))
		_pCurrCamera->MovePosition((1 * deltaTime) * _pCurrCamera->GetMovementSpeed(), 0, 0);
	if (GetAsyncKeyState('A'))
		_pCurrCamera->MovePosition((-1 * deltaTime) * _pCurrCamera->GetMovementSpeed(), 0, 0);
	if (GetAsyncKeyState(VK_SPACE))
		_pCurrCamera->MovePosition(0, (1 * deltaTime) * _pCurrCamera->GetMovementSpeed(), 0);
	if (GetAsyncKeyState(VK_SHIFT))
		_pCurrCamera->MovePosition(0, (-1 * deltaTime) * _pCurrCamera->GetMovementSpeed(), 0);
	if (GetAsyncKeyState('E'))
		_pCurrCamera->Rotate((1 * deltaTime) * _pCurrCamera->GetMovementSpeed());
	if (GetAsyncKeyState('Q'))
		_pCurrCamera->Rotate((-1 * deltaTime) * _pCurrCamera->GetMovementSpeed());
}
