#include "Pyramid.h"



Pyramid::Pyramid()
{
	pVertices = vertices;
	pIndices = indices;
	indexAmount = 18;
	vertexAmount = 5;
}


Pyramid::~Pyramid()
{
	pVertices = nullptr;
	pIndices = nullptr;
}
