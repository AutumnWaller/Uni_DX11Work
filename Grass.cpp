#include "Grass.h"



Grass::Grass()
{
	_pTexturePath = L"Textures/Grass.dds";
	isUpdateable = false;
	Billboard();
}


Grass::~Grass()
{
}
