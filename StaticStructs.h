#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
static class StaticStructs {
public:
	static struct StandardVertex
	{
		DirectX::XMFLOAT3 Pos;
		DirectX::XMFLOAT4 Colour;
	};

	struct ConstantBuffer
	{
		DirectX::XMMATRIX mWorld;
		DirectX::XMMATRIX mView;
		DirectX::XMMATRIX mProjection;
		float gTime;
	};

	static struct Vector3f{
		float x;
		float y;
		float z;
	};

};