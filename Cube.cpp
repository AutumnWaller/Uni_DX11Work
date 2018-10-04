#include "Cube.h"



Cube::Cube()
{
	vertexAmount = 8;
	indexAmount = 36;
	pVertices = vertices;
	pIndices = indices;
}


Cube::~Cube()
{
	pVertices = nullptr;
	pIndices = nullptr;
}
