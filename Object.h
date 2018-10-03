#pragma once

#include <DirectXMath.h>




class Object
{



public:
	static struct StandardVertex
	{
		DirectX::XMFLOAT3 Pos;
		DirectX::XMFLOAT4 Color;
	};

	Object(StandardVertex vertices[]);
	Object();
	~Object();

protected:

	virtual void Draw();
	int vertexAmount;
	int indexAmount;

};

