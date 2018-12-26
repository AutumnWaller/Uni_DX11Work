#include "GameManager.h"




GameManager::GameManager()
{
}


GameManager::~GameManager()
{
	gameObjects.~vector();
	delete _pCameraThirdPerson, _pCameraFront;
	delete car;
}

void GameManager::Initialise(ID3D11Device *deviceRef, ID3D11DeviceContext *context, ID3D11Buffer *cb)
{

	XMStoreFloat4x4(&_World, XMMatrixIdentity());

	_pCameraThirdPerson = new Camera(XMVECTOR(XMVectorSet(0.0f, 0.0f, -3.0f, 0.0f)), XMVECTOR(XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)), XMVECTOR(XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)), XMVECTOR(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f)));
	_pCameraFront = new Camera(XMVECTOR(XMVectorSet(0.0f, 10.0f, 3.0f, 0.0f)), XMVECTOR(XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f)), XMVECTOR(XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)), XMVECTOR(XMVectorSet(0.0f, 0.0f, -2.0f, 0.0f)));
	_pCurrCamera = _pCameraThirdPerson;

	//Object *car = new Object("Models/car.obj", L"Textures/black.dds");
	//gameObjects.emplace_back(car);
	//Object *car2 = new Object("Models/sphere.obj", nullptr);
	//gameObjects.emplace_back(car2);

	Object *object = new Object("Models/Hercules.obj", L"Textures/Hercules_COLOR.dds");
	object->SetPosition(5, 0, 0);
	gameObjects.emplace_back(object);

	Grid *grid = new Grid(100, 100);
	grid->SetPosition(0, 0, 0);
	grid->SetTexture(L"Textures/asphalt.dds");
	//grid->SetSize(5, 5);
	gameObjects.emplace_back(grid);

	car = new Car();
	car->SetScale(0.01f, 0.01f, 0.01f);
	car->SetPosition(20, 1, 20);
	_pCameraFront->FollowObject(car);
	_pCurrCamera->FollowObject(car);
	gameObjects.emplace_back(car);

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
	Input(_Time);
	car->Drive(_Time);

	//gameObjects[0]->SetRotation(-1 * time, 1, -1);
	//gameObjects[0]->ChangeWorld(XMMatrixScaling(0.5f, 0.5f, 0.5f)  * XMMatrixRotationZ(time * 0.25f));
	//gameObjects[1]->ChangeWorld(XMMatrixScaling(1.0f, 1.0f, 1.0f) * XMMatrixRotationZ(time) * XMMatrixTranslation(2.5f, 0, 0)  * XMMatrixRotationZ(time * 2.0f));
	//objects[2]->ChangeWorld(XMMatrixScaling(0.2f, 0.2f, 0.2f) * XMMatrixRotationZ(t) * XMMatrixTranslation(1.0f, 0, 0)  * XMMatrixRotationZ(t * 3.0f)  * XMMatrixTranslation(2.5f, 0, 0)  * XMMatrixRotationZ(t * 2.0f));
	//objects[3]->ChangeWorld(XMMatrixScaling(0.1f, 0.1f, 0.1f) * XMMatrixRotationZ(t) * XMMatrixTranslation(0.5f, 0, 0)  * XMMatrixRotationZ(t * 4.0f) * XMMatrixTranslation(1.0f, 0, 0)  * XMMatrixRotationZ(t * 3.0f)  * XMMatrixTranslation(2.5f, 0, 0)  * XMMatrixRotationZ(t * 2.0f));
	//objects[4]->ChangeWorld(XMMatrixScaling(0.25f, 0.25f, 0.25f)  * XMMatrixTranslation(1.5f, 0, 0) * XMMatrixRotationZ(-t));
	//objects[5]->ChangeWorld(XMMatrixScaling(0.25f, 0.25f, 0.25f)  * XMMatrixTranslation(3.0f, 0, 0) * XMMatrixRotationZ(t));
	for (int i = 0; i < gameObjects.size(); i++)
		gameObjects[i]->Update(_Time);
	_pCurrCamera->Update(_Time);
}

void GameManager::Input(float deltaTime)
{
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
		_pCurrCamera->MoveRotation((-1 * deltaTime), 0, 0);

}
