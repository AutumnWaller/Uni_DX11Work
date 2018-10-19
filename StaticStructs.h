#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
using namespace DirectX;
static class StaticStructs {
public:
	static struct StandardVertex
	{
		XMFLOAT3 Pos;
		XMFLOAT3 Normal;
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

	};

	static struct Vector3f{
		float x;
		float y;
		float z;
	};

};