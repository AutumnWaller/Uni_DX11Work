#include "Object.h"

Object::Object()
{

}


void Object::ChangeColour(DirectX::XMFLOAT4 newColour)
{
	colour = newColour;
	for (int i = 0; i < vertexAmount; i++) {
		pVertices[i].Colour = newColour;
	}
}


Object::Object(StandardVertex vertices[])
{
}

Object::~Object()
{
	delete pVertices;
	delete pIndices;
}
