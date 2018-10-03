#include "Object.h"



void Object::Draw()
{
}

Object::Object()
{
}


void Object::ChangeColour(DirectX::XMFLOAT4 newColour)
{
	colour = newColour;
	for (int i = 0; i < vertexAmount; i++) {
		pVertices[i].Color = newColour;
	}
}

Object::Object(StandardVertex vertices[])
{
}

Object::~Object()
{
}
