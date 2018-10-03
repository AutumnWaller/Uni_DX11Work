#pragma once

#include <DirectXMath.h>
#include <Windows.h>



class Object
{

public:
	static struct StandardVertex
	{
		DirectX::XMFLOAT3 Pos;
		DirectX::XMFLOAT4 Color;
	};



	int vertexAmount;
	int indexAmount;
	void ChangeColour(DirectX::XMFLOAT4 newColour = DirectX::XMFLOAT4{0,1,1,0});

	Object(StandardVertex vertices[]);
	Object();
	~Object();

protected:
	StandardVertex *pVertices;
	virtual void Draw();
	DirectX::XMFLOAT4 colour = {0,0,0,0};

};

