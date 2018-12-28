#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
using namespace DirectX;
class StaticStructs {
public:
	struct StandardVertex
	{
		XMFLOAT3 Pos;
		XMFLOAT3 Normal;
		XMFLOAT2 TexC;
		bool operator<(const StandardVertex other) const
		{
			return memcmp((void*)this, (void*)&other, sizeof(StandardVertex)) > 0;
		};

	};

	struct ConstantBuffer
	{
		XMMATRIX mWorld;
		XMMATRIX mView;
		XMMATRIX mProjection;
		float gTime;
		
		XMFLOAT3 LightVecW;

		XMFLOAT4 DiffuseMtrl;
		XMFLOAT4 DiffuseLight;
		
		XMFLOAT3 AmbientMtrl;
		XMFLOAT3 AmbientLight;
		XMFLOAT4 cameraEye;
		float specularPower = 2;

		XMFLOAT4 specularMtrl;
		XMFLOAT4 specularLight;

	};

	struct Vector3f{
		float x;
		float y;
		float z;
	};

	static enum ObjectType {
		OBJECT,
		GRID,
		DOME,
		CUBE,
		PYRAMID
	};

};