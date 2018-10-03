#pragma once
#include "Application.h"

class Object : Application
{
public:
	static struct Vertex
	{
		XMFLOAT3 Pos;
		XMFLOAT4 Color;
	};

	Object(Vertex vertices[]);
	Object();
	~Object();

protected:

	virtual void Draw();

	Vertex vertices[];

};

